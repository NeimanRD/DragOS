#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/dragos.kernel isodir/boot/dragos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "dragos" {
	multiboot /boot/dragos.kernel
}
EOF
grub-mkrescue -o dragos.iso isodir
