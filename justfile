#!/usr/bin/env -S just --justfile


PORT := env("PORT", "/dev/ttyACM0")
BOARD := env("BOARD", "lgt8fx:avr:328")


build:
    arduino-cli compile --fqbn "{{BOARD}}"

upload:
    arduino-cli upload --port "{{PORT}}" --fqbn "{{BOARD}}"

install-libs:
    arduino-cli lib install "EncButton@3.7.3"
    arduino-cli lib install "GyverTM1637@1.4.2"
