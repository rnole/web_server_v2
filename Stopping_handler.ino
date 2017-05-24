
int Stopping_handler(void){

  Serial.println("Entre: Stopping handler");
  sw_serial.print("stop");
  return IDLE;
}

