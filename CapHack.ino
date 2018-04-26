// Libraries
#include <OneWire.h> // Dallas DS18B20

// Constants
#define DEBUG_MODE 1 // Set to 1 for debugging stuff

// Temperature
#define HOLY_TEMP 80 // [°C.] Target Temperature 
#define OFFSET_TEMP 10 // [°C.] Offset between actual and set temp
#define RANGE_TEMP 2 // [°C.] Deviation within current temp is considered close to target temp
#define START_TEMP 100 // [°C.] Starting Point for temp setting (first number that appears on the gadget display when switching into temp control mode)
#define INCREMENT_TEMP 5 // [C.] Incremental steps in Temp mode

// Power
#define STEPS_TO_MAX_POWER 10 // [int] How many times does the Up Button have to be pressed to reach MAX_POWER on gadget disaply after entering Power Control Mode (neg value if Down Button must be pressed)

#define TIME_SENSOR 750 // [ms] Time that Temperature Sensor needs for measurement
#define TIME_RESTART 5 // [min] Intervall after which gadget will be restarted

#define DURATION_PRESS 500 // [ms] How long a button gets pushed
#define DURATION_WAIT 1000 // [ms] How long to delay after pushing a button

// Pins
#define Pin_OnOff 0 // Capacitive On / Off Switch
#define Pin_Up 1 // Capacitive Up Button
#define Pin_Down 2 // Capacitive Down Button
#define Pin_SwitchPowerTemp 3 // Capacitive Switch between Temperature control or Power Control mode
#define Pin_Timer 4 // Capacitive Button to set Timer
#define Pin_Temp 10 // Yellow wire from DS18B20 at this pin

// Variables
unsigned long now = millis();
unsigned long TIME_SENSOR_OLD = millis(); // save current time for temperatuer sensor
unsigned long TIME_RESTART_OLD; // save current time for restarting gadget

boolean TempState = 0; // 0: current temp is far from target temp; 1: current temp is close to target temp
boolean TempState_OLD = 0; // save current State for comparison in next loop

double ist; 
int n_Temp; // determines how often the Up or Down Buttons must be pressed in order to reach target temp setting


// Temperature Sensor
OneWire ds(Pin_Temp); // initialize OneWire protocoll


// Files
#include "fn_getTemp.h" // get the current Temperature
#include <fn_Press.h> // Push a button
#include <fn_restart.h> // Restart gadget
#include <fn_SwitchToTempControl.h> // Switches to Temperature Control Mode and sets the necessary temp
#include <fn_SwitchToPowerControl.h> // Switches to Power Control Mode and Sets it to MAX_POWER 
#include <fn_check_restart.h> // Check if it is time to restart gadget
#include <fn_check_TempState.h> // check if current temp is close to target temp
#include <fn_testcycle.h> // Turn gadget on and see if all buttons are working
 
void setup()
{
  // Set Pin modes
  pinMode(Pin_OnOff, OUTPUT);
  pinMode(Pin_Up, OUTPUT);
  pinMode(Pin_Down, OUTPUT);
  pinMode(Pin_SwitchPowerTemp, OUTPUT);
  pinMode(Pin_Timer, OUTPUT);

  // Initialization
  delay(3000);
  testcycle(); // Turn gadget on for the first time and test all buttons
  SwitchToPowerControl(); // It is assumed that at start difference in target and actual temp is high

  if (DEBUG_MODE == 1)
  {
    Serial.begin(9600); // Activate Serial Communication
  }
}
 
void loop()
{
  // get time and check if a restart is necessary
  now = millis();
  check_restart();

  // get temp and check if it is close to target temp
  ist = getTemp();
  TempState = check_TempState(); // 0: not close; 1: close

  // If threshold (RANGE_TEMP) is reached change to Temperature Control Mode
  if ((TempState_OLD = 0) and (TempState = 1))
  {
    SwitchToTempControl();
  }

  // If difference in target vs. actual temp gets greater than RANGE_TEMP switch to Power Control Mode
  if ((TempState_OLD = 1) and (TempState = 0))
  {
    SwitchToPowerControl();
  }

  TempState_OLD = TempState; // store value for comparison in next loop

  if (DEBUG_MODE == 1)
  {
    Serial.print('waawwawaws');
  }
}