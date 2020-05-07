#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
int val;
int in1 = 6;
int in2 = 7;
int in3 = 11;
int in4 = 12;
int EN1 = 8;
int EN2 = 10;
//intPin=6;
int in5 = 22;
int in6 = 24;
int EN3 = 26;
char data;
SoftwareSerial bluetooth(50, 51);
int count = 0;
int i;
int j;
int k;
void setup() {
	Serial.begin(9600);
	bluetooth.begin(9600);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(in5, OUTPUT);
	pinMode(in6, OUTPUT);
	pinMode(EN3, OUTPUT);

	pinMode(EN1, OUTPUT);
	pinMode(EN2, OUTPUT);
	//pinMode(Pin,OUTPUT);
	myservo.attach(48);
	j = 0;
	val = 0;
	k = 0;
}
void loop() {
	if (bluetooth.available()) {
		data = bluetooth.read();
		Serial.println(data);
	}
	while (k == 0) {
		delay(3000);
		analogWrite(EN2, 255);
		digitalWrite(in3, LOW);
		digitalWrite(in4, HIGH);
		analogWrite(EN1, 255);
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
		delay(1500);
		analogWrite(EN2, 0);
		digitalWrite(in3, LOW);
		digitalWrite(in4, LOW);
		analogWrite(EN1, 0);
		digitalWrite(in1, LOW);
		digitalWrite(in2, LOW);
		k = 1;
	}

	if (data == 'a') {
		while (1) {
			data = 'a';
			analogWrite(EN2, 100);
			digitalWrite(in3, LOW);
			digitalWrite(in4, HIGH);
			analogWrite(EN1, 100);
			digitalWrite(in1, LOW);
			digitalWrite(in2, HIGH);
			delay(30);
			analogWrite(EN2, 0);
			digitalWrite(in3, LOW);
			digitalWrite(in4, LOW);
			analogWrite(EN1, 0);
			digitalWrite(in1, LOW);
			digitalWrite(in2, LOW);
			count = count + 1;
			break;
		}
	}else if(data == 'c') {
		while (1) {
			data = 'c';
			analogWrite(EN2, 100);
			digitalWrite(in3, HIGH);
			digitalWrite(in4, LOW);
			analogWrite(EN1, 100);
			digitalWrite(in1, HIGH);
			digitalWrite(in2, LOW);
			delay(30);

			analogWrite(EN2, 0);
			digitalWrite(in3, LOW);
			digitalWrite(in4, LOW);
			analogWrite(EN1, 0);
			digitalWrite(in1, LOW);
			digitalWrite(in2, LOW);
			count = count - 1;
			break;
		}
	}else if(data == 'b'&&j == 0) {
		val = 0;
		myservo.write(val);
		delay(400);
		while (1) {
			analogWrite(EN3, 255);
			digitalWrite(in5, LOW);
			digitalWrite(in6, HIGH);
			delay(20000);
			analogWrite(EN3, 0);
			digitalWrite(in5, LOW);
			digitalWrite(in6, LOW);
			delay(400);
			break;
		}
		while (1) {
			val = 180;
			myservo.write(val);
			delay(400);

			break;
		}
		while (1) {
			analogWrite(EN3, 255);
			digitalWrite(in5, HIGH);
			digitalWrite(in6, LOW);
			delay(20000);
			analogWrite(EN3, 0);
			digitalWrite(in5, LOW);
			digitalWrite(in6, LOW);
			delay(400);
			break;
		}
		while (1) {
			val = 0;
			myservo.write(val);
			delay(400);
			break;
		}
		i = 0;
		if (count > 0) {
			while (i < count) {
				analogWrite(EN2, 150);
				digitalWrite(in3, HIGH);
				digitalWrite(in4, LOW);
				analogWrite(EN1, 150);
				digitalWrite(in1, HIGH);
				digitalWrite(in2, LOW);

				delay(30);
				analogWrite(EN2, 0);
				digitalWrite(in3, LOW);
				digitalWrite(in4, LOW);
				analogWrite(EN1, 0);
				digitalWrite(in1, LOW);
				digitalWrite(in2, LOW);
				delay(30);
				i = i + 1;
			}
		}else if(count < 0) {
			while (i > count) {
				analogWrite(EN2, 120);
				digitalWrite(in3, LOW);
				digitalWrite(in4, HIGH);
				analogWrite(EN1, 120);
				digitalWrite(in1, LOW);
				digitalWrite(in2, HIGH);
				delay(30);
				analogWrite(EN2, 0);
				digitalWrite(in3, LOW);
				digitalWrite(in4, LOW);
				analogWrite(EN1, 0);
				digitalWrite(in1, LOW);
				digitalWrite(in2, LOW);
				delay(30);
				i = i - 1;
			}
		} count = 0;
		
		j++;

	}
	else if(data == 'd') {
		while (1) {
			data = 'd';
			break;
		}
	}
	if (j >= 20) {
		j = 0;
	}
}
