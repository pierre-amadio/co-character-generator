#!/bin/bash 

VERSION=`awk '/VERSION =/ {print $3}' CO.pro`
RELEASE=`awk '/RELEASE =/ {print $3}' CO.pro`
SOURCEDIR=/tmp
REPODIR=`pwd`
NAME=`basename $REPODIR`
VERNAME=$NAME-$VERSION
TARNAME=$VERNAME.tar.gz

make clean
make distclean
rm -rf /tmp/$NAME
rm -rf /tmp/$VERNAME
rm $TARNAME/$VERNAME
cd /tmp
#git clone $REPODIR
cp -r $REPODIR $NAME


mv /tmp/$NAME /tmp/$VERNAME
find /tmp/$VERNAME |grep git|xargs rm -rf 
cd /tmp
tar cvzf $TARNAME $VERNAME
mv $TARNAME $SOURCEDIR

echo "The final archive is "$SOURCEDIR/$TARNAME
