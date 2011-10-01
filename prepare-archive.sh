#!/bin/bash 

VERSION=`awk '/VERSION =/ {print $3}' CO.pro`
RELEASE=`awk '/RELEASE =/ {print $3}' CO.pro`
SOURCEDIR=/home/melmoth/rpmbuild/SOURCES 
REPODIR=`pwd`
NAME=`basename $REPODIR`
VERRELNAME=$NAME-$VERSION-$RELEASE
TARNAME=$VERRELNAME.tar.gz

rm -rf /tmp/$NAME
cd /tmp
git clone $REPODIR


mv /tmp/$NAME /tmp/$VERRELNAME
find /tmp/$VERRELNAME |grep git|xargs rm -rf 
cd /tmp
tar cvzf $TARNAME $VERRELNAME
mv $TARNAME $SOURCEDIR