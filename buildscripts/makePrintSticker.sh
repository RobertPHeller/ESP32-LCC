#!/bin/bash
rm PrintSticker.kit
sdx qwrap PrintSticker.tcl
rm -rf PrintSticker.vfs
sdx unwrap PrintSticker.kit
mkdir PrintSticker.vfs/lib/support
cp SnitReceiptPrinter.tcl PrintSticker.vfs/lib/support/
ln -s /usr/share/tcltk/tcllib1.19/snit PrintSticker.vfs/lib/
echo 'pkg_mkIndex PrintSticker.vfs/lib/support/'|/usr/bin/tclsh
sdx wrap PrintSticker.kit
rm -rf PrintSticker.vfs
