// This sketch monitors battery voltage and turns on an LED based on it.
// Processor: ATtiny 13.
// Author: Rafael Larios
// Date: 13.09.03
//

int rLED = 4;                  //Red LED pin
int yLED = 1;                  //Yellow LED pin
int gLED = 2;                  //Green LED pin
int val = 0;                         //This variable will hold voltage input value
int dlyctr = 0;                      //This is the delay counter.

void setup(){
  pinMode(rLED, OUTPUT);            //Define Red LED output
  pinMode(yLED, OUTPUT);            //ditto Yellow LED
  pinMode(gLED, OUTPUT);            //ditto Green LED
}

void loop(){
  val = analogRead(A3);              //Read voltage through Analog input 0
  if(val<446){                      //Is battery voltage below 9.6V?
    digitalWrite(rLED, HIGH);       //Yes, this is bad, turn on Red LED
    digitalWrite(yLED, LOW);        //Turn off Yellow LED
    digitalWrite(gLED, LOW);        //Turn off Green LED
  }
  else
  {
    if(val<586){                    //Is battery voltage between 9.6V and 12.4V?
      digitalWrite(rLED, LOW);      //This is a low voltage, turn off red LED
      digitalWrite(yLED, HIGH);     //Turn on Yelow LED as a warning.
      digitalWrite(gLED, LOW);      //Turn off Green LED
    }
    else
    {
      if(val<621){                  //Is battery voltage between 12.4V and 13.1V?
        digitalWrite(rLED, LOW);    //Yes, turn off Red LED
        digitalWrite(yLED, LOW);    //Turn off Yellow LED
        digitalWrite(gLED, HIGH);   //Turn on Green LED to indicate fully charged battery voltage.
      }
      else
      {
        dlyctr = dlyctr + 1;        //increase delay counter. every pass approx. 100ms
        if(val<742){                      //Is battery voltage above 13.1V and below 15.5V?
          digitalWrite(rLED, LOW);         //Turn off red LED
          digitalWrite(yLED, LOW);        //Turn off yellow LED
          if(dlyctr<6){
            digitalWrite(gLED, HIGH);     //Pulse green LED on for half a second
          }
          else
          {
            digitalWrite(gLED, LOW);      //Pulse green LED off for half a second to show battery is charging.
            if(dlyctr>10){
              dlyctr=0;                   //Reset delay counter
            }
          }
        }
        else                              //Battery voltage is above 15.5V.Danger ! Overcharge
        {
          digitalWrite(yLED, LOW);        //Turn off Yellow LED
          digitalWrite(gLED, LOW);        //Turn off Green LED
          if(dlyctr<6){
            digitalWrite(rLED, HIGH);     //Turn on Red LED for half a second.
          }
          else
          {
            digitalWrite(rLED, LOW);      //Turn off Red LED for half a second.
            if(dlyctr>10){
              dlyctr=0;                   //Reset delay counter
            }
          }
        }
       delay(100);                        //Stop program 100 milliseconds to help pulse LEDs.
      }
    }
  }
}

