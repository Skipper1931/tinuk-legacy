#!/bin/bash
set -e
. ./iso.sh

if [ -z $DISPLAY ]; then # if we're not in a GUI go to Curses UI for QEMU
	export QEMUCurses="--curses"
fi

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom tinuk.iso -d guest_errors -s $QEMUCurses

./clean.sh
