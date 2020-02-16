#!/bin/sh
set -e
cd /tinuk
echo Starting clean.sh
. toolchain/config.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && $MAKE clean)
done
 
rm -rf sysroot
rm -rf isodir
rm -rf tinuk.iso

echo Finished clean.sh