void send_command(){
//   irsend.sendSAMSUNG(0xB24D1FE0,32);
//  digitalWrite(3,HIGH); 
  irsend.sendSony(COMMAND,24); //respawn signal
  irrecv.enableIRIn();  // Start the receiver
}

void  dumpInfo2 (decode_results *results)
{
  if (results->overflow) {
    return;
  }

  // Show Encoding standard
if (results->decode_type == SONY){
//    for (byte i = 0;i<KIT_WEAPONS;i++){
//      if ((results->value) == weapons[i]) Serial.println(i);
//    }
    ID = ((results->value & 0xFF0000) / 0x10000);
    team = (results->value & 0xC000) / 0x4000;
    attack = (results->value & 0x3C00) / 0x400;
    Serial.print("code = ");
    Serial.println(results->value,HEX);
    Serial.println ((results->value & 0xC000));
    Serial.print("ID = ");
    Serial.println(ID);
    Serial.print("team = ");
    Serial.println(teams[team]);
    Serial.print("attack = ");
    Serial.println(attacks[attack]);
   }
  // Show Code & length
}

void  dumpInfo (decode_results *results)
{
  if (results->overflow) {
//    Serial.println("IR code too long. Edit IRremoteInt.h and increase RAWLEN");
    return;
  }

 if (results->decode_type == SONY){
//    Serial.println(results->value,HEX);
//  Serial.println((results->value & 0xFF0000),HEX);
//        Serial.println((results->value & 0xFF00),HEX);
//        Serial.println((results->value & 0xFF),HEX);Serial.println((results->value & 0xFF0000),HEX);
//        Serial.println((results->value & 0xFF00),HEX);
//        Serial.println((results->value & 0xFF),HEX);
//    for (byte i = 0;i<KIT_WEAPONS;i++){
//      if ((results->value) == weapons[i]) Serial.println(i);
//    }
  if (( (((results->value & 0xFF0000) / 0x10000)+((results->value & 0xFF00) / 0x100))) == (results->value & 0xFF)){
//        Serial.println((results->value & 0xFF0000),HEX);
//        Serial.println((results->value & 0xFF00),HEX);
//        Serial.println((results->value & 0xFF),HEX);
        ID = ((results->value & 0xFF0000) / 0x10000);
        team = (results->value & 0xC000) / 0x4000;
        attack = (results->value & 0x3C00) / 0x400;
        disp_number = ID*10 + attacks[attack];
        disp_on(10);
        digitalWrite(LED_RED,LOW);
        digitalWrite(LED_BLUE,LOW);
        digitalWrite(LED_GREEN,LOW);
        digitalWrite(teams[team],HIGH);
        
//        Serial.print("code = ");
//        Serial.println(results->value,HEX);
//    //    Serial.println ((results->value & 0xC000));
//        Serial.print("ID = ");
//        Serial.println(ID);
//        Serial.print("team = ");
//        Serial.println(teams[team]);
//        Serial.print("attack = ");
//        Serial.println(attacks[attack]);
   }
 }
  
}




