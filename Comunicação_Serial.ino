#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1

const char* SSID = "SSID";
const char* PASSWORD = "SENHA";

const char* mqttServer = "xxxxxxxxxxxxxxxxx";
const char* mqttUser = "xxxxxxxx";
const char* mqttPassword = "xxxxxxxxxxxx";
const int mqttPort = xxxxx;

WiFiClient espClient;
PubSubClient client(espClient);

char c;
String readString; 

void setup(){
  Serial.begin(115200){
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Coenctado!");
  
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  while(!client.connected()){
    Serial.println("Conectando ao Broker MQTT...");
    if(client.connect("ESP8266Client", mqttUser, mqttPassword )){
      Serial.println("Conectado ao broker MQTT");  
    }
    else{
      Serial.print("falha estado ");
      Serial.print(client.state());
      delay(2000);
    }
  }
 
  //subscreve no tópico
  client.subscribe("Nome do tópico");
}
  
  
void callback(char* topic, byte* payload, unsigned int length){
  payload[length] = '\0';
  String mensagem = String((char*)payload);
    
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  Serial.print(mensagem);
  Serial.println();
  Serial.println("-----------------------");
}
  
void reconect(){
  while(!client.connected()){
    Serial.print("Tentando conectar ao servidor MQTT");
    
    bool conectado = strlen(mqttUser) > 0 ?
                     client.connect("ESP8266Client", mqttUser, mqttPassword) :
                     client.connect("ESP8266Client");
 
    
    if(conectado){
      Serial.println("Conectado!");
      client.subscribe(mqttTopicSub, 1); //QoS 1
    }
    else{
      Serial.println("Falha durante a conexão.Code: ");
      Serial.println( String(client.state()).c_str());
      Serial.println("Tentando novamente em 10 s");
      delay(10000);
    }
  }
}

void loop(){
  if(!client.connected()){
    reconect();
  }
  client.loop();
  
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
