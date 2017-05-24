#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include "Definitions.h"

char buf_data[200]    = {0};
uint8_t current_state = IDLE;
uint8_t next_state    = IDLE;


SoftwareSerial sw_serial(SL_RX, SL_TX, false, 256);
WiFiClient wifi_client;

esp_state FSM[NUM_STATES] = {
  {&Idle_handler},           //IDLE
  {&Starting_handler},       //STARTING
  {&Stopping_handler},       //STOPPING
  {&On_handler}              //ON
};

void setup() {
  Serial.begin(9600);
  sw_serial.begin(38400);
  Wifi_init();
  
}

void loop() {
  next_state    = FSM[current_state].State_handler();
  current_state = next_state;
  Serial.print("Current state: ");
  Serial.println(current_state);
  delay(2000);
  
}



void Wifi_init(){

  byte ledStatus = LOW;
  Serial.println();
  Serial.println("Connecting to: " + String(WiFiSSID));

  IPAddress ip(192, 168, 43, 36);
  IPAddress gateway(192, 168, 43, 1); 
  IPAddress subnet(255, 255, 255, 0); 
  
  /*
  IPAddress ip(192, 168, 1, 36);
  IPAddress gateway(192, 168, 1, 1); 
  IPAddress subnet(255, 255, 255, 0); 
  */
  WiFi.config(ip, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiSSID, WiFiPSK);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_PIN, ledStatus); 
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
    delay(100);
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int Check_server_request(void){

  static uint32_t last_time = millis();

  if((millis() - last_time) >= _15SECS){

      Http_get_request(buf_data);
      Serial.println("ANSWER: ");
      Serial.println(buf_data);
      last_time = millis();
      
      if(strstr(buf_data, "start") != NULL)
          return STARTING;
      else if(strstr(buf_data, "stop") != NULL)
          return STOPPING;
  } 
  else
       return -1;
}

