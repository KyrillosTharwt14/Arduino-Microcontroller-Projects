#include <Servo.h>
#include "List.h"
#include "Elevator.h"
#include <Keypad.h>
/*
  angle of servo ---> level
  0------> G
  45-----> 1
  90-----> 2
  135----> 3
  180----> 4

*/


Elevator elevator1 ;
Elevator elevator2 ;
Elevator elevator3 ;
Elevator elevator[3] ; //= {elevator1, elevator2, elevator3};

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','E'},
  {'3','4','E','E'},
  {'A','B','C','D'},
  {'a','b','c','d'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int Up = 1 ;int Down = -1 ;
bool FlagOfDoor[5] = {false,false,false,false,false}; //{falg1,flag2,flag3,flag4,flag5};
int * Near[5] ; //{near1,near2,near3,near4,near5}
int DoorNo[5] = {0,45,90,135,180};
int LED[3] = {A0 , A1 , A2};

int flagDes[5] = {false,false,false,false,false} ;
unsigned long lastUp = 0 ;
int  E =0; /// only for elevator 3 destination ;
int Des =0;
String recieved = "" ;

void setup()
{
  Serial.begin(9600);
  delay(200);
  for (int i = 0 ; i <=2 ; i++) {elevator[i].SetElevator();elevator[i].Attach(i+2);   pinMode (LED[i],OUTPUT);}
}
 
void loop()
{
  char myKey = myKeypad.getKey(); 
 // if (myKey){Serial.println(myKey);}
  if ((myKey == 'd' ) || FlagOfDoor[4])                    {Check(4, DoorNo[4]);}
  if (((myKey == 'C') || (myKey == 'c')) || FlagOfDoor[3]) {Check(3, DoorNo[3]);}
  if (((myKey == 'B') || (myKey == 'b')) || FlagOfDoor[2]) {Check(2, DoorNo[2]);}
  if (((myKey == 'A') || (myKey == 'a')) || FlagOfDoor[1]) {Check(1, DoorNo[1]);}
  if ((myKey == 'D' ) || FlagOfDoor[0])                    {Check(0, DoorNo[0]);}
  if ((myKey == '0' ) || flagDes[0] )                     {goDestination(0, 0,   0);}
  if ((myKey == '1' ) || flagDes[1] )                     {goDestination(0, 45,  1);} 
  if ((myKey == '2' ) || flagDes[2] )                     {goDestination(0, 90,  2);}
  if ((myKey == '3' ) || flagDes[3] )                     {goDestination(0, 135, 3);}
  if ((myKey == '4' ) || flagDes[4] )                     {goDestination(0, 180, 4);}
  
  if (Serial.available()>0)
    {
     int x ;
    recieved = Serial.readString();
    Serial.println (recieved);
    int y = (recieved.toInt())/ 10 ;
    int z = (recieved.toInt())% 10 ;
    if (y == 0) {x= 0;}
    else if (y == 1) {x= 45;}
    else if (y == 2) {x= 90;}
    else if (y == 3) {x= 135;}
    else if (y == 4) {x= 180;}
    //Serial.println (y) ;
    //Serial.println (z) ; 
    goDestination(y, x, z);
   }
  unsigned long currentMillis = millis();
  if (millis()- lastUp  >= 3000) 
  { 
    lastUp = currentMillis ;
    Serial.println("/------------------------------------------------------------------/");
    Serial.print("Elevator 1 in: ");
    Serial.println (elevator[0].pos);
    Serial.print("Elevator 2 in: ");
    Serial.println (elevator[1].pos);
    Serial.print("Elevator 3 in: ");
    Serial.println (elevator[2].pos);
    Serial.println("/------------------------------------------------------------------/");
  }
}
  
int * NearestElevator(int CurentPosition, int CurentPositionE0  , int CurentPositionE1 , int CurentPositionE2 ) //  CurrentPosition: based on floor num and up/down button from user
// el mfrod 3ndi 3 variables l kol elevator :  CurentPositionE1 CurentPositionE2 CurentPositionE3
{
  static int y[2] ;
  int  E0 = CurentPosition - CurentPositionE0;
  int  E1 = CurentPosition - CurentPositionE1;
  int  E2 = CurentPosition - CurentPositionE2;
  //y[0] = 0 ; y[1] = E1 / abs(E1) ; // only for test ;
  if ( (abs(E0) < abs(E1) ) && ( abs(E0) < abs(E2) )) {Serial.println("Elevator 1 is the nearest "); y[0] = 0 ; y[1] = (E0 / abs(E0)); }
  else if ( abs(E1) < abs(E2) )                       {Serial.println("Elevator 2 is the nearest "); y[0] = 1 ; y[1] = (E1 / abs(E1)); }
  else                                                {Serial.println("Elevator 3 is the nearest "); y[0] = 2 ; y[1] = (E2 / abs(E2)); }
  return y ;
}

void Check(int level, int doorNo)
{
  if (FlagOfDoor[level] == false)
  {
    Serial.println("/---------------------flag become false");
    Near[level] = NearestElevator ((doorNo) , elevator[0].pos ,elevator[1].pos ,elevator[2].pos) ; // call function find the nearest one, and get it
    if (elevator[*Near[level]].checkEmpty())
    {
      elevator[*Near[level]].mode = *(Near[level]+1);
      Serial.println("/---------------------Mode is selected");
    }
     if (elevator[*Near[level]].pos != doorNo){
    elevator[*(Near[level])].addLevel(doorNo) ;}
    FlagOfDoor[level] = true ;   
  }
  else if (FlagOfDoor[level] == true)
  {
    if (!(elevator[*(Near[level])].Stop)) 
    {
      Serial.println("/---------------------flag become true");
      elevator[*(Near[level])].Update(*(Near[level]+1)) ;
    }   
    if ( elevator[*(Near[level])].pos == doorNo) 
    {
      digitalWrite (LED[*(Near[level])],HIGH);
      elevator[*(Near[level])].removeLevel(doorNo);  
      elevator[*(Near[level])].Stop = true ;
      FlagOfDoor[level] =  elevator[*(Near[level])].StopElevator () ; 
      if (!FlagOfDoor[level]) {digitalWrite (LED[*(Near[level])],LOW);}    
    }
  } 
}
void goDestination(int num, int doorDes, int level)
{
  if (!flagDes[level]){ 
      if (elevator[num].pos != doorDes){
      elevator[num].addLevel(doorDes) ;}
      if (elevator[num].checkEmpty())
      {
        E = doorDes - elevator[num].pos;
        elevator[num].mode = E/abs(E);
        Serial.println("/---------------------Mode is selected");
      }
      flagDes[level] = true ;
    }
    else if (flagDes[level])
    {
      if (!(elevator[num].Stop)) 
      {
      Serial.println("/---------------------flag become true");
      elevator[num].Update(E/abs(E)) ;
      }   
      if ( elevator[num].pos == doorDes) 
      {
      digitalWrite (LED[num],HIGH);
      elevator[num].removeLevel(doorDes);  
      elevator[num].Stop = true ;
      flagDes[level] =  elevator[num].StopElevator () ; 
      if (!flagDes[level]) {digitalWrite (LED[num],LOW);}    
      }
    }
  }
