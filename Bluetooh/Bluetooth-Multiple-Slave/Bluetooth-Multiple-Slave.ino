/**
 * Código desenvolvido para realizar o comando de dispositivos Bluetooth através de um dispositivo Bluetooth central
 * autor Jó Sales
 */
 
#include<SoftwareSerial.h>//Inclui a biblioteca SoftwareSerial.

boolean flag = HIGH; 
int pinEn = 12;
int btPower = 9;
String str = "";
SoftwareSerial mySerial(10, 11);//Cria uma comunicação serial nos pinos 10 e 11. 
String address = "";
String acao = "";

void setup(){
  Serial.begin(115200);//Inicia a comunicação Serial. 
  pinMode(pinEn, OUTPUT);
  pinMode(btPower, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  putInSlaveMode();//Chama a função putInSlaveMode
  Serial.println("Aguardando por conexão");
 }

void loop(){//Rotina que irá ficar repetindo
  str = "";
  //A variável flag iniciará como HIGH
  if(flag == HIGH){
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    if(mySerial.available()){//Verifica se há dados vindo pela serial criada
      while(mySerial.available()){//Enquanto estiver dados vindo pela serial criada
        str += (char)mySerial.read();//Recebe os dados e concatena na string str
      }
      Serial.println(str);
    }
    if(Serial.available()){
      delay(10);
      mySerial.write(Serial.read());
    }
    if(str.startsWith("comd:")){//Verifica se o dado recebido inicia com "comd:"
      //Divide a string em duas substring
      address = str.substring(5,str.length()-2); 
      acao = str.substring(str.length()-1);
      Serial.print("Address: ");Serial.println(address);
      Serial.print("Açao: ");Serial.println(acao);
      flag = !flag;//Inverte o valor de flag
    }
  }
  //Agora flag esteja com valor LOW
  else{
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    //Chama função comandaDevide passando duas strings
    comandaDevice(address,acao);
    delay(500);
  }
}

void comandaDevice(String address,String acao){
  //Função responsável por se conectar ao dispositivo em específico e comandá-lo
  putInMasterMode();//Configura HC-05 como mestre
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
  putInSlaveMode();//Configura o HC-05 como escravo
  flag = !flag;//Inverte o valor da variável flag
}

void putInATCommands(){//Configura o módulo para receber comandos AT.
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

void putInMasterMode(){//Configura módulo como mestre.
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

void putInSlaveMode(){//Configura o comando como escravo.
  putInATCommands();
  mySerial.write("AT+ROLE=0\r\n");
  delay(500);
  digitalWrite(pinEn,LOW);
  digitalWrite(btPower,LOW);
  delay(500);
  digitalWrite(btPower,HIGH);
  delay(500);
}

void waitForResponse(){//Aguarda pela resposta do módulo
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  Serial.write("\n");
}
