
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