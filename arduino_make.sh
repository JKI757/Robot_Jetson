#!/bin/sh
arduino-cli compile --fqbn arduino:avr:mega arduino_l298n

arduino-cli upload --port /dev/ttyACM0 --fqbn arduino:avr:mega arduino_l298n
