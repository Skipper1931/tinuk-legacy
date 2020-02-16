#!/bin/sh
set -e
cd /tinuk
echo Staring build.sh
. toolchain/headers.sh

export PATH="/opt/cross64/bin:/opt/cross32/bin:$PATH"

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install -j 12)
done

echo Finished build.sh