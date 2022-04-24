# SETUP 

## Arduino-CLI

### General

`arduino-cli core update-index`

* List all detected boards: `arduino-cli board list`
* List all available boards: `arduino-cli board listall`


### Install Board

We got: `arduino:avr:nano` as FQBN

`arduino-cli core install arduino:avr` 

Check: `arduino-cli core list`

### Install Libs

arduino-cli lib download NeoGPS
arduino-cli lib download NeoSWSerial



