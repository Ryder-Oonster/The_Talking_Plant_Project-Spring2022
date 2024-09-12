/*
  SparkFun Inventor’s Kit
  Circuit 4A-HelloWorld

  The LCD will display the words "Hello World" and show how many seconds have passed since
  the RedBoard was last reset.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display



/*-----------------------------------------------------------------------------------------------------------

/*  Soil Moisture Basic Example
    This sketch was written by SparkFun Electronics
    Joel Bartlett
    August 31, 2015

    Basic skecth to print out soil moisture values to the Serial Monitor

    Released under the MIT License(http://opensource.org/licenses/MIT)
*/

int val = 0; //value for storing moisture value
int soilPin = A0;//Declare a variable for the soil moisture sensor
int soilPower = 7;//Variable for Soil moisture Power

//Rather than powering the sensor through the 3.3V or 5V pins,
//we'll use a digital pin to power the sensor. This will
//prevent corrosion of the sensor as it sits in the soil.

int cond;

int const greenButtonPin = 6;
int greenButtonState = 0;

int const redButtonPin = 5;
int redButtonState = 0;

int const blueButtonPin = 4;
int blueButtonState = 0;

int moistMin;
int moistMax;
int plantType = 1;

int rs;


void setup()
{
  Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor

  // Kill me
  pinMode(greenButtonPin, INPUT);
  pinMode(redButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);


  //lcd commands

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
}

void loop()
{
Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
Serial.println(readSoil());

greenButtonState = digitalRead(greenButtonPin);
redButtonState = digitalRead(redButtonPin);
blueButtonState = digitalRead(blueButtonPin);

//lcd commands.

//Possible alternate fix: lcd.clear();
lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
lcd.print("H2O (ppt)= ");       //print Moisture Level starting at that position
lcd.print(readSoil());
rs = readSoil();

                      // Tropical plant, normal plant, cactus
                      // Normal: 290 min, 435 max
                      // Tropical: 150 min, 400 max
                      // Cactus: 30 min, 150 max

                      
                      if (greenButtonState == HIGH) {
                        plantType = 1;
                        moistMin = 290;
                        moistMax = 435 *2;
                      }
                      else if (redButtonState == HIGH) {
                        plantType = 2;
                        moistMin = 30;
                        moistMax = 150 *2;
                      }
                      else if (blueButtonState == HIGH) {
                        plantType = 3;
                        moistMin = 150;
                        moistMax = 400 *2;
                      }
                      else {
                        plantType = plantType;
                        moistMin = moistMin;
                        moistMax = moistMax;
                      }

                      
                     
                      // Condition for Satisfactory moisture
                     if (moistMin <= rs && rs <= moistMax) {
                     lcd.setCursor(0, 1);
                     lcd.print("Good on Water!");
                     Serial.println("Good on Water!");
                      }
                       else if (((0.75*moistMin) <= rs && rs < moistMin)) {
                      // Condition for low moisture
                      lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
                      lcd.print("More water plz:)");
                      Serial.println("More water plz:)");
                      }
                      else if ((rs < (0.75*moistMin))) {
                      // Condition for super low moisture
                      lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
                      lcd.print("Dying of thirst");
                      Serial.println("Dying of thirst");
                      }
                      else if (moistMax < rs <= (1.25*moistMax)) {
                      // Condition for high moisture
                      // 
                      lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
                      lcd.print("Enough H2O!");
                      Serial.println("Enough H2O!");
                      }
                      else if ((1.25*moistMax) < rs) {
                        // Condition for super high moisture
                        lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
                        lcd.print("Too much!");
                        Serial.println("Too much!");
                      }
                      else if (cond == 6) {
                        // Test cond
                        lcd.setCursor(0, 1);              //move the cursor to the first space of the bottom row
                        lcd.print("Ok");
                        Serial.println(greenButtonState);
                      }
                      else {
                        // Detection error
                        lcd.clear();
                        lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
                        lcd.print("Err");              //move the cursor to the first space of the bottom row
                      }
                      
//This 1 second timefrme is used so you can test the sensor and see it change in real-time.
//For in-plant applications, you will want to take readings much less frequently.


delay(1000);//take a reading every second
}
//This is a function used to get the soil moisture content
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds
    val = analogRead(soilPin);//Read the SIG value form sensor
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}
