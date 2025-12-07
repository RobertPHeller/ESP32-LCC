#!/bin/bash
########################################################
##
##  Copyright (c) 2025, Robert Heller
##  License       :
##  Date          : $Date$
##  Author        : $Author$
##  Created By    : Robert Heller
##  Created       : 2025-12-07 09:28:11
##  Last Modified : <251207.0949>
##
##  Description	  :
##
########################################################
./build.sh
BuildBinaries = "build/bootloader/bootloader.bin build/partition_table/partition-table.bin build/ota_data_initial.bin build/AtlasLightBoardWiFiLCCTraction.bin"
BuildDocs = " doc/KitBooklet.pdf  doc/UserManual.pdf"
FlashProgram = '~/.espressif/python_env/idf5.0_py3.11_env/bin/python ../../../esp-idf-v5.0.1/components/esptool_py/esptool/esptool.py -p (PORT) -b 460800 --before default_reset --after hard_reset --chip esp32s3  write_flash --flash_mode dio --flash_size 4MB --flash_freq 80m 0x0 bin/bootloader.bin 0x8000 bin/partition-table.bin 0xe000 bin/ota_data_initial.bin 0x10000 bin/AtlasLightBoardWiFiLCCTraction.bin'
mkdir /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`
mkdir /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`/bin
mkdir /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`/doc
cp -v $BuildBinaries /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`/bin
cp -v $BuildDocs /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`/doc
echo "$FlashProgram" > /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`/FlashCommand
zip AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`.zip -r /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`
rm -rf /tmp/AtlasLightBoardWiFiLCCTraction-`git rev-parse --short HEAD`

