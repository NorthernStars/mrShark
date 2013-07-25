#!/bin/bash
avrdude -c usbasp -p m48 -P usb -B 3 -e -U flash:w:./Release/Motortest.hex