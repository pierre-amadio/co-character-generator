#!/bin/bash 

VERSION=`awk '/VERSION =/ {print $3}' CO.pro`
RELEASE=`awk '/RELEASE =/ {print $3}' CO.pro`
SOURCEDIR=/home/melmoth/rpmbuild/SOURCES 
REPODIR=`pwd`
NAME=`basename $REPODIR`
VERNAME=$NAME-$VERSION
TARNAME=$VERNAME.tar.gz

rm -rf /tmp/$NAME
cd /tmp
#git clone $REPODIR
cp -r $REPODIR $NAME


mv /tmp/$NAME /tmp/$VERNAME
find /tmp/$VERNAME |grep git|xargs rm -rf 
cd /tmp
tar cvzf $TARNAME $VERNAME
mv $TARNAME $SOURCEDIR

echo "The final archive is "$SOURCEDIR/$TARNAME