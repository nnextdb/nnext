
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
For detailed installation instructions, please see the [Installation](INSTALL.md) guide.
#### Nnext is supported on
<table>
  <tr>
    <td><img src="https://s3.us-east-2.amazonaws.com/assets.nnext.io/img/build.png" width="50" /></td>
    <td>Build from Source</td>
    <td>Build and install nnext from source using cmake & gcc/g++. Please follow the <a href="/COMPILATION.md">Compilation guide</a>.</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/ab/Logo-ubuntu_cof-orange-hex.svg/570px-Logo-ubuntu_cof-orange-hex.svg.png?20130511162351" width="50" /></td>
    <td>Debian <br> Ubuntu</td>
    <td>Install NNext on Ubuntu using <span style="color: yellowgreen">debian</span> package manager.
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/a/ab/Apple-logo.png" width="50" /></td>
    <td>MacOS</td>
    <td>🚧 WIP 🚧<br>Install via <span style="color: yellowgreen">homebrew</span></td>
  </tr>
  <tr>
    <td><img src="https://www.docker.com/wp-content/uploads/2022/03/vertical-logo-monochromatic.png" width="50" /></td>
    <td>Docker</td>
    <td>🚧 WIP 🚧<br>Get the image <span style="color: yellowgreen">nnext:latest</span> image from docker hub</td>
  </tr>
  <tr>
    <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/39/Kubernetes_logo_without_workmark.svg/1234px-Kubernetes_logo_without_workmark.svg.png" width="50" /></td>
    <td>Kubernetes</td>
    <td>🚧 WIP 🚧<br>Create a NNext service on a kubernetes cluster</td>
  </tr>
  <tr>
    <td><img src="https://www.datocms-assets.com/2885/1620155116-brandhcterraformverticalcolor.svg" width="50" /></td>
    <td>Terraform + Kubernetes</td>
    <td>🚧 WIP 🚧<br>Create a NNext service via Terraform on a kubernetes cluster</td>
  </tr>
  <tr>
    <td><img src="https://www.datocms-assets.com/2885/1620155116-brandhcterraformverticalcolor.svg" width="50" /></td>
    <td>Terraform + NNext Cloud</td>
    <td>🚧 WIP 🚧<br>Provision a Cluster on NNext's cloud via terraform</td>
  </tr>
  <tr>
    <td><img src="https://www.pngall.com/wp-content/uploads/2/Windows-Logo-PNG-File-Download-Free.png" width="50" /></td>
    <td>Windows</td>
    <td>🚧 WIP 🚧<br>Not really supported, for purposes development only</td>
  </tr>
 </table>

## Quick Start

Here's a quick example showcasing how you can create an index, insert vectors/documents and search it on NNext.

Let's begin by installing the NNext server.

```shell
NNEXT_PKG=nnext-0.0.1-amd64.deb
NNEXT_URL=https://trove.nnext.io/downloads
wget $NNEXT_URL/$NNEXT_PKG
wget $NNEXT_URL/$NNEXT_PKG.sha512
shasum -a 512 -c $NNEXT_PKG.sha512
sudo dpkg -i $NNEXT_PKG
```

Run nnext
```shell
sudo nnext
```

You should see output like this
```shell
...
...
[2022-04-27 13:02:10.029] [info] 🏁 Started NNext at ▸ 127.0.0.1:6040
```

Install the Python client for NNext:

```
pip install nnext
```

We can now initialize the client and create a `movies` index:

```python
import nnext
import numpy as np
from nnext import _and, _eq, _gte, _in

nnclient = nnext.Client({
  'nodes': [{
    'host': 'localhost',
    'port': '6040'
  }]
})
```
Create an index
```python
dims = 768
nnindex = client.index.create({
  "name": "movies_simple",
  "dims": dims
})
```

Add vectors to the index.
```python
data = np.random.rand(100, dims)
add_res = nnindex.add(query)
```
Search the vectors. Get the nearest 7 vectors for each query vector.
```python
query = np.random.rand(5,dims)
sch_res = idx.search(query, k=7)
```

## Documentation

All NNext Server and Client documentation, including pynext integration articles and helpful recipes, can be found at:
<br/>

🚧 WIP 🚧<br>
[https://nnext.ai/docs/](https://nnext.ai/docs)

## FAQs

<details><summary>How does this differ from Faiss, ScaNN and Annoy?</summary>
<p>
First of all, NNext uses Faiss under the hood. The main thing to note about these software come as python
packages installable via PIP or Conda. These libraries are very easy to use, from install to the API. However, while
allowing you to quickly get started, they don't allow for persistence, index growth or high availability. If your
application goes down for whatever reason, so do your search indices and data.
</p>
</details>

<details><summary>How does this differ from Milvus?</summary>
<p>
Milvus is a large piece of software, that takes non-trivial amount of effort to setup, administer, scale and fine-tune.
It offers you a few thousand configuration parameters to get to your ideal configuration. So it's better suited for large teams
who have the bandwidth to get it production-ready, regularly monitor it and scale it, especially when they have a need to store
billions of documents and petabytes of data (eg: logs).

NNext is built specifically for decreasing the "time to market" for a delightful nearest-neighbor search experience. It 
is a light-weight yet powerful & scaleable alternative that focuses on Developer Happiness and Experience with a 
clean well-documented API, clear semantics and smart defaults so it just works well out-of-the-box, without you having to turn many knobs.

See a side-by-side feature comparison [here](https://typesense.org/typesense-vs-algolia-vs-elasticsearch-vs-meilisearch/).
</p>
</details>

<details><summary>How does this differ other fully managed solutions like Pinecone?</summary>
<p>
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
</p>
</details>

<details><summary>Why the Elastic License 2.0?</summary>
<p>
NNext Server is **source available**, **server software** and we expect users to typically run it as a separate daemon, 
and not integrate it 
with their own code. Elastic Licence 2.0 (EL2) covers and allows for this use case **generously**. We aim to set the
minimum limitations necessary to strike a fair balance between freedom to use, share and change the software, and 
preventing actions that will harm the community.

If you have specifics that prevent you from using NNext due to a licensing issue, we're happy to explore this topic 
further with you. Please reach out to us legal@nnext.ai.
</p>
</details>
<details><summary>I heard Elasticsearch and OpenSearch were planning on implementing ANN Search?</summary>
<p>
Fundamentally, Elasticsearch and it's variants, run on the JVM, which by itself can be quite an effort to tune to run 
optimally. NNext, on the other hand, is a single light-weight self-contained native binary, so it's simple to setup and
operate. Furthermore, ANN search on Elasticseach runs as a secondary process, a sidecar, which is not natively 
supported by the main indexing engine.
</p>
</details>

## Who is NNext?

[NNext](https://nnext.io/) builds open-source ML-Ops software to help make development and deployment of machine 
learning applications painless.

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

