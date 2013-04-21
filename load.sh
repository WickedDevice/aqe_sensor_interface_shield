#!/bin/bash
sudo avrdude -p t88 -c avrispmkII -P usb -u -U efuse:w:0xff:m
sleep 2
sudo avrdude -p t88 -c avrispmkII -P usb -u -U hfuse:w:0xdf:m
sleep 2
sudo avrdude -p t88 -c avrispmkII -P usb -u -U lfuse:w:0xee:m
sleep 2
sudo avrdude -p t88 -c avrispmkII -e -P usb -U flash:w:aqe_sensor_interface_shield.hex
sleep 2
sudo avrdude -p t88 -c avrispmkII -P usb -U eeprom:w:aqe_sensor_interface_shield.eep
