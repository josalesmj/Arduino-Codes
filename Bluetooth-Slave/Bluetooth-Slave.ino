char buf;
String corLed = "azul"; 
ind ledStatus = 10; //Variável para checar o status do pin24 da placa hc06
void setup(){
  pinMode(9, OUTPUT);
  pinMode(ledStatus,INPUT);
  Serial.begin(9600);
}

void loop(){
  if(digitalRead(ledStatus)==HIGH){
    Serial.write(corLed);
    while(Serial.available() > 0){
      buf = Serial.read();
      if (buf == 'L'){
      digitalWrite(9, HIGH);
      }
      if (buf == 'D'){
        digitalWrite(9, LOW);
      }
    }
  }
}
