#include <SoftwareSerial.h>

boolean flag = HIGH;
int pinEn = 12;
int btPower = 9;
String command = "";
SoftwareSerial mySerial(10, 11); //RX, TX

void setup(){
  Serial.begin(115200);
  pinMode(pinEn, OUTPUT);  
  pinMode(btPower, OUTPUT);
  
  digitalWrite(btPower, LOW);
  digitalWrite(pinEn, LOW);
  
  /************************************************
  Setting the pins to low is important because 
  in order for us to get into AT mode the key pin
  has to be set to Ground FIRST. Many tutorials out
  there fail to mention this important fact and 
  therefore many people have problems with getting 
  into the AT mode of the HC-05
  ************************************************/
  delay(100);
  digitalWrite(pinEn, HIGH);
  delay(100);

  //Liga o HC-05
  digitalWrite(btPower, HIGH);
  delay(500);
  mySerial.begin(38400);
  
  // Send an "AT" command to the AT (without quotes)
  // if response is OK, then we are connected
  // and ready to program the BT module
  delay(3000);
  mySerial.write("AT+ROLE=0\r\n");
  Serial.println("Aguardando por conexão");
  delay(1000);
  digitalWrite(pinEn,LOW);
  digitalWrite(btPower,LOW);
  delay(500);
  digitalWrite(btPower,HIGH);
  delay(500);
 }

void loop(){
  //Aguardando por ordem
  if(flag == HIGH){
    if(mySerial.available()){
      while(mySerial.available()){
        command += (char)mySerial.read();
      }
      Serial.println(command);  
    }
    if(Serial.available()){
      delay(10);
      mySerial.write(Serial.read());
    }
    command = "";
  }

  else{
    mySerial.write("AT+BIND=98D3,31,F50EEC\r\n");
    Serial.write("AT+BIND=98D3,31,F50EEC\r\n");
    delay(2000);
    mySerial.write("AT+INIT\r\n");
    Serial.write("AT+INIT\r\n");
    delay(3000);
    mySerial.write("AT+INQ\r\n");
    Serial.write("AT+INQ\r\n");
    delay(4000);
    mySerial.write("AT+LINK=98D3,31,F50EEC\r\n");   
    Serial.write("AT+LINK=98D3,31,F50EEC\r\n");   
    delay(4000);    
    
    mySerial.write("on");
    delay(2000);
    mySerial.write("off");
    delay(4000);
    digitalWrite(btPower, LOW);
    digitalWrite(pinEn, LOW);
    delay(100);
    digitalWrite(pinEn, HIGH);
    delay(100);
    digitalWrite(btPower, HIGH);
    Serial.write("Desconectando\r\n");
    delay(4000);
  
  
    mySerial.write("AT+BIND=12,9,139146\r\n");
    Serial.write("AT+BIND=12,9,139146\r\n");
    delay(2000);
    mySerial.write("AT+INIT\r\n");
    Serial.write("AT+INIT\r\n");
    delay(3000);
    mySerial.write("AT+INQ\r\n");
    Serial.write("AT+INQ\r\n");
    delay(4000);
    mySerial.write("AT+LINK=12,9,139146\r\n");   
    Serial.write("AT+LINK=12,9,139146\r\n");   
    delay(4000);    
  
    mySerial.write("on");
    delay(2000);
    mySerial.write("off");
    delay(4000);
    digitalWrite(btPower, LOW);
    digitalWrite(pinEn, LOW);
    delay(100);
    digitalWrite(pinEn, HIGH);
    delay(100);
    digitalWrite(btPower, HIGH);
    Serial.write("Desconectando\r\n");
    delay(4000);
  

    // listen for a response from the HC-05 and write it to the serial monitor
    if (mySerial.available())
      Serial.write(mySerial.read());

    // listen for user input and send it to the HC-05
    if (Serial.available())
      mySerial.write(Serial.read());
  }
}
