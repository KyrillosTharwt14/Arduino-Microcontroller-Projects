#include <AFMotor.h>
#include <Servo.h> 
AF_Stepper StepperX(48, 1); // A 48-step-per-revolution motor on channels 1 & 2
AF_Stepper StepperY(48, 2); // A 48-step-per-revolution motor on channels 3 & a
Servo ServoZ ; 
int junk;
int type;
int var;
void initiate();

void setup() {
  Serial.begin(9600);
  StepperX.setSpeed(255);
  StepperY.setSpeed(255);
  ServoZ.attach (10)    ;  
  initiate () ;
  
}
 

void loop() 
{
  
  if (Serial.available()>0)
  {
  type = Serial.read();
     // Serial.println(type);  
  if(type > 111 && type < 129)
  {
     if(type > 111 && type <119)
     {
      //Serial.println(type);
      var = type-110;
      DrawLine_H (var);
      //initiate () ;
     }
     else
     {
      var = type-120;
      DrawLine_V (var);
      //initiate () ;
     }
  }
  else if(type >= 11 && type <=99)
  {
    DrawSquare (int(type/10), type%10)   ;
    
  }
  else if (type == 200)
  {
    DRAWMULTILINE ();
    }
  }
   while(Serial.available()>0)
   {junk = Serial.read();}
}

void initiate()
{
  ServoZ.write (90);
  delay (500) ; 
  StepperX.step(400,FORWARD,DOUBLE);
  delay (100) ; 
  StepperY.step(400,FORWARD,DOUBLE);
  
}

void DrawLine_H (int Length)
{
  ServoZ.write (-90);
  StepperX.step((Length*30),BACKWARD,DOUBLE)  ;   
  delay (1000);
  StepperX.step((Length*30), FORWARD,DOUBLE);
  ServoZ.write (90);
 }
 
void DrawLine_V (int Length)
{
   ServoZ.write (-90);
   StepperY.step((Length*30), BACKWARD,DOUBLE);
   delay (100);
   StepperY.step((Length*30),FORWARD,DOUBLE);  
   ServoZ.write (90);
 }
 
  void DrawSquare (int Length , int Width)
  {
    ServoZ.write (-90);
     StepperX.step((Width*30), BACKWARD,DOUBLE);
     delay (1000);
     StepperY.step((Width*30), BACKWARD,DOUBLE);
     delay (1000);
     ServoZ.write (-90);
     StepperX.step((Length*30), FORWARD,DOUBLE);
     delay (1000);
     StepperY.step((Length*30), FORWARD,DOUBLE);
     delay (1000);
     ServoZ.write (90);
     
    }
    void DRAWMULTILINE ()
    {
      ServoZ.write (-90);
      StepperX.step(200, BACKWARD,DOUBLE);
      delay (100);
      ServoZ.write (90);
      StepperY.step(200, FORWARD,DOUBLE) ;
      delay (100);
      ServoZ.write (-90);
      StepperX.step(200, FORWARD,DOUBLE) ;
      delay (100);
     }
    
