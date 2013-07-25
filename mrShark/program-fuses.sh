#!/bin/bash
avrdude -c usbasp -p m48 -P usb -B 3 -e -U lfuse:w:0xfb:m -U hfuse:w:0xde:m