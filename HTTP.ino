
void Http_get_request(char buf_request[]){

  int timeout_wait = 0;
  int buffer_index = 0;

  if (wifi_client.connect(HOST, HOST_PORT) == 1) {
      Serial.println("-> Connected");
      wifi_client.println(F("GET /query HTTP/1.1"));
      wifi_client.print(F("Host: "));
      wifi_client.println(HOST);
      wifi_client.println(F("Connection: close"));
      wifi_client.println(F("Content-Type: application/x-www-form-urlencoded"));
      wifi_client.println();

      while(wifi_client.connected()){
          while(wifi_client.available()){
              buf_request[buffer_index++] = wifi_client.read();
              timeout_wait = 0;
          }
          delay(1);
          timeout_wait++;
          if(timeout_wait > 10000){
            Serial.println(F("Timeout"));
            wifi_client.flush();
            wifi_client.stop();
          }
      }
      Serial.println(F("disconnecting."));
      wifi_client.stop();   
  }
  else
      Serial.println("-> Couldn't connect");
}

void Http_post_request(char buf_request[]){

  int timeout_wait = 0;
  int buffer_index = 0;

  if (wifi_client.connect(HOST, HOST_PORT) == 1) {
      Serial.println("-> Connected");
      wifi_client.println(F("POST /plotdata HTTP/1.1"));
      wifi_client.print(F("Host: "));
      wifi_client.println(HOST);
      wifi_client.println(F("Connection: close"));
      wifi_client.println(F("Content-Type: application/x-www-form-urlencoded"));
      wifi_client.print(F("Content-Length: "));
      wifi_client.println(strlen(buf_request));
      wifi_client.println();
      wifi_client.println(buf_request);   
      

      while(wifi_client.connected()){
          while(wifi_client.available()){
              Serial.print((char)wifi_client.read());
              timeout_wait = 0;
          }
          delay(1);
          timeout_wait++;
          if(timeout_wait > 10000){
            Serial.println(F("Timeout"));
            wifi_client.flush();
            wifi_client.stop();
          }
      }
      Serial.println(F("disconnecting."));
      wifi_client.stop();   
  }
  else
      Serial.println("-> Couldn't connect");

}

