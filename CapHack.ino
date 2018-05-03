// Libraries
#include <OneWire.h> // Dallas DS18B20
#include <LiquidCrystal.h> // LCD

// Constants
#define DEBUG_MODE 1 // default 0 0; set to 1 for debugging stuff to appear

// Temperature
#define HOLY_TEMP 22 // [°C.] Target Temperature 
#define OFFSET_TEMP 1 // [°C.] Offset between actual and set temp (depending on heat transfer, water volume etc.)
#define RANGE_TEMP 2 // [°C.] Range for current temp which is considered close to target temp
#define START_TEMP 100 // [°C.] Starting Point for temp setting (first number that appears on the gadget display when switching into temp control mode)
#define INCREMENT_TEMP 5 // [C.] Incremental steps in Temp mode
#define LOOP_DELAY 1 // [ms] Pause between Loops

// Power
#define STEPS_TO_MAX_POWER 6 // [int] How many times does the Up Button have to be pressed to reach MAX_POWER on gadget disaply after entering Power Control Mode

#define TIME_SENSOR 750 // [ms] Time that Temperature Sensor needs for measurement
#define TIME_RESTART 5 // [min] Intervall after which gadget will be restarted (to prevent shutdown)

#define DURATION_PRESS 250 // [ms] How long a button gets pushed (250)
#define DURATION_WAIT 100 // [ms] How long to wait after pushing a button (1000)

// Pin numbers 
#define Pin_OnOff 2 // Capacitive On / Off Switch
#define Pin_Up 3 // Capacitive Up Button
#define Pin_Down 11 // Capacitive Down Button
#define Pin_SwitchPowerTemp 12 // Capacitive Switch between Temperature Control Mode and Power Control Mode
#define Pin_Temp 13 // Yellow wire from DS18B20 at this pin

// Analog Buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Variables
unsigned long now = millis();
unsigned long TIME_SENSOR_OLD = millis(); // store current time for temperature sensor
unsigned long TIME_RESTART_OLD = millis(); // store current time for restarting gadget
unsigned long count = 1;

boolean TempState = 0; // 0: current temp is far from target temp; 1: current temp is close to target temp
boolean TempState_OLD = 0; // store current State for comparison in next loop

double ist; 
double soll = HOLY_TEMP;
int n_Temp; // determines how often the Up or Down Buttons must be pressed in order to reach target temp setting
float rest; // dump for overhead serial messages

// Variables for Analog Buttons
int lcd_key       = 0;
int adc_key_in    = 0;
int adc_key_prev  = 0;



// Temperature Sensor
OneWire ds(Pin_Temp); // initialize OneWire protocoll

// LCD
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);


// other Files
#include "fn_getTemp.h" // get the current Temperature
#include "fn_Press.h" // Push a button
#include "fn_restart.h" // Restart gadget
#include "fn_SwitchToTempControl.h" // Switches to Temperature Control Mode and sets the necessary temp
#include "fn_SwitchToPowerControl.h" // Switches to Power Control Mode and Sets it to MAX_POWER 
#include "fn_check_restart.h" // Check if it is time to restart gadget
#include "fn_check_TempState.h" // check if current temp is close to target temp
#include "fn_testcycle.h" // Turn gadget on and see if all buttons are working
#include "fn_UpdateLCD.h" // Update text on LCD
#include "fn_SerialStuff.h" // Serial Connection
#include "fn_check_switch.h" // Switch between Power Control Mode and Temperature Control Mode
#include "fn_read_LCD_buttons.h" // Reads the analog values from A0
#include "fn_check_buttons.h" // Check if Analog Buttons are pressed and act accordingly

 
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

  lcd.begin(16, 2);
  ist = getTemp(); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Starting");
  lcd.setCursor(0,1);
  lcd.print("Testcycle...");


  // Set Pin modes
  pinMode(Pin_OnOff, OUTPUT);
  digitalWrite(Pin_OnOff, HIGH);
  pinMode(Pin_Up, OUTPUT);
  digitalWrite(Pin_Up, HIGH);
  pinMode(Pin_Down, OUTPUT);
  digitalWrite(Pin_Down, HIGH);
  pinMode(Pin_SwitchPowerTemp, OUTPUT);
  digitalWrite(Pin_SwitchPowerTemp, HIGH);

  // Warm up2
  delay(1000);
  testcycle(); // Turn gadget on for the first time and test all buttons
  SwitchToPowerControl();
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

  // do the important things
  now = millis();
  check_restart();
  ist = getTemp();
  getTemp(); // Second message from OneWire Protocoll not needed
  SerialStuff();
  TempState = check_TempState(); // 0: not close; 1: close
  UpdateLCD();
  check_switch();
  check_buttons();
  if (DEBUG_MODE == 1)
  {
    Serial.println("End of Loop");
    Serial.println(" ");
  }
delay(LOOP_DELAY);
}