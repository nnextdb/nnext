
# <a href="https://nnext.ai/"><img src="https://d135j1zm1liera.cloudfront.net/nnext-logo-wide.png" height="100" alt="Apollo Client"></a>

## About

NNext is a
* ⚡ blazingly fast
* 📖 source-available [[Elastic License 2.0]](https://www.elastic.co/licensing/elastic-license)
* 🔍 nearest-neighbors vector search engine

<a href="https://discord.gg/vBPpJkS"><img src="https://img.shields.io/badge/chat-slack-orange.svg?logo=slack&style=flat"></a>
<a href="https://twitter.com/intent/follow?screen_name=nnextai"><img src="https://img.shields.io/badge/Follow-nnextai-blue.svg?style=flat&logo=twitter"></a>

[Installation](#installation) | [Contributing](#contributing) |  [Getting Started](#getting-started) | [Connecting 
To NNext](#connecting-to-redis)

## Installation

#### Nnext is supported on
<table>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/ab/Logo-ubuntu_cof-orange-hex.svg/570px-Logo-ubuntu_cof-orange-hex.svg.png?20130511162351" width="50" /></td>
    <td>Ubuntu</td>
    <td>Install nnext on Ubuntu using <span style="color: yellowgreen">debian</span> package manager.</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/a/ab/Apple-logo.png" width="50" /></td>
    <td>MacOS</td>
    <td>Install via <span style="color: yellowgreen">homebrew</span></td>
  </tr>
  <tr>
    <td><img src="https://www.docker.com/wp-content/uploads/2022/03/vertical-logo-monochromatic.png" width="50" /></td>
    <td>Docker</td>
    <td>Get the image <span style="color: yellowgreen">nnext:latest</span> image from docker hub</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/39/Kubernetes_logo_without_workmark.svg/1234px-Kubernetes_logo_without_workmark.svg.png" width="50" /></td>
    <td>Kubernetes</td>
    <td>Create a NNext service on a kubernetes cluster</td>
  </tr>
  <tr>
    <td><img src="https://www.datocms-assets.com/2885/1620155116-brandhcterraformverticalcolor.svg" width="50" /></td>
    <td>Terraform + Kubernetes</td>
    <td>Create a NNext service via Terraform on a kubernetes cluster</td>
  </tr>
  <tr>
    <td><img src="https://www.datocms-assets.com/2885/1620155116-brandhcterraformverticalcolor.svg" width="50" /></td>
    <td>Terraform + NNext Cloud</td>
    <td>Provision a Cluster on NNext's cloud via terraform</td>
  </tr>
  <tr>
    <td><img src="https://cdn-icons.flaticon.com/png/512/4997/premium/4997543.png?token=exp=1649875771~hmac=2b99925c335cf7a3a0e9805274c30c69" width="50" /></td>
    <td>Build from Source</td>
    <td>Build and install nnext from source using cmake & gcc/g++</td>
  </tr>
  <tr>
    <td><img src="https://www.pngall.com/wp-content/uploads/2/Windows-Logo-PNG-File-Download-Free.png" width="50" /></td>
    <td>Windows</td>
    <td>Not really supported, for purposes development only</td>
  </tr>
 </table>

## Quick Start

Here's a quick example showcasing how you can create an index, insert vectors/documents and search it on NNext.

Let's begin by starting the NNext server via Docker:

```
docker run -p 6040:6040 -v/tmp/data:/data nnext/nnext:latest --data-dir /data --api-key=Hu52dwsas2AdxdE
```

We have a [API Client](#api-clients) in python only, but let's use it for this example.

Install the Python client for NNext:

```
pip install nnext
```

We can now initialize the client and create a `movies` index:

```python
import nnext
from nnext import _and, _eq, _gte, _in

nnclient = nnext.Client({
  'api_key': 'Hu52dwsas2AdxdE',
  'nodes': [{
    'host': 'localhost',
    'port': '6040'
  }],
  'connection_timeout_seconds': 2
})
```
Broadly speaking, you can create two types of indices
### 1. Simple indices
```python
nnindex = client.index.create({
  "name": "movies_simple",
  "index_type": "approximated",
  "dims": 768
})
```


You can simply insert vector embeddings into the index.
### 1. Compound indices
```python
nnindex = client.index.create({
  "name": "movies",
  "schema": {
      "id" : "string", #⬅ inferred primary key
      "title" : "string",
      "released_year" : "int32",
      "genre" :  "float",
      "wikipage" : "string",
      "plot" : "string",
      "rating" :  "float"
  },
  "index_type": "approximated",
  "dims": 768
})
```
**Did you notice that the primary key was not specified?** No big deal. NNext automatically infers or creates vector 
IDs out-of-the-box! Fields starting with _id_, __id_, _uid_ or __uid_ are automatically inferred as primary keys.


Now, let's add a vector to the collection we just created:

```python
vector = {
 "id": "124",
 "company_name": "Stark Industries",
 "num_employees": 5215,
 "country": "USA",
}

nnindex.documents.create(document)
```

Finally, let's search for the document we just indexed:

```python
q_filter = {
    _and: [
        { "Release Year": { _gte: 2015 } },
        { "Genre": { _eq: "comedy" } },
        { "actors": { _in: ["Russell Crowe"] } }
    ]
}

client.collections['companies'].documents.search(search_parameters)
```

## Contributing

### Introduction
First off, 🙏🏾 thank you for considering contributing to nnext. We value community contributions!

### How can you help?

You may already know what you want to contribute -- a fix for a bug you encountered, or a new feature your team wants to use.

If you don't know what to contribute, keep an open mind! Here's some examples of helpful contributions that mean 
less work for you
* Improving documentation
* bug triaging
* writing tutorials

Checkout [guide to contributing](https://github.com/redis/redis-py/blob/master/CONTRIBUTING.md) to learn more.


## Documentation

All NNext Server and Client documentation, including pynext integration articles and helpful recipes, can be found at:
<br/>

[https://nnext.ai/docs/](https://nnext.ai/docs)

## FAQs

### How does this differ from Faiss, ScaNN and Annoy?

First of all, NNext uses Faiss under the hood. The main thing to note about these software come as python 
packages installable via PIP or Conda. These libraries are very easy to use, from install to the API. However, while 
allowing you to quickly get started, they don't allow for persistence, index growth or high availability. If your
application goes down for whatever reason, so do your search indices and data.

### How does this differ from Milvus?

Milvus is a large piece of software, that takes non-trivial amount of effort to setup, administer, scale and fine-tune.
It offers you a few thousand configuration parameters to get to your ideal configuration. So it's better suited for large teams
who have the bandwidth to get it production-ready, regularly monitor it and scale it, especially when they have a need to store
billions of documents and petabytes of data (eg: logs).

NNext is built specifically for decreasing the "time to market" for a delightful nearest-neighbor search experience. It 
is a light-weight yet powerful & scaleable alternative that focuses on Developer Happiness and Experience with a 
clean well-documented API, clear semantics and smart defaults so it just works well out-of-the-box, without you having to turn many knobs.

See a side-by-side feature comparison [here](https://typesense.org/typesense-vs-algolia-vs-elasticsearch-vs-meilisearch/).

### How does this differ other fully managed solutions like Pinecone?

In brief - **no vendor lock-in**. Tired of using NNext cloud? Pack up your vectors and go. Obviously we don't want you 
to go, but if you have to, NNext Cloud allows you to download a compressed zip file containing the latest backup of 
your vectors to your machine. These vectors can then be used with another installation of NNext on premise or on 
another cloud provider.

Pinecone is a proprietary, hosted, nearest-neighbour search-as-a-service product that works well, when cost is not an 
issue. However, fast growing applications will quickly run into search & indexing limits, accompanied by expensive plan
upgrades as they scale.

NNext on the other hand is an open-source product that you can run on your own infrastructure or
use our managed SaaS offering - [NNext Cloud](https://app.nnext.ai).
The open source version is free to use (besides of course your own infra costs).
With NNext Cloud we do not charge by records or search operations. Instead, you get a dedicated cluster
and you can throw as much data and traffic at it as it can handle. You only pay a fixed hourly cost & bandwidth charges
for it, depending on the configuration your choose, similar to most modern cloud platforms.

From a product perspective, NNext is closer in spirit to Jina.ai than Pinecone.

See a side-by-side feature comparison [here](https://nnext.ai/product-matrix?source=gitreadme).

### Speed is great, but what about the memory footprint?

A fresh NNext server will consume about 50 MB of memory. As you start indexing documents, the memory use will
increase correspondingly. How much it increases depends on the number and type of fields you index.

We strove to keep the in-memory data structures lean. To give you a rough idea: when 1 million
vector embeddings of the ImageNet dataset are indexed, NNext consumes 16GB of memory. 
For comparison, the same dataset stored in raw-uncompressed format in a redis server is 32GB. If you have any 
numbers from your own datasets that we can add to this section, please send us a PR!

### Why the Elastic License 2.0?

NNext Server is **source available**, **server software** and we expect users to typically run it as a separate daemon, 
and not integrate it 
with their own code. Elastic Licence 2.0 (EL2) covers and allows for this use case **generously**. We aim to set the
minimum limitations necessary to strike a fair balance between freedom to use, share and change the software, and 
preventing actions that will harm the community. Key among these adverse actions is the exploitative tendency of "big 
clouds" to egregiously fork, privatize and subsequently commercialize what was otherwise free software all without 
contributing back to the community significantly.

If you have specifics that prevent you from using NNext due to a licensing issue, we're happy to explore this topic 
further with you. Please reach out to us legal@nnext.ai.

### I heard Elasticsearch and OpenSearch were planning on implementing ANN Search?

Fundamentally, Elasticsearch and it's variants, run on the JVM, which by itself can be quite an effort to tune to run 
optimally. NNext, on the other hand, is a single light-weight self-contained native binary, so it's simple to setup and
operate. Furthermore, ANN search on Elasticseach runs as a secondary process, a sidecar, which is not natively 
supported by the main indexing engine.


## Who is NNext?

[NNext](https://nnext.ai/) builds open-source ML-Ops software to help make development and deployment of machine 
learning applications painless.
