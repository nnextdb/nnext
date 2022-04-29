FROM ubuntu:20.04

RUN apt-get update

RUN apt-get install wget curl libdigest-sha-perl -y

ARG NNEXT_PKG=nnext-0.0.6-amd64.deb
ARG NNEXT_URL=https://trove.nnext.io/downloads

RUN wget --quiet $NNEXT_URL/$NNEXT_PKG
RUN wget $NNEXT_URL/$NNEXT_PKG.sha512
RUN shasum -a 512 -c $NNEXT_PKG.sha512
RUN dpkg -i $NNEXT_PKG

CMD nnext