# ant-arduino

Arduino library for communicating with ANT radios, with support for nrf51 devices. This library Includes support for the majority of packet types, including: channel config.

## Status

[![Build Status](https://travis-ci.org/cujomalainey/ant-arduino.svg?branch=master)](https://travis-ci.org/cujomalainey/ant-arduino)
[![Coverage Status](https://coveralls.io/repos/github/cujomalainey/ant-arduino/badge.svg?branch=master)](https://coveralls.io/github/cujomalainey/ant-arduino?branch=master)

## News

* 04/21/2016 Project forked from Andrew Wrapp xbee-arduino

## Documentation
Doxygen API documentation is available in the downloads. Unfortunately it is not available online anymore as Git does not support the html mime type as Subversion does

[Developer's Guide](https://github.com/cujomalainey/ant-arduino/blob/wiki/DevelopersGuide.md)

## Example
I have created several sketches of sending/receiving packets with NRF51 ANT radios. You can find these in the examples folder. Here's an example of sending a packet with a NRF51 radio:

```
// Create an ANT object at the top of your sketch
ANT ant = ANT();

// Start the serial port
Serial.begin(9600);
// Tell XBee to use Hardware Serial. It's also possible to use SoftwareSerial
ant.setSerial(Serial);

// Create an array for holding the data you want to send.
uint8_t payload[] = { 'H', 'i' };

// Specify the address of the remote XBee (this is the SH + SL)
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x403e0f30);

// Create a TX Request
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

// Send your request
ant.send(zbTx);
```

See the examples folder for the full source. There are more examples in the download.

To add XBee support to a new sketch, add "#include <ANT.h>" (without quotes) to the top of your sketch. You can also add it by selecting the "sketch" menu, and choosing "Import Library->ANT".

## Hardware

For development and general tinkering I highly recommend using an Arduino that has 2 serial ports, such as the Arduino Leonardo. The reason is the ANT Radio requires serial port access and it is useful to have another serial port available for debugging via the Arduino serial console.

* Arduino Leonardo (recommended)
* Arduino UNO R3 (single serial port)
* Arduino Pro (single serial port)

ANT radios come in multiple models, but this driver is designed to only support the following:

* NRF51
* NRF52

You will need 3.3V regulator and logic shifting to convert from 5V (Arduino) to 3.3V (ANT). The Arduino is 3.3V tolerant.


## Installation
Arduino 1.5 and later

Arduino now includes a library manager for easier library installation. From the Sketch menu select include library->Manage Libraries, then type "ant" in the filter and install.

Prior to Arduino 1.5 installation is a manual

Download a .zip or .tar.gz release from github. Determine the location of your sketchbook by selecting "preferences" on the Arduino menu. Create a "libraries" folder in your sketchbook and unzip the release file in that location.

## Uploading Sketches

Uploading sketches with a Leonardo is as simple as connecting the Arduino to your computer and uploading. When using a single serial port Arduino, such as the UNO, the jumpers on the ANT Radio must be disconnected. Then, after upload, reconnect the lines to have access to the serial port. Always remember to power off the Arduino before moving the jumpers.

## Configuration

To use this library your ANT radio must be loaded with the ANT Network Processor firmware.

## Questions/Feedback

Questions about this project should be posted to http://groups.google.com/group/ant-api?pli=1 Be sure to provide as much detail as possible (e.g. what radios, firmware versions, configuration and code).

## Consulting/Commercial Licenses

If you are looking for commercial support go to thisisant.com
