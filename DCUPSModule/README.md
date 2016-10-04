# Early steps towards IoT

* ESP8266
* Arduino Uno R3 (sometimes used as FT232 USB to TTL to program ES8266)

For adding any device to internet, we need a connectivity to internet. The most straight forward way to do that is WiFi via a WiFi home router. ESP8266 is a cheap, general purpose RF board with 802.11 a/b/g/n protocol stack programable board which can make your device connect to internet.

To program, sketch comes in handy. Download the ESP8266 board in sketch and connect the modules Rx and Tx pins to Arduino Rx and Tx port also connect VCC and 3rd pin to +3.3 and ground to ground. Now, we can plugin the Arduino USB to latpop. After chosing the correct board and port, open the serial monitor and start issuing the commands. You need to select appropriate baud rate, all new boards uses 115200 as baud rate, while older firmwares may still use 9600.

There is a decent set of AT commands which can be used to program ESP8266 board. It can then be used either as a server or a client.

