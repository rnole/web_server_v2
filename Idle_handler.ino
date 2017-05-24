
int Idle_handler(void){
  int next_state = 0;
  Serial.println("Entre: Idle handler");

  next_state = Check_server_request();
  
  if(next_state != -1){
      return next_state;
  }
  
  else if(sw_serial.available() > 0){
    
      SW_serial_read_data(buf_data);  
      if(strncmp(buf_data, "on", sizeof("on")) == 0){
          return ON;  
      }
      else if(strncmp(buf_data, "temp_big_oven", sizeof("temp_big_oven")) == 0){
          return IDLE;
      }
  }
  else
      return IDLE;
  
}

void SW_serial_read_data(char *buf){

  int idx = 0;

  while(sw_serial.available() > 0){
       buf[idx++] = (char)sw_serial.read();
  }
}

