// Libraries
#include <OneWire.h> // Dallas DS18B20
#include <LiquidCrystal.h>

// Constants
#define DEBUG_MODE 1 // Set to 1 for debugging stuff

// Temperature
#define HOLY_TEMP 50 // [°C.] Target Temperature 
#define OFFSET_TEMP 1 // [°C.] Offset between actual and set temp
#define RANGE_TEMP 2 // [°C.] Deviation within current temp is considered close to target temp
#define START_TEMP 100 // [°C.] Starting Point for temp setting (first number that appears on the gadget display when switching into temp control mode)
#define INCREMENT_TEMP 5 // [C.] Incremental steps in Temp mode

// Power
#define STEPS_TO_MAX_POWER 6 // [int] How many times does the Up Button have to be pressed to reach MAX_POWER on gadget disaply after entering Power Control Mode (neg value if Down Button must be pressed)

#define TIME_SENSOR 750 // [ms] Time that Temperature Sensor needs for measurement
#define TIME_RESTART 5 // [min] Intervall after which gadget will be restarted

#define DURATION_PRESS 250 // [ms] How long a button gets pushed (250)
#define DURATION_WAIT 100 // [ms] How long to delay after pushing a button (1000)

// Pins
#define Pin_OnOff 2 // Capacitive On / Off Switch
#define Pin_Up 3 // Capacitive Up Button
#define Pin_Down 11 // Capacitive Down Button
#define Pin_SwitchPowerTemp 12 // Capacitive Switch between Temperature control or Power Control mode
#define Pin_Temp 13 // Yellow wire from DS18B20 at this pin

// Variables
unsigned long now = millis();
unsigned long TIME_SENSOR_OLD = millis(); // save current time for temperatuer sensor
unsigned long TIME_RESTART_OLD; // save current time for restarting gadget

boolean TempState = 0; // 0: current temp is far from target temp; 1: current temp is close to target temp
boolean TempState_OLD = 0; // save current State for comparison in next loop

double ist; 
double soll = HOLY_TEMP;
int n_Temp; // determines how often the Up or Down Buttons must be pressed in order to reach target temp setting
float rest;


// Temperature Sensor
OneWire ds(Pin_Temp); // initialize OneWire protocoll

// LCD
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);


// Files
#include "fn_getTemp.h" // get the current Temperature
#include "fn_Press.h" // Push a button
#include "fn_restart.h" // Restart gadget
#include "fn_SwitchToTempControl.h" // Switches to Temperature Control Mode and sets the necessary temp
#include "fn_SwitchToPowerControl.h" // Switches to Power Control Mode and Sets it to MAX_POWER 
#include "fn_check_restart.h" // Check if it is time to restart gadget
#include "fn_check_TempState.h" // check if current temp is close to target temp
#include "fn_testcycle.h" // Turn gadget on and see if all buttons are working
#include "fn_UpdateLCD.h" // Update text on LCD
 
void setup()
{
  if (DEBUG_MODE == 1)
  {
    Serial.begin(9600); // Activate Serial Communication
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println("Debug Mode on");
  }

  // Start up LCD
  lcd.begin(16, 2);
  getTemp();
  ist = getTemp();
  UpdateLCD();


  // Set Pin modes
  pinMode(Pin_OnOff, OUTPUT);
  digitalWrite(Pin_OnOff, HIGH);
  pinMode(Pin_Up, OUTPUT);
  digitalWrite(Pin_Up, HIGH);
  pinMode(Pin_Down, OUTPUT);
  digitalWrite(Pin_Down, HIGH);
  pinMode(Pin_SwitchPowerTemp, OUTPUT);
  digitalWrite(Pin_SwitchPowerTemp, HIGH);

  // Initialization
  delay(3000);
  if (DEBUG_MODE == 1)
  {
    Serial.println("Starting Testcycle");
  }

  TIME_RESTART_OLD = millis();
  testcycle(); // Turn gadget on for the first time and test all buttons
  SwitchToPowerControl(); // It is assumed that at start difference in target and actual temp is high
  // SwitchToTempControl();
}
 
void loop()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println(" ");
    Serial.println(" ");
    Serial.println("New Loop");
    delay(2000);
  }

  // get time and check if a restart is necessary
  now = millis();
  check_restart();

  // get temp and check if it is close to target temp
  getTemp();
  ist = getTemp(); // do it twice to get correct values in OneWire Protocoll
  if (Serial.available() > 0)
  {
    ist = Serial.parseInt();
    while (Serial.available() >0)
      rest = Serial.read();
  }

  Serial.print("ist: ");
  Serial.println(ist);
  TempState = check_TempState(); // 0: not close; 1: close

  // If threshold (RANGE_TEMP) is reached change to Temperature Control Mode
  if ((TempState_OLD == 0) and (TempState == 1))
  {
    SwitchToTempControl();
  }

  // If difference in target vs. actual temp gets greater than RANGE_TEMP switch to Power Control Mode
  if ((TempState_OLD == 1) and (TempState == 0))
  {
    SwitchToPowerControl();
  }

  TempState_OLD = TempState; // store value for comparison in next loop

  if (DEBUG_MODE == 1)
  {
    Serial.println("End of Loop");
    Serial.println(" ");
  }
UpdateLCD();
}