#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/tinuk.kernel isodir/boot/tinuk.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "Tinuk" {
	multiboot /boot/tinuk.kernel
}
EOF
grub-mkrescue -o tinuk.iso isodir