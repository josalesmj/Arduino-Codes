#include <SoftwareSerial.h>

boolean flag = HIGH;
int pinEn = 12;
int btPower = 9;
String str = "";
SoftwareSerial mySerial(10, 11); //RX, TX
  String address = "";
  String acao = "";


void setup(){
  Serial.begin(115200);
  pinMode(pinEn, OUTPUT);  
  pinMode(btPower, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  putInSlaveMode();
  Serial.println("Aguardando por conexão");
 }

void loop(){
  str = "";
  //Aguardando por ordem
  if(flag == HIGH){
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    if(mySerial.available()){
      while(mySerial.available()){
        str += (char)mySerial.read();
      }
      Serial.println(str);  
    }
    if(Serial.available()){
      delay(10);
      mySerial.write(Serial.read());
    }
    if(str.startsWith("comd:")){
      address = str.substring(5,str.length()-2);
      acao = str.substring(str.length()-1);
      Serial.print("Address: ");Serial.println(address);
      Serial.print("Açao: ");Serial.println(acao);
      flag = !flag;
    }
  }
  else{
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    comandaDevice(address,acao);
    delay(500);
  }
}

void comandaDevice(String address,String acao){
  putInMasterMode();
  mySerial.print("AT+CMODE=1\r\n");
  delay(500);
  String aux = "AT+BIND=" + address + "\r\n";
  mySerial.print(aux);
  Serial.print(aux);
  waitForResponse();
  mySerial.print("AT+INIT\r\n");
  Serial.println("AT+INIT\r\n");
  waitForResponse();
  mySerial.print("AT+INQ\r\n");
  Serial.println("AT+INQ\r\n");
  waitForResponse();
  aux = "AT+LINK=" + address + "\r\n";
  mySerial.print(aux);
  Serial.println(aux);
  waitForResponse();
  acao += "\r\n";
  mySerial.print(acao);
  waitForResponse();
  digitalWrite(btPower, LOW);
  digitalWrite(pinEn, LOW);
  delay(100);
  digitalWrite(pinEn, HIGH);
  delay(100);
  digitalWrite(btPower, HIGH);
  Serial.println("Desconectando");
  delay(1000);
  putInSlaveMode();
  flag = !flag;
}
void putInATCommands(){
  digitalWrite(btPower,LOW);
  digitalWrite(pinEn,LOW);
  delay(100);
  digitalWrite(pinEn,HIGH);
  delay(100);
  digitalWrite(btPower,HIGH);
  delay(500);
  mySerial.begin(38400);
  delay(3000);
}

void putInMasterMode(){
  putInATCommands();
  mySerial.write("AT+ROLE=1\r\n");
  delay(500);
  mySerial.write("AT+CMODE=0\r\n");
  digitalWrite(pinEn,LOW);
  digitalWrite(btPower,LOW);
  delay(500);
  digitalWrite(btPower,HIGH);
  delay(500);
}
void putInSlaveMode(){
  putInATCommands();
  mySerial.write("AT+ROLE=0\r\n");
  delay(500);
  digitalWrite(pinEn,LOW);
  digitalWrite(btPower,LOW);
  delay(500);
  digitalWrite(btPower,HIGH);
  delay(500);
}
void waitForResponse(){
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  Serial.write("\n");
}
