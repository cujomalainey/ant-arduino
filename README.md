# ant-arduino

Arduino library for communicating with ANT radios, with support for nrf51 devices. This library Includes support for the majority of packet types, including: channel config.


## News

* 04/21/2016 Project forked from Andrew Wrapp xbee-arduino

## Documentation
Doxygen API documentation is available in the downloads. Unfortunately it is not available online anymore as Git does not support the html mime type as Subversion does

[Developer's Guide](https://github.com/cujomalainey/ant-arduino/blob/wiki/DevelopersGuide.md)

## Example
I have created several sketches of sending/receiving packets with Series 1 and 2 XBee radios. You can find these in the examples folder. Here's an example of sending a packet with a Series 2 radio:

```
// Create an ANT object at the top of your sketch
ANT ant = ANT();

// Start the serial port
Serial.begin(9600);
// Tell XBee to use Hardware Serial. It's also possible to use SoftwareSerial
xbee.setSerial(Serial);

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

See the XBee API project for Arduino < - > Computer communication.

To add XBee support to a new sketch, add "#include <XBee.h>" (without quotes) to the top of your sketch. You can also add it by selecting the "sketch" menu, and choosing "Import Library->XBee".

## Hardware

For development and general tinkering I highly recommend using an Arduino that has 2 serial ports, such as the Arduino Leonardo. The reason is the XBee requires serial port access and it is useful to have another serial port available for debugging via the Arduino serial console.

* Arduino Leonardo (recommended)
* Arduino UNO R3 (single serial port)
* Arduino Pro (single serial port)

XBee radios come in two models: Series 1 (S1) and Series 2 (S2). Series 1 are the best choice for most people as they are the easiest to configure. Series 2 XBee radios feature ZigBee and require a firmware update to use this software. Series 1 and 2 are not compatible with each other.

* XBee Series 1
* XBee Series 2 (ZigBee)

The Arduino XBee Shield is the easiest option for connecting the XBee to an Arduino. You can find XBee Shields from several vendors and even on ebay. Keep in mind if you select the SparkFun XBee Shield, it requires soldering headers (not included) to connect to an Arduino board.

If not using an XBee shield you'll need a 3.3V regulator and logic shifting to convert from 5V (Arduino) to 3.3V (XBee). The Arduino is 3.3V tolerant.

An XBee Explorer is highly recommended for updating firmware and configuring the radio. This is also useful for interfacing an XBee with a computer. If you are using Series 2 radios you'll need an XBee Explorer to upload API firmware to the radio, via X-CTU (they ship with AT firmware).


## Installation
Arduino 1.5 and later

Arduino now includes a library manager for easier library installation. From the Sketch menu select include library->Manage Libraries, then type "xbee" in the filter and install.

Prior to Arduino 1.5 installation is a manual

Download a .zip or .tar.gz release from github. Determine the location of your sketchbook by selecting "preferences" on the Arduino menu. Create a "libraries" folder in your sketchbook and unzip the release file in that location.

## Uploading Sketches

Uploading sketches with a Leonardo is as simple as connecting the Arduino to your computer and uploading. When using a single serial port Arduino, such as the UNO, the jumpers on the XBee Shield must be set to USB. Then, after upload, set back to the XBee position for the XBee to have access to the serial port. Always remember to power off the Arduino before moving the jumpers.

## Configuration

To use this library your XBee must be configured in API mode (AP=2). Take a look at this for information on configuring your radios to form a network.

## Questions/Feedback

Questions about this project should be posted to http://groups.google.com/group/xbee-api?pli=1 Be sure to provide as much detail as possible (e.g. what radios s1 or s2, firmware versions, configuration and code).

## Consulting/Commercial Licenses

I'm available for consulting to assist businesses or entrepreneurs that need help getting their projects up and running. I can also provide a commercial license for situations where you need to distribute code to clients/third parties that would otherwise conflict with GPL. For these matters I can be contacted at andrew.rapp [at] gmail.
