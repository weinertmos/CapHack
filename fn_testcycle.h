// Turn gadget on and see if all buttons are working
void testcycle()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Starting Testcycle");
  }
  // Press(Pin_OnOff);
  Press(Pin_Up);
  Press(Pin_Down);
  // Press(Pin_Timer);
  // Press(Pin_Timer);
  Press(Pin_SwitchPowerTemp);
  Press(Pin_SwitchPowerTemp);
  Press(Pin_OnOff);
  Press(Pin_OnOff);
  if (DEBUG_MODE == 1)
  {
    Serial.println("Testcycle finished");
  }

}