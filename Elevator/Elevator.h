#ifndef ELEVATOR
#define ELEVATOR



class Elevator
{
  private :
    Servo servo;              // the servo
    int increment;            // increment to move for each interval
    int  updateInterval;      // interval between updates
    unsigned long lastUpdate; // last update of position
    unsigned long previousMillis = 0 ; 
    const long interval = 3000 ;
    List list ;
    
  public:
    int pos = 0;              // current servo position
    int mode =0;             //mode elevator UP/ DOWN
    bool Stop ;
    void SetElevator() { updateInterval = 100; increment = 5; servo.write(0) ; Stop = false;}
    void Attach(int pin) { servo.attach(pin);}
    void addLevel (int level)    {list.Add(level);   }
    void removeLevel (int level) {list.Remove(level);}
    bool StopElevator ()
    {
      unsigned long currentMillis = millis();
      if (currentMillis - lastUpdate >= interval) { lastUpdate = currentMillis; Stop = false; return false ;}
      else return true ; 
    }
    bool checkEmpty()
    {
      if (list.IsEmpty()){return true;}
      else {return false ;}
    }
    void Update(int sign)
    {
      if ((millis() - lastUpdate) > updateInterval) // time to update
      {
        lastUpdate = millis();
        if (!list.IsEmpty())
        {
          if (sign != mode){
            sign = mode ;
            }
          pos = pos + (sign * increment);
          if (sign == 1)
          {if (pos <= list.largestElement()) {servo.write(pos);}else { pos  = list.largestElement() ;  servo.write(pos);}}
          else // sign = -1
          { if (pos >= list.smallestElement()) {servo.write(pos);}else {pos = list.smallestElement() ; servo.write(pos);}}
        
        }
       if ((pos == 180 || pos == list.largestElement ()) ){mode = -1;}
       if ((pos == 0   || pos == list.smallestElement()) ){mode = 1 ;}
      }
    }
};

#endif
