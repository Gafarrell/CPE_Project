// created on November 04 2020
// main file for the swamp cooler code, switches to different states. 
// takes in data from temperature and water level sensor.
// worked on by Alan Garcia and Gavin Farrell

//addresses
volatile unsigned char *myDDRA = (unsigned char *) 0x22;
volatile unsigned char *port_a = (unsigned char *) 0x23;
volatile unsigned char *pin_a = (unsigned char *) 0x21;
volatile unsigned char *myDDRB = (unsigned char *) 0x25;
volatile unsigned char *port_b = (unsigned char *) 0x26;

//character variable that decides which state the program is in, defaults to Disabled
unsigned char state;
//threshold for the temperature
unsigned int threshold;
//minimum amount of water
unsigned int water_minimum;

//each of the following functions is a state of the machine, will change the state variable within.
void Disabled(); //unsure if we need to pass in anything in
void Idle();
void Runnung();
void Error();

//functions to help with the operation
unsigned int button_press();
void all_state(); //functionally for most of the states

setup(){
  state = 'D'; // at Disabled state by default.
  //we must decide our threshold and minimum water values
  //we must decide the addresses for our outputs and inputs
  *myDDRA |= 0xF0; //set pins 26-29 to outputs for the LEDs
  *myDDRA &= 0xFE; //set pin 22 to input for the push button
  *port_a |= 0x01; //enable pullup resistor on pin 22
  *myDDRB |= 0x80; //set pin 53 to output for the motor
  }
  
loop(){
  switch(state){ //takes in the state character and changes states accordingly
    case 'D':
      Disabled();
      break;
    case 'I':
      Idle();
      break;
    case 'R':
      Running();
      break;
    case 'E':
      Error();
      break;
    default:
      Disabled(); // Fail-safe, sets to Disabled state
      break;
    }
  }

unsigned int button_press(){
  if(!(*pin_a & 0x01)){
    for(volatile unsigned int i=0; i<1000; i++);//check if the input is only a small error
    if(!(*pin_a & 0x01)){
      return 1;  //returns 1 if the button has been properly pressed
      }
  return 0; //returns 0 if the button has not been properly pressed
  }
      
//This is the common functionallity of most of the states in this system
void all_state(){
  //update current water level, send to LCD screen
  //update current temperature, send to LCD screen
  //vent position manipulation
}
      
unsigned char Disabled(){
  *port_a |= 0x80;    //activate yellow LED (pin 29)
  while(button_press()){  }
  *port_a &= 0x7F;    //deactivate yellow LED
  state='I';          //returns I so that it can move to the Idle state
}
      
void Idle(){
  *port_a |= 0x40;       //activate green LED (pin 28)
  unsigned int change=0; //checks if the state needs to change
  while(!change){
    all_state();
    if(//water bellow minimum){
      change=1;
      state='E';
      }
    if(//temperature above threshold){
      change=1;
      state='R';
      }
    if(button_press()){
      change=1;
      state='D';
      }
    }
  *port_a &= 0xBF; //deactivate green LED
  }
      
void Running(){
  *port_a |= 0x20;  //activate blue LED (pin 27)
  *port_b |= 0x80;  //activate motor
                    //timestamp for motor turning on
  unsigned int change=0; //checks if the state needs to change
  while(!change){
    all_state();
    if(//water bellow minimum){
      change=1;
      state='E';
      }
    if(//temperature bellow threshold){
      change=1;
      state='I';
      }
    if(button_press()){
      change=1;
      state='D';
      }
    }
  *port_a &= 0xDF;  //deactivate blue LED
  *port_b &= 0x7F;  //deactivate motor
                    //timestamp for motor turning off
  }
      
void Error(){
  *port_a |= 0x10;  //activate red LED (pin 26)
                    //display error message on LCD screen
  while(//water bellow minimum){
    all_state();
    if(button_press()){
      state='D';
      }
    }
  state= 'I'        //return to idle once water is above minimum
  *port_a &= 0xEF;  //deactivate red LEd
  }
