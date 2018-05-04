char c;
String readString;
char corLed[4] = "azul"; 
void setup(){
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  //Serial.write("AT\r\t"); Outra possibilidade, chegar se retorna "OK" para o comando AT, o que significaria não estar conectado. 
  //str = Serial.read();
  //if(!str.equals("OK"));{
  while(Serial.available()>0){
    delay(3);
    c = Serial.read();
    readString += c;
  }
  if(readString.length()>0){
    Serial.println(readString);
    if(readString == "cor?"){
      Serial.println(corLed);
    }
    else if(readString == "on"){
      digitalWrite(9,HIGH);
      Serial.println("On");
    }
    else if(readString == "off"){
      digitalWrite(9,LOW);
      Serial.println("Off");
    }
    readString =""; 
  }
}
