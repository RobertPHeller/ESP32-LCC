#!/bin/bash
########################################################
##
##  Copyright (c) 2025, Robert Heller
##  License       :
##  Date          : $Date$
##  Author        : $Author$
##  Created By    : Robert Heller
##  Created       : 2025-12-07 09:28:11
##  Last Modified : <260326.1306>
##
##  Description	  :
##
########################################################
. ~/esp-idf-v5.4.3/esp-idf/export.sh
export IDF_TARGET=esp32s3
idf.py build
BuildBinaries="build/bootloader/bootloader.bin build/partition_table/partition-table.bin build/ota_data_initial.bin build/AtlasLightBoardWiFiLCCTraction_Sound.bin"
BuildDocs="doc/KitBooklet.pdf  doc/UserManual.pdf"
FlashProgram='~/.espressif/python_env/idf5.0_py3.11_env/bin/python ~/esp-idf-v5.4.3/esp-idf/components/esptool_py/esptool/esptool.py -p (PORT) -b 460800 --before default_reset --after hard_reset --chip esp32s3  write_flash --flash_mode dio --flash_size 4MB --flash_freq 80m 0x0 bin/bootloader.bin 0x8000 bin/partition-table.bin 0xe000 bin/ota_data_initial.bin 0x10000 bin/AtlasLightBoardWiFiLCCTraction_Sound.bin'
GITRevShort=`git rev-parse --short HEAD`
mkdir /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort
mkdir /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort/bin
mkdir /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort/doc
cp -v $BuildBinaries /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort/bin
cp -v $BuildDocs /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort/doc
echo "$FlashProgram" > /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort/FlashCommand
here=`pwd`
rm -f AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort.zip
(cd /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort; zip $here/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort.zip -r .)
rm -rf /tmp/AtlasLightBoardWiFiLCCTraction_Sound-$GITRevShort

