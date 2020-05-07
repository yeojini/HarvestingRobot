#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2,3);

void setup(){
	Serial.begin(9600);
	BTSerial.begin(9600);
}

void loop(){
	if(Serial.available()){
		BTSerial.write(Serial.read());
	}
}
