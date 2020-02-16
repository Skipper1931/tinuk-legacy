#!/bin/bash
set -e
cd /tinuk
echo Starting qemu.sh
. toolchain/iso.sh

if [ -z $DISPLAY ]; then # if we're not in a GUI go to Curses UI for QEMU
	export QEMUCurses="--curses"
fi

qemu-system-$(toolchain/target-triplet-to-arch.sh $HOST) -cdrom tinuk.iso -d guest_errors -s $QEMUCurses

echo Finished qemu.sh