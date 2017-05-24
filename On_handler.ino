
int On_handler(void){
  int next_state = 0;
  Serial.println("Entre: On handler");

  next_state = Check_server_request();
  
  if(next_state != -1){
      return next_state;
  }
  
  else if(sw_serial.available() > 0){ 
      memset(buf_data, 0, sizeof(buf_data));
      SW_serial_read_data(buf_data);
      Http_post_request(buf_data);
  }
  else
      return ON;
}

