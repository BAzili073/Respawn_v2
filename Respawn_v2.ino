#include <IRremote.h>
#include <MySeven.h>
IRsend irsend;

#define RESP_COMM 0x8305E8
#define MINE_COMM 0x6384E7//0x8300E8
#define ADD_IK_LED 2
#define IRSENDPIN 3
#define D_A 4    //11
#define D_B A3   //7
#define D_C 7    //4
#define D_D 5    //2
#define D_E 6    //1
#define D_F 9   // 10
#define D_G 8   //5
//#define PIN 10
#define IRRECPIN 11
#define LED_BLUE 12
#define LED_RED 10
#define LED_GREEN 13
//#define PIN 4
#define D_D1 A2   //6
#define D_D2 A1   //8
#define D_D3 A0   //9
#define MOTION_PIN A4
//#define PIN A6
#define BUTTONS A7

#define MODE_RESP_TIME 1
#define MODE_RESP_BUTTON 2
#define MODE_MINE 3
#define MODE_REC 4
#define MODE_MAX 5

#define MINE_NOT_READY 0
#define MINE_PRE_READY 1
#define MINE_READY 2
#define MINE_ACTIVATED 3
#define MINE_USED 4

#define RESP_BUTTON 1
#define DISP_BUTTON 2
#define MODE_BUTTON 3
#define NO_BUTTON 4

indicator display1(D_A,D_B,D_C,D_D,D_E,D_F,D_G,0,D_D1,D_D2,D_D3);

#define KIT_WEAPONS 15
int time_mine_forready;
byte time_led;

byte mine_state = MINE_NOT_READY;
byte model;
unsigned long COMMAND;
byte time_send = 0;
unsigned long weapons[KIT_WEAPONS] = {0x204060, 0x8305E8,0x8300E8};
int disp_number;
int button_var;
bool old_state_button_mode = false;
bool old_state_button_resp = false;
bool old_state_button_disp = false;
int time_on_disp = 5;
byte m_sec = 0;
byte sec = 0;
byte time_for_resp = 0;
byte time_for_resp_set = 15;
byte mode = MODE_RESP_TIME;
int resp_counter = 0;

     decode_results  results;        // Somewhere to store the results


byte ID ;
byte team ;
byte attack ;
byte attacks[5] = {1,2,4,7,8};
byte teams[4] = {LED_RED,LED_BLUE,LED_RED | LED_GREEN,LED_GREEN};


IRrecv irrecv(IRRECPIN);

void  setup ( )
{
  
  pinMode(ADD_IK_LED,OUTPUT);
  pinMode(IRSENDPIN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(BUTTONS,INPUT);
  pinMode(MOTION_PIN,INPUT);
  Serial.begin(9600);   // Status message will be sent to PC at 9600 baud
  irrecv.enableIRIn();  // Start the receiver
}

void  loop ( )
{
  if (mode == MODE_REC){
     if (irrecv.decode(&results)) {  // Grab an IR code
      dumpInfo(&results);           // Output the results
      irrecv.resume();              // Prepare for the next value
     }
     check_buttons();
  }else{
   timerIsr();
  }
   if (time_on_disp > 0){
      display_set(disp_number);
   }
// Serial.println(analogRead(MOTION_PIN));
}
