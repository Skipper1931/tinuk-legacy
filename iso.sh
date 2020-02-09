#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/karyon.kernel isodir/boot/karyon.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "TinukOS" {
	echo If you see this, it is because the system could not succesfully boot. This may be because you are not running a 64-bit CPU.
	multiboot /boot/karyon.kernel
}
EOF
grub-mkrescue -o tinuk.iso isodir
