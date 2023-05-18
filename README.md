# ant-arduino

Arduino library for communicating with ANT radios, with support for nRF51 devices. This library Includes support for the majority of packet types.

## Status

[![Build Status](https://travis-ci.org/cujomalainey/ant-arduino.svg?branch=master)](https://travis-ci.org/cujomalainey/ant-arduino)
[![Test Status](https://img.shields.io/circleci/build/github/cujomalainey/ant-arduino?label=test)](https://circleci.com/gh/cujomalainey/ant-arduino)

## News

* 06/28/2020 ant-arduino v2.0.0 released with mbed support
* 10/01/2017 [Antplus-arduino](https://github.com/cujomalainey/antplus-arduino) released
* 09/30/2017 Callback system complete, v1.0.0 released
* 09/10/2017 System refactor complete
* 12/26/2016 More examples and Tx added
* 06/08/2016 Initial Experimental Rx only release
* 04/21/2016 Project forked from Andrew Wrapp xbee-arduino

## Roadmap

* Add support for Zephyr and ESPIDF
* Add support for SPI interface

[Developer's Guide](https://github.com/cujomalainey/ant-arduino/wiki/Developer's-Guide)

## Example
I have created several sketches of sending/receiving packets with NRF51 ANT radios. You can find these in the examples folder. Here's an example of configuring a channel with a NRF51 radio:

```
// Create an ANT object at the top of your sketch
ANT ant = ANT();

// Start the serial port
Serial.begin(9600);
// Tell ANT to use Hardware Serial. It's also possible to use SoftwareSerial
ant.setSerial(Serial);

AssignChannel ac;
ResetSystem rs;
SetNetworkKey snk;
ChannelId ci;
ChannelPeriod cp;
ChannelRfFrequency crf;
OpenChannel oc;

// Set Network Key, defaults to public, if you want the ANT+ key you need to get it from thisisant.com, DO NOT PUBLISH IT
snk = SetNetworkKey();
snk.setNetwork(0);
snk.setKey((uint8_t*)NETWORK_KEY);
ant.send(snk);

// Assign the channel and its type
ac = AssignChannel();
ac.setChannel(0);
ac.setChannelType(0);
ac.setChannelNetwork(0);
ant.send(ac);

// Assign the Channel IDs (these are all wildcarded values) (if you are using ANT+ see the profile for settings)
ci = ChannelId();
ci.setChannel(0);
ci.setDeviceNumber(0);
ci.setDeviceType(0);
ci.setTransmissionType(0);
ant.send(ci);

// Set the channel period (if you are using ANT+ see the profile for settings)
cp = ChannelPeriod();
cp.setChannel(0);
cp.setPeriod(1111);
ant.send(cp);

crf = ChannelRfFrequency();
crf.setChannel(0);
crf.setRfFrequency(0);
ant.send(crf);

// open the channel
oc = OpenChannel();
oc.setChannel(0);
ant.send(oc);

// Wait for the responses
```

See the examples folder for the full source. There are more examples in the download.

To add ANT support to a new sketch, add "#include <ANT.h>" (without quotes) to the top of your sketch. You can also add it by selecting the "sketch" menu, and choosing "Import Library->ANT".

## Hardware

### Internal Radio usage

If you are a more advanced tinkerer you can attempt to buy an ANT ready micro controller (such as the [adafruit nrf52 express](https://www.adafruit.com/product/4062)) you can load the board with the ANT softdevice and still use this library. Note: this does carry an element of risk. If you load a bad bootloader and brick your board and don't have a [programmer](https://www.adafruit.com/product/3571) handy then you will not be able to recover it till you get a programmer. [Orrmany](https://github.com/orrmany) carries two repos that are example templates for the adafruit nrf52 express ([bootloader](https://github.com/orrmany/Adafruit_nRF52_Bootloader/tree/s340-for-nrf52840-Feather) and [BSP](https://github.com/orrmany/Adafruit_nRF52_Arduino/tree/adding-S340-to-nrf52840-Feather).) You still need to added the headers and softdevice file yourself locally as Dynastream does not allow redistribution of the ANT softdevice.

### External Radio usage

For development and general tinkering I highly recommend using an Arduino that has 2 serial ports, such as the Arduino Leonardo. The reason is the ANT Radio requires serial port access and it is useful to have another serial port available for debugging via the Arduino serial console. Also it is easier to use a 3.3V arduino than to use a level shifter

* Teensy 3.2
* Pro Mini 3.3V
* Trinket 3.3V

ANT radios come in multiple models, but this driver is designed to only support the following:

* nRF51
* nRF52

You will need 3.3V regulator and logic shifting to convert from 5V (Arduino) to 3.3V (ANT). The Arduino is 3.3V tolerant.

## Installation
Arduino 1.5 and later

Arduino now includes a library manager for easier library installation. From the Sketch menu select include library->Manage Libraries, then type "ant-arduino" in the filter and install.

Prior to Arduino 1.5 installation is a manual

Download a .zip or .tar.gz release from github. Determine the location of your sketchbook by selecting "preferences" on the Arduino menu. Create a "libraries" folder in your sketchbook and unzip the release file in that location.

If you are using platformio you can install the library by running
``` platformio lib install 353 ```

## Uploading Sketches

Uploading sketches with a Leonardo is as simple as connecting the Arduino to your computer and uploading. When using a single serial port Arduino, such as the Pro Mini (3.3V), the jumpers on the ANT Radio must be disconnected. Then, after upload, reconnect the lines to have access to the serial port. Always remember to power off the Arduino before moving the jumpers.

## Configuration

To use this library your ANT radio must be loaded with the ANT Network Processor firmware. See Wiki for recommended wiring.

## Questions/Feedback

Questions about this project should be posted to Github Discussions Be sure to provide as much detail as possible (e.g. what radios, firmware versions, configuration and code).

## Consulting/Commercial Licenses
At the current time there is zero support for commercial usage. Contact me via email if you are looking to use this code commercially.

If you are looking for commercial support for ANT radios go to [thisisant.com](http://thisisant.com)
