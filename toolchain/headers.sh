#!/bin/sh
set -e
cd /tinuk
echo Starting headers.sh
. toolchain/config.sh

mkdir -p "$SYSROOT"

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done

echo Finished headers.sh