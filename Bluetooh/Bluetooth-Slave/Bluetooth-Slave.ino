char c;
String readString;
char corLed[4] = "azul"; 

void setup(){
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  while(Serial.available()>0){
    delay(10);
    c = Serial.read();
    readString += c;
  }
  if(readString.length()>0){
    Serial.println(readString);
    if(readString == "c"){
      Serial.println("0");
    }
    else if(readString == "1" || readString.equals("1") || readString.startsWith("1")){
      digitalWrite(9,HIGH);
      //Serial.println("On");
    }
    else if(readString == "0" || readString.equals("0") || readString.startsWith("0")){
      digitalWrite(9,LOW);
      //Serial.println("Off");
    }
    readString =""; 
  }
}
