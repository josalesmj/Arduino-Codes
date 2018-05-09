#include<SoftwareSerial.h>
SoftwareSerial mySerial(10,11);
String command = "";
String str = "";
String andress;
int pinEn = 12;
int btPower = 9;
int flag = HIGH;
void setup(){
  Serial.begin(115200);
  mySerial.begin(38400);
  pinMode(pinEn,OUTPUT);
  pinMode(btPower,OUTPUT);
  digitalWrite(btPower,HIGH);
  delay(100);
  digitalWrite(pinEn,HIGH);
  delay(100);
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
    digitalWrite(pinEn,HIGH);
    delay(400);
    mySerial.write("AT+INQ\r\t");
    if(mySerial.available()){
      while(mySerial.available()){
        str += (char)mySerial.read();
      }
    }
    Serial.println(str);
    if(str.startsWith("+INQ:")){
      andress = str.substring(5,str.length() - 12);
      andress.replace(":",",");
      Serial.print("Andress:");
      Serial.println(andress);
      String aux = "";
      String link = "AT+BIND=" + andress + "\r\t";
      String link1 = "AT+LINK" + andress + "\r\t";
      char link2[link.length()];
      char link3[link.length()];
      link.toCharArray(link2,link.length());
      link1.toCharArray(link3,link1.length());
      mySerial.write("AT+CMODE=1\r\t");
      delay(100);
      mySerial.write(link2);
      delay(100);
      mySerial.write(link3);
      if(mySerial.available()){
      while(mySerial.available()){
        aux += (char)mySerial.read();
      }
      Serial.print("Aux: ");Serial.println(aux);
      flag = !flag;
      }
    }
  }
  else if(flag == LOW){
    digitalWrite(pinEn,LOW);
    delay(100);
   // int n = 8 + andress.length();
  //  char link1[n];// = "AT+LINK=";
//    link.toCharArray(link1,link.length());
    //sprintf(link1,andress);
    //mySerial.write(link1);
    if(mySerial.available()){
      while(mySerial.available()){
        str += (char)mySerial.read();
      }
    }
  }
}
