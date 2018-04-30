#include<SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
String command = "";
String str = "";
int pinEn = 12;
int flag = HIGH;
void setup(){
  Serial.begin(115200);
  mySerial.begin(38400);
  pinMode(pinEn, OUTPUT);
  digitalWrite(pinEn,HIGH);
  delay(1000);
  mySerial.write("AT+INIT\r\t");
  if(mySerial.available()){
    while(mySerial.available()){
      str += (char)mySerial.read();
    }
  }
}
void loop(){
  if(flag == HIGH){
    str = "";
    Serial.println("Tentando...");
    //digitalWrite(pinEn,HIGH);
    delay(1000);
    mySerial.write("AT+INQ\r\t");
    if(mySerial.available()){
      while(mySerial.available()){
        str += (char)mySerial.read();
      }
    }
    Serial.println(str);
  }
  else{
    Serial.println("Tomando um tempo pra descansar...");
    for(int i = 0;i<10;i++){
      Serial.print(10-i);
      delay(1000);
    }
    flag = !flag;
  }
}
