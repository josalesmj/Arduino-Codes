#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int relePin = 4;
int ledPin = 2;

boolean ledEstado = LOW;

float tempC = 0;

float temperaturaMaxima = 28;
float temperaturaMinima = 10;

unsigned long lastCall = 0;
unsigned long intervalCall = 2000;

void setup(){
  Serial.begin(115200); //INICIALIZA A SERIAL
  pinMode(relePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  dht.begin(); 
  delay(2000);
}
void loop(){
  tempC = dht.readTemperature();

  if(isnan(tempC)){
    Serial.println(F("Failed to read from DHT sensor!"));
    //PISCA RÁPIDO
    intervalCall = 500;
  }
  else{
    Serial.print("temperatura:");Serial.println(tempC);
    //PISCA LENTO
    intervalCall = 2000;
    verificaTemperatura(tempC);
  }

  if(millis() > lastCall + intervalCall){
    lastCall = millis();
    ledEstado = !ledEstado;
    digitalWrite(ledPin, ledEstado);
  }
}

void verificaTemperatura(float t) {
  if(t >= temperaturaMaxima){
    ligaRele(true);
  }
  else if(t <= temperaturaMinima){
    ligaRele(false);
  }
}

void ligaRele(boolean estado){
  digitalWrite(relePin, estado);
}
