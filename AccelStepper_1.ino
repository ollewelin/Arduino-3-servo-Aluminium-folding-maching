//#include <AccelStepper.h>
//#include <MultiStepper.h>

/*   
 *   Basic example code for controlling a stepper with the AccelStepper library
 *      
 *   by Dejan, https://howtomechatronics.com
 */

#include <AccelStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 2, 5); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 3, 6); // (Type of driver: with 3 pins, STEP, DIR)
AccelStepper stepper3(1, 4, 7); // (Type of driver: with 4 pins, STEP, DIR)

void setup() {
  // Set maximum speed value for the stepper
  stepper1.setMaxSpeed(4000);
  stepper1.setAcceleration(10000.0);
  stepper1.moveTo(0);
  stepper2.setMaxSpeed(4000);
  stepper2.setAcceleration(10000.0);
  stepper2.moveTo(0);
  stepper3.setMaxSpeed(4000);
  stepper3.setAcceleration(10000.0);
  stepper3.moveTo(0);
  pinMode(A0, INPUT);//Stop
pinMode(A1, INPUT);//Start
pinMode(A2, INPUT);//Restart

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}
const int p_step = 10;
const int r_step = 9;
int godata_X[p_step]; 
int godata_Y[p_step]; 
int godata_Z[p_step]; 
int startX = 0;
int tempx = 0;
int X_start_set_OK = 0;
int startY = 0;
int tempY = 0;
int Y_start_set_OK = 0;
int startZ = 0;
int tempZ = 0;
int Z_start_set_OK = 0;

int stopped = 0;

void check_and_stop(){
  if(digitalRead(A0)==1){
    Serial.println("Stop All motors user set A0 HIGH ");
  stepper1.stop();
  stepper2.stop();
  stepper3.stop(); 
  stopped = 1;
    while(digitalRead(A0)==1){}
     Serial.println("Press agian to start ");
     delay(1000);
    while(digitalRead(A0)==0){} 
    Serial.println("Warning! Machine will Start in 3 sec");
    delay(3000);
 stopped = 0;
  }
  
}

int readInt(void){
  int readIntValue =0;
  while (Serial.available()==0){}             // wait for user input
  readIntValue = Serial.parseInt(); //
  Serial.print("You enter value ");
  Serial.print(readIntValue);
  Serial.println();
  return readIntValue;
}


void loop() {
   char dummy=0;
  /*
  int test1 =0;
  int test2 =0;
 
  int a=0;
  while(1){
  // if there's any serial available, read it:
  if(a==0){
Serial.println("debug0");
  }
  a=1;
  while (Serial.available() > 0) {
    a=0;
Serial.println("debug1");
    
    // look for the next valid integer in the incoming serial stream:


    int red = Serial.parseInt();

Serial.println("debug2");
    // do it again:


    int green = Serial.parseInt();

Serial.println("debug3");
    // do it again:


    int blue = Serial.parseInt();
Serial.println("debug4");

    // look for the newline. That's the end of your sentence:


    if (Serial.read() == '\n') {

      // constrain the values to 0 - 255 and invert


      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"


  

  
      // print the three numbers in one string as hexadecimal:


      Serial.println(red, DEC);


      Serial.println(green, DEC);


      Serial.println(blue, DEC);


    }
  }
//--
  }

  int old_startX =0;
  Serial.println("Set X start pos value +/-32767 ");
  old_startX = startX;
  startX = readInt();
  while(X_start_set_OK != 1){
  while(stepper3.run()){check_and_stop();};
  stepper3.moveTo(startX);
  while(stepper3.run()){check_and_stop();};
  Serial.println("Is this position OK then set 0 else type new value +/-32767 ");
  
  dummy = Serial.read();
  Serial.print("char :");
  Serial.println(dummy, DEC);
  old_startX = startX;
  tempx = readInt();
  if(tempx==0){
    X_start_set_OK=1;
  }
  else{
    startX=tempx;
  }
  check_and_stop();
  }
  dummy = Serial.read();
  Serial.println("X pos is now set to :");
  Serial.print(startX);
  Serial.println();
  */

  for(int i=0;i<p_step;i++){
    Serial.print("Set programming X, Y point number :");
    Serial.print(i);
    Serial.println();
     X_start_set_OK = 0;
     Y_start_set_OK = 0;
     Z_start_set_OK = 0;


// set X point 
  int old_startX =0;
  Serial.println("Set X start pos value +/-32767 ");
  if(i>0){
    Serial.print("Is: ");
    Serial.println(godata_X[i-1]);
  }
  old_startX = startX;
  startX = readInt();
  while(X_start_set_OK != 1){
  while(stepper3.run()){check_and_stop();};
  stepper3.moveTo(startX);
  while(stepper3.run()){check_and_stop();};
  Serial.println("Is this position OK then set 0 else type new value +/-32767 ");
  
  dummy = Serial.read();
//  Serial.print("char :");
//  Serial.println(dummy, DEC);
  old_startX = startX;
  tempx = readInt();
  if(tempx==0){
    X_start_set_OK=1;
  }
  else{
    startX=tempx;
  }
  check_and_stop();
  }
  dummy = Serial.read();
  Serial.println("X pos is now set to :");
  Serial.print(startX);
  Serial.println();
  godata_X[i] = startX;
//

// set Y point 
  int old_startY =0;
  Serial.println("Set Y start pos value +/-32767 ");
    if(i>0){
    Serial.print("Is: ");
    Serial.println(godata_Y[i-1]);
  }

  old_startY = startY;
  startY = readInt();
  while(Y_start_set_OK != 1){
  while(stepper1.run()){check_and_stop();};
  stepper1.moveTo(startY);
  while(stepper1.run()){check_and_stop();};
  Serial.println("Is this position OK then set 0 else type new value +/-32767 ");
  
  dummy = Serial.read();
//  Serial.print("char :");
//  Serial.println(dummy, DEC);
  old_startY = startY;
  tempY = readInt();
  if(tempY==0){
    Y_start_set_OK=1;
  }
  else{
    startY=tempY;
  }
  check_and_stop();
  }
  dummy = Serial.read();
  Serial.println("Y pos is now set to :");
  Serial.print(startY);
  Serial.println();
  godata_Y[i] = startY;
//
if(i<3){
// set Z point 
  int old_startZ =0;
  Serial.println("Set Z start pos value +/-32767 ");
    if(i>0){
    Serial.print("Is: ");
    Serial.println(godata_Z[i-1]);
  }

  old_startZ = startZ;
  startZ = readInt();
  while(Z_start_set_OK != 1){
  while(stepper2.run()){check_and_stop();};
  stepper2.moveTo(startZ);
  while(stepper2.run()){check_and_stop();};
  Serial.println("Is this position OK then set 0 else type new value +/-32767 ");
  
  dummy = Serial.read();
//  Serial.print("char :");
//  Serial.println(dummy, DEC);
  old_startZ = startZ;
  tempZ = readInt();
  if(tempZ==0){
    Z_start_set_OK=1;
  }
  else{
    startZ=tempZ;
  }
  check_and_stop();
  }
  dummy = Serial.read();
  Serial.println("Z pos is now set to :");
  Serial.print(startZ);
  Serial.println();
  godata_Z[i] = startZ;
//
}


  }

Serial.println("Programming is done!");
    for(int i=0;i<p_step;i++){
    Serial.print("Programming X, Y point number :");
    Serial.print(i);
    Serial.println();
    Serial.print("X point = ");
    
    Serial.print(godata_X[i]);
    Serial.println();
    Serial.print("Y point = ");
    Serial.print(godata_Y[i]);
    Serial.println();
    Serial.print("Z point = ");
    Serial.print(godata_Z[i]);
    Serial.println();
   
    }

    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[0]);
    while(stepper2.run()){check_and_stop();};
    
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[0]);
    while(stepper3.run()){check_and_stop();};

    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[0]);
    while(stepper1.run()){check_and_stop();};
    Serial.println("Start");
/*
    
 for(int i=0;i<r_step;i++){
  switch(i){
  case 0:
    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[0]);
    while(stepper2.run()){check_and_stop();};
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[0]);
    while(stepper3.run()){check_and_stop();};
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[0]);
    while(stepper1.run()){check_and_stop();};
  break;
  case 1:
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[1]);
    while(stepper3.run()){check_and_stop();};
  break;
  case 2:
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[1]);
    while(stepper1.run()){check_and_stop();};
  break;
  case 3:
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[0]);
    while(stepper1.run()){check_and_stop();};
  
  break;
  case 4:
    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[1]);
    while(stepper2.run()){check_and_stop();};
   
  break;
  case 5:

    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[0]);
    while(stepper3.run()){check_and_stop();};
  
  break;
  case 6:
    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[2]);
    while(stepper2.run()){check_and_stop();};
  
  break;
  case 7:
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[2]);
    while(stepper1.run()){check_and_stop();};

    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[3]);
    while(stepper3.run()){check_and_stop();};

    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[4]);
    while(stepper1.run()){check_and_stop();};

    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[0]);
    while(stepper2.run()){check_and_stop();};

    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[3]);
    while(stepper1.run()){check_and_stop();};


  break;
  case 8:
     while(stepper3.run()){check_and_stop();};
     stepper3.moveTo(godata_X[0]);
      while(stepper3.run()){check_and_stop();};
   while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[0]);
    while(stepper1.run()){check_and_stop();};
  
  break;

  
  default:
  break;
  }
  }
  */

  
 
    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[0]);
    while(stepper2.run()){check_and_stop();};

 
  while(1){
    Serial.println("Start");
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[0]);
    while(stepper3.run()){check_and_stop();};
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[0]);
    while(stepper1.run()){check_and_stop();};
    Serial.println("Run");
   
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[1]);
    while(stepper3.run()){check_and_stop();};
    
    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[1]);
    while(stepper2.run()){check_and_stop();};

    Serial.print("godata_Y[1] ");
     Serial.println(godata_Y[1]);
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[1]);
    while(stepper1.run()){check_and_stop();};
    Serial.print("godata_Y[2] ");
     Serial.println(godata_Y[2]);
    
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[2]);
    while(stepper1.run()){check_and_stop();};

    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[0]);
    while(stepper2.run()){check_and_stop();};

    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[3]);
    while(stepper1.run()){check_and_stop();};
    
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[4]);
    while(stepper3.run()){check_and_stop();};
    
   while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[2]);
    while(stepper2.run()){check_and_stop();};

    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[5]);
    while(stepper3.run()){check_and_stop();};
    
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[5]);
    while(stepper1.run()){check_and_stop();};
    
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[5]);
    while(stepper3.run()){check_and_stop();};
 
 
    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[6]);
    while(stepper1.run()){check_and_stop();};
    
    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[6]);
    while(stepper3.run()){check_and_stop();};

    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[7]);
    while(stepper3.run()){check_and_stop();};

    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[7]);
    while(stepper1.run()){check_and_stop();};

    while(stepper2.run()){check_and_stop();};
    stepper2.moveTo(godata_Z[1]);
    while(stepper2.run()){check_and_stop();};


    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[8]);
    while(stepper1.run()){check_and_stop();};

 //   while(stepper2.run()){check_and_stop();};
 //   stepper2.moveTo(godata_Z[0]);
 //   while(stepper2.run()){check_and_stop();};

    while(stepper1.run()){check_and_stop();};
    stepper1.moveTo(godata_Y[9]);
    while(stepper1.run()){check_and_stop();};

    while(stepper3.run()){check_and_stop();};
    stepper3.moveTo(godata_X[9]);
    while(stepper3.run()){check_and_stop();};

//    while(stepper2.run()){check_and_stop();};
//  stepper2.moveTo(godata_Z[2]);
//    while(stepper2.run()){check_and_stop();};


    
    }
 // stepper1.setSpeed((analogRead(A0));
  // Step the motor with a constant speed previously set by setSpeed();
  //  stepper1.moveTo(-stepper1.currentPosition());
 
  // run() returns true as long as the final position 
  //    has not been reached and speed is not 0.

  
  /*
  int i=0;
  while(stepper3.run()){};
  stepper3.moveTo(0);
  while(stepper3.run()){};
  
  while(stepper1.run()){};
  stepper1.moveTo(-2000);
  while(stepper1.run()){};
  
  while(stepper3.run()){};
  stepper3.moveTo(2000);
  while(stepper3.run()){};

  while(stepper1.run()){};
  stepper1.moveTo(2000);
  while(stepper1.run()){};
 */
 

  

  
}


/*   
 *   Basic example code for controlling a stepper without library
 *      
 *   by Dejan, https://howtomechatronics.com
 */
/*
// defines pins
#define stepPin 2
#define dirPin 5 
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(700);    // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(700); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 1600; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}
*/
