#!/usr/bin/env bash

sudo esptool.py --before default_reset --after hard_reset --baud 460800 --port /dev/ttyUSB0 --chip esp32 write_flash -z --flash_size detect 0x10000 $PWD/.esphome/build/aquamat/.pioenvs/aquamat/firmware.bin 0x1000 ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/bin/bootloader_dio_40m.bin 0x8000 $PWD/.esphome/build/aquamat/.pioenvs/aquamat/partitions.bin 0xe000 ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin

