VERSION=0.0.11

set -ex

rm -rf nnext-*

cp -r nnext nnext-$VERSION-amd64

NNEXT_SRC_DIR=nnext-$VERSION-amd64
NNEXT_DEB=$NNEXT_SRC_DIR.deb
SHAFILE=$NNEXT_DEB.sha512
S3_REPO=s3://nnext-trove/downloads/

dpkg-deb --build $NNEXT_SRC_DIR

sha512sum $NNEXT_DEB > $SHAFILE

shasum -a 512 -c $SHAFILE

aws s3 cp $NNEXT_DEB $S3_REPO
aws s3 cp $SHAFILE $S3_REPO