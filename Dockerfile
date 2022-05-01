FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN apt-get install -y \
    gpg libdigest-sha-perl wget \
    intel-mkl

RUn apt-get update

ARG NNEXT_VERSION=0.0.19
ARG NNEXT_PKG=nnext-$NNEXT_VERSION-amd64.deb
ARG NNEXT_URL=https://trove.nnext.io/downloads

RUN wget --quiet $NNEXT_URL/$NNEXT_PKG
RUN wget $NNEXT_URL/$NNEXT_PKG.sha512
RUN shasum -a 512 -c $NNEXT_PKG.sha512
RUN dpkg -i $NNEXT_PKG

ENTRYPOINT ["nnext"]