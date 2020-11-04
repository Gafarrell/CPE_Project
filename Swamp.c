// created on November 04 2020
// main file for the swamp cooler code, switches to different states. 
// takes in data from temperature and water level sensor.
// worked on by Alan Garcia and Gavin Farrell

//character variable that decides which state the program is in, defaults to Disabled
unsigned char state='D';

//each of the following functions is a state of the machine, returns a character of the next state.
unsigned char Disabled(); //unsure if we need to pass in anything
unsigned char Idle();
unsigned char Runnung();
unsigned char Error();

setup(){
  state = Disabled(); // at Disabled state by default.
  
  }
  
loop(){
  switch(state){ //takes in the state character and changes states accordingly
    case 'D':
      state= Disabled();
      break;
    case 'I':
      state = Idle();
      break;
    case 'R':
      state= Running();
      break;
    case 'E':
      state= Error();
      break;
    default:
      state =Disabled(); // Fail-safe, sets to Disabled state
      break;
    }
  }
