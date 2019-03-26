char c;
String readString; 

void setup(){
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop(){
  while(Serial.available()>0){
    delay(10);
    c = Serial.read();
    readString += c;
  }
  if(readString.lenght() > 0){
    if(readString.equalsIgnoreCase("Comando_1")){
      Serial.println("Resposta_1");
    }
    else if(readString.equalsIgnoreCase("Comando_2")){
      Serial.println("Resposta_2");
    }
    else if(readString.equalsIgnoreCase("Comando_3")){
      Serial.println("Resposta_3");
    }
  }
}
