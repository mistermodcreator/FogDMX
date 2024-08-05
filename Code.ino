// TM1637 Driver - Version: 2.1.2
#include <TM1637.h>

#include <DMXSerial.h>

const int status_led = 13;      //The pin to use for the status led (13 being the internal LED)
const int out = 5;              //The pin to use for relais/mosfet control

const int dmx_switch = 7;       //The pin to use to read the switch to disabel/enable manual control
const int pot_pin = A0;         //The pin to use for the pot input when manually controling
const int manual_pin = 6;       //The pin to use for the manual fog trigger

int channel = 1;                //The default DMX Adress to listen to
const int min_val = 2;         //Min DMX value to turn output on

const int ontime = 20;          //How long to turn Output on
const int min = 1000;            //Offtime for min Output
const int max = 0;             //Offtime for max Output

const int dmx_act_min = 1000;    //Max time between DMX Packets before an error is displayed

//Display pin config (CLK, DIO)
TM1637 tm(3, 4);

//Initialize all used variables as save values
int nodmx = 0;
int dmx_act = 0;
int in = 0;
int pot_val = 0;
int manual_trigger = 0;
int dmx_switch_state = 2;
int pot_perc = 0;
int waitnum = 999;
int old_dmx_switch_state = 10;

void setup() {
//Init DMXSerial as Reciever and set pinmodes
  DMXSerial.init(DMXReceiver);
  pinMode(status_led, OUTPUT);
  pinMode(out, OUTPUT);
  pinMode(dmx_switch, INPUT_PULLUP);
  pinMode(pot_pin, INPUT_PULLUP);
  pinMode(manual_pin, INPUT_PULLUP);
  digitalWrite(out, 1);
  //startup display driver
  tm.begin();
  tm.setBrightness(2);
  tm.clearScreen();
  tm.display("HI");
  delay(1500);
  tm.clearScreen();
}

void loop() {
  delay(30);
  tm.display("    ");
  old_dmx_switch_state = dmx_switch_state;
  dmx_switch_state=digitalRead(dmx_switch);
  if(dmx_switch_state != old_dmx_switch_state) {
    if(dmx_switch_state == 1){
      tm.display("D512");
      delay(1000);
      tm.clearScreen();}
    if(dmx_switch_state == 0){
      tm.display("BUTN");
      delay(1000);
      tm.clearScreen();}
  }
  //Check for DMX Activity, turn off status light and write to var if no activity
  dmx_act = DMXSerial.noDataSince();

  if(dmx_act > dmx_act_min && dmx_switch_state == 1){
    digitalWrite(status_led, 0);
    nodmx = 1;
    tm.display("nDMX");
  }
  if(dmx_act < dmx_act_min){
    digitalWrite(status_led, 1);
    nodmx = 0;
  }
  
  if(dmx_switch_state==1){
    // Turn output off (for safety, should already be off)
    digitalWrite(out, 1);

    if(nodmx == 0){
      in = DMXSerial.read(channel);
      manual_trigger=digitalRead(manual_pin);   //Read manual trigger
      tm.display(channel);
    
      if(in < 255){     //Check if not 100%
      
        // Turn output off (for safety, should already be off)
        digitalWrite(out, 1);
        if(in > min_val){   //Check if DMX Value is above min
          waitnum = map(in, 0, 255, min, max);
          digitalWrite(out, 0); //Turn output on, then wait for calculated time
          delay(ontime);
          digitalWrite(out, 1);
          delay(waitnum);
        }
      
      }
      if(in == 255){
        digitalWrite(out,0);    //Turn Output on when DMX Value is 255
      }

      if(manual_trigger==0){
        pot_val=analogRead(pot_pin);            //Read pot
        if(pot_val >= 15 && pot_val <= 700){pot_val=map(pot_val, 15, 700,1,64);}
        else if(pot_val < 15){pot_val = 1;}
        else if(pot_val > 700){pot_val = 64;}
        channel=pot_val;                        //Set Channel as pot value
      }
    }
  
    else{
      digitalWrite(out, 1);   //Wenn kein DMX, Output aus
    }
  
  }
  if(dmx_switch_state==0){      //When dmx is turned off, read pot and map to 0-255
    
    pot_val = analogRead(pot_pin);
    if(pot_val <= 700 && pot_val >= 5) {pot_val = map(pot_val,5,700,0,255);}
    if(pot_val > 700){pot_val = 255;}
    if(pot_val < 2){pot_val = 0;}
    manual_trigger = digitalRead(manual_pin);   //Read manual trigger
    tm.display(pot_val);                       //Display pot value
    
    if(manual_trigger == 0){                      //When fog triggered
      if(pot_val < 255 && pot_val >= min_val){    //Check if pot is not 100% and above min
        waitnum = map(pot_val, 0, 255, min, max); //Map pot to min and max value
        digitalWrite(out, 0);                     //Turn output on for time set on top
        delay(ontime);
        digitalWrite(out, 1);                     //Wait for time maped from pot value
        delay(waitnum);
      }
      
      if(pot_val == 255){
        digitalWrite(out,0);    //When pot is 100%, just press the button
      }
    }
    else{
      digitalWrite(out, 1);
    }
  }
}