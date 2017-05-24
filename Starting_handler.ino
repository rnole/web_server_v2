

int Starting_handler(void){

  struct_starting_cmd starting_cmd;
  Serial.println("Entre: Starting handler");
  Starting_parse_command(&starting_cmd, buf_data);
  Starting_send_msg_to_arduino(&starting_cmd);
  
  return ON;
}

void Starting_parse_command(struct_starting_cmd *cmd, char *buf){

  char *p_cmd;

  p_cmd = strstr(buf, "start,") + 6;
  cmd->type_oven = atoi(p_cmd);
  p_cmd = strstr(p_cmd, ",") + 1;
  cmd->profile = atoi(p_cmd);

  Serial.print("type oven: ");
  Serial.println(cmd->type_oven);
  Serial.print("profile: ");
  Serial.println(cmd->profile);
}

void Starting_send_msg_to_arduino(struct_starting_cmd *cmd){
  
  sw_serial.print("on,");
  sw_serial.print(cmd->type_oven);  
  sw_serial.print(',');
  sw_serial.print(cmd->profile);
}




