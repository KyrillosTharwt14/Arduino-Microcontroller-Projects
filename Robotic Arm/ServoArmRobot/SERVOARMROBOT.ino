#include <Servo.h>
#include <Keyboard.h>



class Sweeper
{
    Servo servo;              // the servo
    int pos;              // current servo position
    int increment;        // increment to move for each interval
    int  updateInterval;      // interval between updates
    unsigned long lastUpdate; // last update of position

  public:
    Sweeper(int interval)
    {
      updateInterval = interval;
      increment = 5;
      servo.write(0) ;
    }

    void Attach(int pin)
    {
      servo.attach(pin);
    }

    void Update(int sign)
    {
      if ((millis() - lastUpdate) > updateInterval) // time to update
      {
        lastUpdate = millis();
        pos = pos + (sign * increment);
        if (sign == 1)
        {
          if (pos <= 180) {servo.write(pos);}
          else { pos  = 180 ;  servo.write(pos);}
        }
        else
        { // sign = -1
          if (pos >= 0) {servo.write(pos);}
          else {pos = 0 ; servo.write(pos);}
        }
      }
    }
};


Sweeper sweeper1(25);
Sweeper sweeper2(25);



const int buttonPinUp1   = 6;     // the number of the pushbutton pin
const int buttonPinDown1 = 5;     // the number of the pushbutton pin
const int buttonPinUp2   = 4;     // the number of the pushbutton pin
const int buttonPinDown2 = 3;     // the number of the pushbutton pin


int buttonState1 = 0 , buttonState2 = 0 , buttonState3 = 0 , buttonState4 = 0;       // variable for reading the pushbutton status
uint8_t buf[8] = {0};   /* Keyboard report buffer */
int Up = 1 ;  
int Down = -1 ;

void setup()
{
  Serial.begin(9600);
  delay(200);
  sweeper1.Attach(9);
  sweeper2.Attach(10);

  pinMode(buttonPinUp1, INPUT);
  pinMode(buttonPinDown2, INPUT);
  pinMode(buttonPinUp2, INPUT);
  pinMode(buttonPinDown2, INPUT);
}


void loop()
{
  buttonState1 = digitalRead(buttonPinUp1);
  buttonState2 = digitalRead(buttonPinDown1);
  buttonState3 = digitalRead(buttonPinUp2);
  buttonState4 = digitalRead(buttonPinDown2);

  if (buttonState1 == HIGH) {
    sweeper1.Update(Up);
    ButtonPressedLetter ('a');
  }

  if (buttonState2 == HIGH) {
    sweeper1.Update(Down);
    ButtonPressedLetter ('b');
  }

  if (buttonState3 == HIGH) {
    sweeper2.Update(Up);
    ButtonPressedLetter ('c');
  }

  if (buttonState4 == HIGH) {
    sweeper2.Update(Down);
    ButtonPressedLetter ('d');
  }
  else {
    //do nothing
  }
  delay(20) ;
}

void ButtonPressedLetter (char letter)
{
  buf[0] = 0;
  if (letter == 'a' ) {buf[2] = 0x04;}
  else if (letter == 'b' ) {buf[2] = 0x05;}
  else if (letter == 'c' ) {buf[2] = 0x06;}
  else if (letter == 'd' ) {buf[2] = 0x07;}
  else {// do nothing
  }
  Serial.write(buf, 8);
  releaseKey();
}



void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
}
