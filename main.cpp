/*
 * Copyright NNext Co. and/or licensed to NNext Co.
 * @author [Peter. Njenga]
 *
 * This file and its contents are licensed under the NNext License.
 * Please see the included NOTICE for copyright information and
 * LICENSE for a copy of the license.
 */

// Standard Libraries
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>

// External Libraries
#include <argparse/argparse.hpp>
#include <grpcpp/grpcpp.h>
#include <rocksdb/db.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

// Internal Libraries
#include "server.h"

using grpc::Status;
using nnext::NNext;

void RunServer(argparse::ArgumentParser &opts, spdlog::logger &logger) {
  std::string host = opts.get("--host");
  std::string port = opts.get("--port");
  std::string data_dir = opts.get("--data-dir");

  std::string server_address = host + ":" + port;
    NNextServiceImpl nnext_service;

  rocksdb::Status db_status;
  rocksdb::Options options;
  options.create_if_missing = true;
  options.enable_blob_files = true;

  /*
   * Connect to RocksDB.
   */
    db_status = rocksdb::DB::Open(options, data_dir, &nnext_service._rocksdb);

    if (!db_status.ok()) {
      logger.critical("RocksDB error {}", db_status.ToString());
      exit(1);
    } else {
      logger.debug("Connected to RocksdDB. Data directory {}", data_dir);
    }

    /*
     * Reload data from disk.
     */
    nnext_service._init();

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address,
    grpc::InsecureServerCredentials());

    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&nnext_service);

    // Finally assemble the server.
    std::unique_ptr<grpc::Server> nnext_server(builder.BuildAndStart());
    logger.info("🏁 Started NNext at ▸ {}", server_address);

    // Wait for the server to shut down. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    nnext_server->Wait();
}

int main(int argc, char *argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;
  int verbosity = 0;

  argparse::ArgumentParser opts("nnext", "0.0.0");

  opts.add_argument("-V", "--verbose")
      .action([&](const auto &) { ++verbosity; })
      .append()
      .help("Verbose mode.  Causes nnext to print debugging messages about its "
            "progress.  This is helpful in debugging connection, "
            "authentication, and configuration problems.  Multiple -v options "
            "increase the verbosity.  The maximum is 3.")
      .default_value(false)
      .implicit_value(true)
      .nargs(0);

  opts.add_argument("--port", "-p")
      .default_value(std::string("6040"))
      .help("Specifies the port for the server to listen to.");

  opts.add_argument("--host", "-h")
      .default_value(std::string("127.0.0.1"))
      .help("Specifies the host for the server to listen to.");

  opts.add_argument("--data-dir", "--data_dir", "-D")
      .help("Specifies the directory to use for data storage.")
      .default_value(std::string("/var/lib/nnext/data"));

  opts.add_argument("--log-dir", "--log-dir", "-g")
      .help("Specifies the directory to write logs to.")
      .default_value(std::string("/var/log/nnext"));

  opts.add_argument("--index-type", "--index_type", "-I")
      .default_value("Flat")
      .action([](const std::string &value) {
        static const std::vector<std::string> choices = {"Flat", "HNSW", "IVF",
                                                         "SQ8", "PQ"};
        if (std::find(choices.begin(), choices.end(), value) != choices.end()) {
          return value;
        }
        spdlog::warn("Unknown index should appear in both console and file");
        return std::string{"Flat"};
      });

  try {
    opts.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << opts;
    std::exit(1);
  }

  switch (verbosity) {
  case 0:
    spdlog::set_level(spdlog::level::info);
    break;
  case 1:
    spdlog::set_level(spdlog::level::debug);
    break;
  default:
    spdlog::set_level(spdlog::level::err);
  }

  std::string log_dir = opts.get("--log-dir");
  std::string log_file = fmt::format("{}/nnext.txt", log_dir);

  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::info);

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      log_dir, true);
  file_sink->set_level(spdlog::level::trace);

  spdlog::logger logger("multi_sink", {console_sink, file_sink});
  logger.set_level(spdlog::level::debug);

  logger.info("\nATTENTION: NNext.ai collects completely anonymous telemetry "
               "regarding usage."
               "\nThis information is used to shape NNext.ai' roadmap and "
               "prioritize features."
               "\nYou can learn more, including how to opt-out if you'd not "
               "like to participate"
               "\nin this anonymous program, by visiting the following URL:"
               "\nhttps://nnext.ai/telemetry");
  RunServer(opts, logger);

  return 0;
}