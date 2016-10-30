byte check_buttons(){
  button_var = analogRead(BUTTONS);
  
//  Serial.println(button_var);
  if (button_var > 800){
      buttons_unpress();
      return NO_BUTTON;   
  } else{
    if (button_var > 450){
       button_mode_press(); 
       return MODE_BUTTON;    
    }else{
       if (button_var > 100){
         button_disp_press();
         return DISP_BUTTON;   
       }else{
          if (button_var < 100){
            button_resp_press();
            return RESP_BUTTON;   
          }
       }
    }
  }
   
}


void button_mode_press(){
  if (!old_state_button_mode){
    old_state_button_mode = true;
    mode ++;
    switch (mode){
      case MODE_RESP_TIME:
        
      break;
      case MODE_RESP_BUTTON:
        
      break;
      case MODE_MINE:
        mine_state = MINE_NOT_READY;
        COMMAND =  MINE_COMM;
        time_led = 5;
//        COMMAND =  weapons[1];
//        time_send = 50;
        digitalWrite(ADD_IK_LED,HIGH);
      break;
      case MODE_MAX:
        digitalWrite(ADD_IK_LED,LOW);
        digitalWrite(LED_GREEN,LOW);
        digitalWrite(LED_BLUE,LOW);
        digitalWrite(LED_RED,LOW);
        COMMAND = RESP_COMM;
//        COMMAND =  0x1D88A5
        mode = MODE_RESP_TIME;
      break;
      
    }

    disp_number = mode;
    disp_on(10);
  }
}

void button_resp_press(){
  if (!old_state_button_resp){
    old_state_button_resp = true;
    if (mode == MODE_RESP_BUTTON){
      time_send = 1;
      resp_counter++;
      disp_number = resp_counter;
    }
  }
}

void button_disp_press(){
  if (!old_state_button_disp){
    old_state_button_disp = true;
    disp_number = resp_counter;
    disp_on(10);
  }
}

void buttons_unpress(){
   old_state_button_mode = false;
   old_state_button_resp = false;
   old_state_button_disp = false;
}

bool check_motion(){
  
  return digitalRead(MOTION_PIN);
  
}


