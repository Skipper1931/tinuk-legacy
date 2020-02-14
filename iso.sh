#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/karyon.kernel isodir/boot/karyon.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "TinukOS" {
	insmod /boot/karyon.kernel
	multiboot /boot/loader32.elf
}
EOF
grub-mkrescue -o tinuk.iso isodir
