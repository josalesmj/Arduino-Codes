#include <VirtualWire.h>

char inData[50];
int newMessage = 0;
void setup(){
  vw_setup(2000);
  vw_set_tx_pin(5);
  Serial.begin(9600);
}

void loop(){
  char inChar;
  byte index = 0;
  char mss[20];
  while(Serial.available() > 1){
    if(index < 49){
      delay(10);
      inChar = Serial.read();
      inData[index] = inChar;
      index++;
      inData[index] = '\0';
    }
    newMessage = 1;
  }
  if(newMessage == 1){
    inData[0] = '-';
    sprintf(mss, "%s", inData);
    for(int i=0;i<10;i++){
      vw_send((uint8_t *)mss, strlen(mss));
      vw_wait_tx();
      Serial.println(mss);
      delay(600);
    }
    newMessage = 0;
  }
}
