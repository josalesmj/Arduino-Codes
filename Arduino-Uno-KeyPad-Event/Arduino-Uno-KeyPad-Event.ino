#include <Keypad.h>                                                // biblioteca Keypad

const byte ROWS = 4;                                               // Keypad 4 linhas
const byte COLS = 4;                                               // Keypad 4 colunas

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}                                             // alterações *=F e #=E
};

byte rowPins[ROWS] = {3, 4, 5, 6};                               // portas D11 a D8 conectadas nas linhas do Keypad
byte colPins[COLS] = {8, 9, 10, 11};                                 // portas D7 a D4  conectadas nas colunas do Keypad
//{12, 11, 13, 2

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);  // inicializa o Keypad


bool change = false;
unsigned long lastCall = 0;
boolean flag = HIGH;

void setup(){
  Serial.begin(115200);                    // console serial 9600 Bps 
  pinMode(LED_BUILTIN, OUTPUT);
  keypad.addEventListener(keypadEvent);
  
}

void loop(){
  char key = keypad.getKey();                  // leitura da tecla pressionada no Keypad
  //if(customKey){
    //Serial.println(customKey);
  //}
  //delay(20);
  if(millis() - lastCall >= 1000){
    lastCall = millis();
    flag = !flag;
    digitalWrite(LED_BUILTIN, flag);  
  }
  if (change == true) getnum();
}

void keypadEvent(KeypadEvent key){
  switch(keypad.getState()){
    case PRESSED:
    String s = (String)key;
    
      Serial.println(s);
      if(key == 'A'){
        change = true;
      }
      else{
        
      }
    break;
  }
}

void getnum(){
  Serial.println("Esperando apertar algo....");
  char key = keypad.waitForKey();

  if(key) Serial.println(key);
  change = false;
}

void handleState(){
  
}
