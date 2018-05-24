#include<SoftwareSerial.h>
/*
 * HC-06: 98D3,31,F50EEC
 * linvor: 12,9,139146
*/
SoftwareSerial mySerial(10, 11);
String command = "";
String str = "";
String andress;
int pinEn = 12;
int btPower = 9;
int flag = HIGH;

void setup(){
  Serial.begin(115200);
  mySerial.begin(38400);
  pinMode(pinEn, OUTPUT);
  pinMode(btPower, OUTPUT);
  digitalWrite(btPower, HIGH);
  digitalWrite(pinEn, HIGH);
  delay(2000);
  if (mySerial.available()) {
    while (mySerial.available()) {
      str += (char)mySerial.read();
    }
  }
}

void loop(){
  mySerial.write("AT+BIND=12,9,139146\r\t");
  delay(2000);
  mySerial.write("AT+INIT\r\t");
  delay(2000);
  //mySerial.write("AT+INQ\r\t");
  //delay(3000);
  mySerial.write("AT+LINK=12,9,139146\r\t");
  delay(3000);
  digitalWrite(pinEn,LOW);
  delay(2000);
  
  int i = 0;
  while(i<5){
  mySerial.println("on");
  delay(2000);
  mySerial.println("off");
  delay(2000);
  i++;
  }
  //Alteração daqui pra baixo.
  digitalWrite(pinEn, HIGH);
  delay(2000);
  mySerial.write("AT+DISC\r\t");
  delay(2000);
  mySerial.write("AT+BIND=98D3,31,F50EEC\r\t");
  delay(2000);
  digitalWrite("AT+INIT\r\t");
  delay(2000);
  mySerial.write("AT+LINK=98D3,31,F50EEC\r\t");
  delay(2000);
  digitalWrite(pinEn,LOW);
  delay(2000);
  
  i = 0;
  while(i<5){
  mySerial.println("on");
  delay(2000);
  mySerial.println("off");
  delay(2000);
  i++;
  }
}