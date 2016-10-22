# Early steps towards IoT
[Ref to pic]

## Internet access for devices

### Things you will need

* [ESP8266 - ESP-1](http://amzn.to/2eQHQRW)
* [Arduino Uno R3](http://amzn.to/2eQHwTv) (sometimes used as [FT232 USB to TTL](http://amzn.to/2dWHpRk) to program ES8266 directly)
* [8 channel relay controller](http://amzn.to/2esLa1v)
* [Jumper wires](http://amzn.to/2esMrW9)
* Bread board

For adding any device to internet, we need a connectivity to internet. The most straight forward way to do that is WiFi via a WiFi home router. ESP8266 is a cheap, general purpose RF board with 802.11 a/b/g/n protocol stack programable board which can make your device connect to internet.

To program, sketch comes in handy. Download the ESP8266 board in sketch and connect the modules Rx and Tx pins to Arduino Rx and Tx port also connect VCC and CH_PD pin to +3.3 and ground to ground. A thing to note is ESP8266 works on 3.2v, we should use a voltage divider while connecting to the Rx of arduino. Please refer to the diagram below. 

Now, we can plugin the Arduino USB to latpop. After chosing the correct board and port, open the serial monitor and start issuing the commands. You need to select appropriate baud rate, all new boards uses 115200 as baud rate, while older firmwares may still use 9600.

There is a decent set of AT commands which can be used to program ESP8266 board. It can then be used either as a server or a client.

ESP8266 ESP-1 in itself is capable to control upto 3 devices using its 3 pins, to address more you either need to opt for more advanced options. I have recursed to use it in combination with Arduino UNO. For other (more pricier options) see [this link](https://retro.moe/2016/03/27/c64-remote-controller-nodemcu-vs-adafruit-huzzah-vs-sparkfun-thing-vs/)

## How to make a device IoT enabled

I am considering the devices which can be controlled using circuit switches. The choice of a generic switch is one which can take up circuits with potential difference from 1.5v to 440v. With these we can cover wide variety of home electrical equipments. For any other special equipment we can device a analog/digital circuit which can be driven by our Arduino board, but that will be highly specific and maybe I can discuss about that in some of my future blogs.

So, the setup is like this -

1. Arduino UNO as a generic slave controller
2. ESP8266 ESP-1 as a cheap wifi interface card for UNO
3. 8 channel optocoupler relay controller to control device switching

[Refer to pic]

Once the connections are made, we need to program our arduino. Working code for this can be cloned from [here](https://github.com/meetpraveen/HomeAutoSecure/tree/master/SlaveControllers/arduino). The code does the following -

1. Initialize serial channel with ESP8266
2. Discover wifi APs and connect to the one provided
3. Send the assigned IP to Serial interface of UNO so that it can be printed in Serial Monitor
4. Start listening to port 80 for TCP requests
5. In a loop, reads messages on port 80 in a multiclient mode and process it according to this logic
  a. If message url has query param in the format deviceN=[1 or 0], switch OFF or ON the Nth relay and return back the status of all relay switches as JSON
  
Viola, you can now send REST like request to our Arduino and it can control the device/devices by a combination of 8 programmable switches :)

[Ref](https://www.baldengineer.com/four-esp8266-gotchas.html)
