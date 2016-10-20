/*
Slave controller main routine. Exposes REST like GET API with query params <code>d<x>=[1,0]</code>
The api has a side effect of switching on or off the particular device and returns back a json with
all device status as follows -
<code>[{"d1":1},{"d2":1},{"d3":1},{"d4":0},{"d5":0},{"d6":0},{"d7":0},{"d8":0}]</code>
 */

#define SSID      "Praveen ACT"
#define PASSWORD  "8041693017"
#define NO_OF_DEVICES 8

#include <uartWIFIUNO.h>
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include "StringClass.h"

template<typename T> void PROGMEM_readAnything(const T * sce, T& dest) {
	memcpy_P(&dest, sce, sizeof(T));
}

template<typename T> T PROGMEM_getAnything(const T * sce) {
	static T temp;
	memcpy_P(&temp, sce, sizeof(T));
	return temp;
}

const StringClass::Constants StringClass::Messages[8] PROGMEM = {
		  {{'{','\"','d','1','\"',':','1','}','\0'}, {'{','\"','d','1','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','1','=','1','\0'}, {'G','E','T',' ','/','?','d','1','=','0','\0'}},
		  {{'{','\"','d','2','\"',':','1','}','\0'}, {'{','\"','d','2','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','2','=','1','\0'}, {'G','E','T',' ','/','?','d','2','=','0','\0'}},
		  {{'{','\"','d','3','\"',':','1','}','\0'}, {'{','\"','d','3','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','3','=','1','\0'}, {'G','E','T',' ','/','?','d','3','=','0','\0'}},
		  {{'{','\"','d','4','\"',':','1','}','\0'}, {'{','\"','d','4','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','4','=','1','\0'}, {'G','E','T',' ','/','?','d','4','=','0','\0'}},
		  {{'{','\"','d','5','\"',':','1','}','\0'}, {'{','\"','d','5','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','5','=','1','\0'}, {'G','E','T',' ','/','?','d','5','=','0','\0'}},
		  {{'{','\"','d','6','\"',':','1','}','\0'}, {'{','\"','d','6','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','6','=','1','\0'}, {'G','E','T',' ','/','?','d','6','=','0','\0'}},
		  {{'{','\"','d','7','\"',':','1','}','\0'}, {'{','\"','d','7','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','7','=','1','\0'}, {'G','E','T',' ','/','?','d','7','=','0','\0'}},
		  {{'{','\"','d','8','\"',':','1','}','\0'}, {'{','\"','d','8','\"',':','0','}','\0'}, {'G','E','T',' ', '/', '?','d','8','=','1','\0'}, {'G','E','T',' ','/','?','d','8','=','0','\0'}}
};

template<typename T, size_t N> size_t ArraySize(T (&)[N]) {
	return N;
}

WIFIUNO wifi;
extern int chlID;

// set pin numbers:
const int ledPin = 13; // the number of the LED pin
const int relay[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };

boolean device[8];

void setup() {

	pinMode(ledPin, OUTPUT);

	for (int i = 0; i < 8; i++) {
		pinMode(relay[i], OUTPUT);
		device[i] = false;
		digitalWrite(relay[i], HIGH);
	}

	if (!wifi.begin()) {
		DebugSerial.println("Wifi begin failed");
	}

	if (!wifi.Initialize(STA, SSID, PASSWORD)) {
		DebugSerial.println("Wifi init failed");
	}

	DebugSerial.println(wifi.showIP());

	wifi.confMux(1);
	if (wifi.confServer(1, 80)) {
		DebugSerial.println("Server is set up");
	}
}

void loop() {
	char buf[500];
	int iLen = wifi.ReceiveMessage(buf);
	if (iLen > 0) {
		String responses = "[";
		delay(300);
		for (int i = 0; i < 8; i++) {
			if (responses.length() > 2)
				responses += ",";
			StringClass::Constants request = PROGMEM_getAnything(&StringClass::Messages[i]);
			DebugSerial.print(buf);
			DebugSerial.println(request.requestOn);
			if (strncmp(buf, request.requestOn, 10) == 0) {
				Serial.println("RELAY 1 ON");
				digitalWrite(relay[i], LOW);
				device[i] = true;
				responses += request.responseOn;
			} else if (strncmp(buf, request.requestOff, 10) == 0) {
				Serial.println("RELAY 1 OFF");
				digitalWrite(relay[i], HIGH);
				device[i] = false;
				responses += request.responseOff;
			} else if (device[i]) {
				responses += request.responseOn;
			} else if (!device[i]) {
				responses += request.responseOff;
			}
		}
		responses += ']';
		DebugSerial.println(responses);
		wifi.Send(chlID, responses);
		delay(200);
		wifi.closeMux(chlID);
	}
	delay(300);
}
