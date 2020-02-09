#!/bin/sh
set -e
. ./headers.sh

export PATH="$HOME/opt/cross64/bin:$PATH"
 
for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
