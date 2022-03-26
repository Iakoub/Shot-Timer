#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128                          // OLED display width,  in pixels
#define SCREEN_HEIGHT 64                          // OLED display height, in pixels

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // declare an SSD1306 display object connected to I2C

int solPin = 7;                                   // solenoid switch to digital pin 21

int sol;
double sec = 0;                                   // seconds variable
double currentMillis;                             // snapshot millis
double startMillis = millis();                    // start millis from code start

void setup() {
  Serial.begin(9600);                             // Enable Serial

  pinMode(solPin, INPUT);                         // reed switch pin position
  digitalWrite(solPin, HIGH);                     // reed switch pull up

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // initialize OLED display with address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
    oled.setTextColor(WHITE);                     // text color
}


void loop() {
  String finalTime = "";
  int x1 = 46;
  int y1 = 10;
  
  sol = digitalRead(solPin);                      // read the input pin of the reed switch
  oled.clearDisplay();
  finalTime = String(sec, 1);

  oled.setTextSize(2);                            // text size
  oled.setCursor(31, 16);                         // center next text
  oled.println("Silvia");                         // text to display
  oled.setCursor(36, 34);
  oled.println("Ready");
  oled.display();                                 // show on OLED
  oled.clearDisplay();

    if (sol == LOW){                              // monitor for reed switch state and if triggered execute order 66, I mean the following code
     startMillis = millis();                      // start counting milliseconds

     while(sol == LOW){                           // while the reed switch remains closed (triggered) keep displaying the timer
      currentMillis = millis();                   // take a snapshot of millisecond
      sec = (currentMillis - startMillis)/1000;   //do maths to deduct start milliseons from snapshot milliseconds to basically get 0 and divide by 1000 to get value in seconds

      oled.setCursor(x1, y1);                     // set cursor position dependant on variables x1 and y1   
      oled.print(sec, 1);                         // send the seconds elapsed from trigger of reed switch (to 1 decimal place)   
      oled.print("s");                            // print the s for seconds
      oled.display();
      oled.clearDisplay();
      sol = digitalRead(solPin);                  // check the state of the solenoid reed switch

      if (sec >= 9.9){                            // depending on whether more or less than 10s have passed, adjust the cursor position
        x1 = 36;
        y1 = 10;
      } else {
        x1 = 46;
        y1 = 10;
      }  
     
      if (sol == HIGH && sec <= 24){              // in the case the reed switch opens again and the brew process was less than 24s (brew process is over) execute the following
          oled.clearDisplay();                    // clear display
          finalTime = String(sec, 1);             // convert the time of the shot to a string with 1 decimal place
          if (sec <= 9.99){                       // adjust the cursor position depending on whether the time is more or less than 10
            x1 = 46;
            y1 = 10;            
          } else {
            x1 = 36;
            y1 = 10;
          }
          callDisp(2, x1, y1, finalTime);         // call the function to print the final time
          oled.print("s");                        // print s for seconds
          callDisp(1, 31, 45, "Grind Finer!");    // scold the user to grind finer
          delay (2500);                           // keep the message displayed for 2.5s
        } else if (sol == HIGH) {                 // if the brew process was more than 24s 
          oled.clearDisplay();
          finalTime = String(sec, 1);
          callDisp(2, x1, y1, finalTime);
          oled.print("s");
          callDisp(1, 36, 40, "Nice Shot!");      // praise the user
          delay (2500);
        }
      }
   }
}

void callDisp(int i, int x, int y, String thing){ // purely to keep the code a little bit cleaner in a couple instances
    oled.setTextSize(i);                          // text size
    oled.setCursor(x, y);                         // set cursor position
    oled.print(thing);                            // text to display
    oled.display();                               // show on OLED
}
