void timerIsr()
{ 
  static unsigned long timer = millis();
  if (millis() >= timer ){
    if (time_send) {
      send_command();
      time_send -- ;
    }
    timer = millis() + 100 ;
    check_buttons();
    m_sec ++;
    if (m_sec == 10){
      if (time_on_disp) time_on_disp--;
      m_sec = 0;
      sec++;
      if (sec == 60) sec = 0;
    } 
     if (mode == MODE_RESP_TIME){
      
        time_for_resp ++;
        if (time_for_resp == time_for_resp_set){
          time_for_resp = 0;
          time_send = 1;
        }
     }
     if (mode == MODE_MINE){
        switch (mine_state){
          case MINE_NOT_READY:
          #ifdef DEBUG
             Serial.println ("MINE_NOT_READY");
           #endif
          time_led--;
          if (time_led<=0){
//              time_send = 1;
              time_led = 5;
              if (digitalRead(LED_GREEN)) 
              digitalWrite(LED_GREEN,LOW);
              else digitalWrite(LED_GREEN,HIGH);
            }
            if (check_buttons() == RESP_BUTTON){
              mine_state = MINE_PRE_READY;
              time_mine_forready = 300;
              time_led = 1;
            }
          break;
          case MINE_PRE_READY:
          #ifdef DEBUG
             Serial.println ("MINE_PRE_READY");
           #endif
            time_mine_forready --;
            time_led--;
            if (!time_led){ 
              time_led = 5;
              if (digitalRead(LED_BLUE)) digitalWrite(LED_BLUE,LOW);
              else digitalWrite(LED_BLUE,HIGH);
            }
            if (!time_mine_forready) {
              mine_state = MINE_READY;
              digitalWrite(LED_BLUE,LOW);
              digitalWrite(LED_RED,LOW);
            }
          break;
          case MINE_READY:
          #ifdef DEBUG
             Serial.println ("MINE_READY");
           #endif
//            if (check_motion()){
              mine_state = MINE_ACTIVATED;
//            }
          break;
          case MINE_ACTIVATED:
          time_led--;
          #ifdef DEBUG
             Serial.println ("MINE_ACTIV");
           #endif
            if (!time_led){
              time_send = 1;
              time_led = 5;
              if (digitalRead(LED_RED)) digitalWrite(LED_RED,LOW);
              else digitalWrite(LED_RED,HIGH);
            }
//            time_send = 50;
//            mine_state = MINE_USED;
          break;
          case MINE_USED:
            
          break;    
        }
     }
  }
  
}
