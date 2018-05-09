#include <SoftwareSerial.h>
int pinEn = 12;   
int btPower = 9;
SoftwareSerial mySerial(10, 11); // RX, TX  
String command = ""; 
   
void setup(){  
  //Inicia a serial  
  pinMode(pinEn,OUTPUT);
  pinMode(btPower,OUTPUT);
  digitalWrite(btPower,HIGH);
  digitalWrite(pinEn,HIGH);
  delay(3000);
  Serial.begin(115200);  
  Serial.println("Digite os comandos AT :");  
  mySerial.begin(38400);  
}  
   
void loop(){
  if (mySerial.available()){  
     while(mySerial.available()){
      command += (char)mySerial.read();  
     }  
   Serial.println(command);  
   command = "";
  }  
  if (Serial.available()){  
    delay(10);
    mySerial.write(Serial.read());  
  }  
}
