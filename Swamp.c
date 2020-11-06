// created on November 04 2020
// main file for the swamp cooler code, switches to different states. 
// takes in data from temperature and water level sensor.
// worked on by Alan Garcia and Gavin Farrell

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
  if(//we must decide which pin will take an input from){
    for(volatile unsigned int i=0; i<1000; i++);//check if the input is only a small error
    if(//same issue as above){
      return 1;  //returns 1 if the button has been properly pressed
      }
  return 0; //returns 0 if the button has not been properly pressed
  }
      
void all_state(){
  
}
      
unsigned char Disabled(){
                       //activate yellow LED (need to decide which pin we're using
  while(button_press()){  }
                       //deactivate yellow LED
  state='I';          //returns I so that it can move to the Idle state
}
      
void Idle(){
                      //activate green LED
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
                     //deactivate green LED
  }
      
void Running(){
                    //activate blue LED
                    //activate motor
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
                    //deactivate blue LED
                    //deactivate motor
  }
      
void Error(){
                    //activate red LED
                    //display error message on LCD screen
  while(//water bellow minimum){
    all_state();
    if(button_press()){
      state='D';
      }
    }
  state= 'I'        //return to idle once water is above minimum
                    //deactivate red LEd
  }
