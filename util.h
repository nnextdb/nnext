/*
 * Copyright NNext Co. and/or licensed to NNext Co.
 * @author [Peter. Njenga]
 *
 * This file and its contents are licensed under the NNext License.
 * Please see the included NOTICE for copyright information and
 * LICENSE for a copy of the license.
 */

#ifndef NNEXT__UTIL_H_
#define NNEXT__UTIL_H_


#include <regex>
#include <exception>
#include <spdlog/fmt/fmt.h>


const nnext::Schema parse_index_schema(const nnext::Schema &schema) {

  unordered_map<std::string, int> counter;
  set<string> pk_set;
  string pk_name;
  nnext::Schema parsed_schema;

  for (auto &si : schema.rptd__schema_item()) {
    string name = si.name();
    /*
     * Todo:
     * Check that the column names are sanitary
     * - Not too long or short
     * - Don't contain strange characters.
     * - schema item names are not repeated.
     */
    if (name.length() < 2 || name.length() > 64) {
      string
          msg = fmt::format("Schema name length must be between [2,64] characters. Found {} characters.", name.length
                                                                                                          ());
      throw invalid_argument(msg);
    }

    if (counter[name]++ > 1) {
      string msg = fmt::format("Repeated schema name '{}'", name.length());
      throw invalid_argument(msg);
    }

    if (si.is_primary()) {
      pk_set.insert(name);
    }
  }

  if (pk_set.size() > 1) {
    string rptd_pks;
    for (auto pk_name : pk_set)
    {
      rptd_pks += pk_name;
      rptd_pks += ",";
    }
    // Remove the last comma (,).
    rptd_pks.pop_back();

    string msg = fmt::format("Found multiple primary keys. {}", rptd_pks);
    throw invalid_argument(msg);
  } else if (pk_set.size() == 0) {
    /*
     * Attempt to infer the schema from the name. The following names are assumed to refer to the primary key
     * [id, uid, pk] as well their variants that begin with underscore such as _id
     */
    set<string> infered_pk_set = {"id", "_id", "pk", "_pk", "uid", "_uid"};

    for (auto &si : schema.rptd__schema_item()) {
      if (infered_pk_set.contains(si.name())) {
        pk_name = si.name();
        break;
      }
    }
  } else {
    pk_name = *pk_set.begin();
  }

  /*
   * Construct a new schema object. Values are copied from the schema we just validated.
   */
  for (auto si : schema.rptd__schema_item()) {
    auto pk_schema_item = parsed_schema.add_rptd__schema_item();
    pk_schema_item->CopyFrom(si);

    if(si.name() == pk_name) {
      pk_schema_item->set_is_primary(true);
      pk_schema_item->set_is_indexed(true);
    }
  }

  return parsed_schema;
}

#endif // NNEXT__UTIL_H_
