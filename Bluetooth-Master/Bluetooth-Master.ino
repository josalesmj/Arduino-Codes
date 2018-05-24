#include<SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);//RX,TX
String str = "";
int pinEn = 12;
int btPower = 9;
char c = 'a';
int cont = -1;
int cont1 = 0;

void setup(){
  Serial.begin(115200);
  mySerial.begin(38400);
  pinMode(pinEn, OUTPUT);
  pinMode(btPower, OUTPUT);
  digitalWrite(btPower, HIGH);
  delay(100);
  digitalWrite(pinEn, HIGH);
  delay(2000);
  mySerial.write("AT+INIT\r\t");
  if (mySerial.available()) {
    while (mySerial.available()) {
      str += (char)mySerial.read();
    }
  }
}

void loop(){
  //Variáveis para trabalhar com o retorno do comando AT+INQ
  cont = -1;
  cont1 = 0;
  str = "";
  delay(400);//Quando tirei esse tempo deixou de funcionar
  Serial.println("Enviando AT+INQ...");
  mySerial.write("AT+INQ\r\t");//Envia AT+INQ para o bluetooth
   
  //while para aguardar receber mais de um endereço. Precisando melhorar essa lógica.
  while(str.length()<50){
    if(mySerial.available()){
      while (mySerial.available()){
        str += (char)mySerial.read();
      }
    }
  }
    
  //Diversas tentativas para limpar a string str de todas as "new line"
  str.replace("\n","\\");
  str.replace("\r","");
  str.replace("\t","");
  str.replace("\\","");

  //imprime a string str
  Serial.println(str);

  //Lógica para contar quantos dispositivos bluetooth encontrou
  for(int i=0;i<str.length()-4;i++){
    String s = str.substring(i, i+4);
    if(s.equals("+INQ"))
      cont1++;
  }
  Serial.print("Número de endereços encontrados: ");Serial.println(cont1);

  //Cria um array de string onde cada posição irá receber um endereço de String
  String address[cont1];

  //Se str começa com "OK", remove o OK de str
  if(str.startsWith("OK")){
    str = str.substring(3, str.length());
 
    //Forma esperada de str.
    //+INQ:12:9:139146,1F00,7FFF+INQ:98D3:31:F50EEC,1F00,7FFF

    //Lógica para extrair cada endereço contido na string str para uma posição do array address
    for(int i=0;i<cont1;i++){
      int aux = 0;

      //cria um array de char
      char strArray[str.length()];
      //Passa todo o conteúdo da string str para o array de char
      str.toCharArray(strArray,str.length());

      //Aqui onde a mágica acontece...
      do{
        cont++;
        c = strArray[cont];
        if(c == 'Q')
          aux = cont;
      }while(c != '+' && cont<str.length());

      //Após detectar alguns char chave, passa o endereço para a posição address da forma que devemos mandar para o HC-05
      address[i] = str.substring(aux + 2, cont - 10);
      address[i].replace(":",","); 
      }
    }

    //Imprime os endereços na tela
    for(int i =0;i<cont1;i++){
      Serial.print(i+1);Serial.print("º Endereço:");Serial.println(address[i]);
    }
    Serial.print("\n\n");
}
