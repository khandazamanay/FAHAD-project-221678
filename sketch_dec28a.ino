#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 
#define echo A2    //Echo pin
#define trigger A3 //Trigger pin
#define servo A5


int Set=50;
int distance_L, distance_F, distance_R; 
void setup(){ 
Serial.begin(9600); // start serial communication at 9600bps

 

pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  
pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

pinMode(servo, OUTPUT);
 
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }                    // for right
 for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }                    //for left
   for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }

distance_F = Ultrasonic_read();
delay(200);
}
void loop(){  
  
distance_F = Ultrasonic_read();
  
  if(distance_F > Set)
  {moveforward();}

   else
   {Check_side();
   compareDistance();
   }
delay(10);
}

void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;      // Convert angle to microseconds
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50); // Refresh cycle of servo
}
//*Ultrasonic_read*
long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(5);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}
void compareDistance(){
    if(distance_L > distance_R){
  moveback();
  delay(600);
  turnLeft();
  delay(500);
  moveforward();
  delay(600);
  turnRight();
  delay(500);
  moveforward();
  delay(600);
  
  }
  else{
    moveback();
    delay(600);
  turnRight();
  delay(500);
  moveforward();
  delay(600);
  turnLeft();
  delay(500);
  moveforward();
  delay(600);  
  
  }
}
void Check_side(){
    Stop();
    delay(100);
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
     delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
      delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    
}
void moveforward(){
analogWrite(enA, 150);
analogWrite(enB, 150);

digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
void moveback(){        //backword
analogWrite(enA, 150);
analogWrite(enB, 150);
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW); 
digitalWrite(in4, HIGH);   
}
void turnRight(){       //turnRight
 analogWrite(enA, 150);
digitalWrite(in1, LOW);  
digitalWrite(in2, HIGH); 
analogWrite(enB, 50);
digitalWrite(in3, HIGH); 
digitalWrite(in4, LOW);  
}
void turnLeft(){          //turnLeft
 analogWrite(enA, 50);
digitalWrite(in1, LOW);  
digitalWrite(in2, HIGH); 
analogWrite(enB, 150);
digitalWrite(in3, HIGH); 
digitalWrite(in4, LOW);  
}
void Stop(){ //stop
digitalWrite(in1, LOW);  
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW); 
digitalWrite(in4, LOW); 
}