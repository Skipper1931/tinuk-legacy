#!/bin/sh
set -e
. ./build.sh
 
mkdir -p sysroot/boot/grub
mkdir -p sysroot/sys/src

cp -r kernel sysroot/sys/src
cp -r libc sysroot/sys/src

find sysroot/sys/src -type f -name "*.d" -delete
find sysroot/sys/src -type f -name "*.o" -delete

cat > sysroot/boot/grub/grub.cfg << EOF
menuentry "TinukOS" {
	multiboot /boot/loader32.elf
	module /boot/karyon.kernel "KARYON_KERNEL"
}
EOF
grub-mkrescue -o tinuk.iso sysroot
