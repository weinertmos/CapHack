// Switches to Power Control Mode and Sets it to MAX_POWER 
void SwitchToPowerControl()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Switching to Power Control Mode");
  }
  
  restart();
  for (int i = 0; i < abs(STEPS_TO_MAX_POWER); i++)
  {
    if (STEPS_TO_MAX_POWER > 0)
    {
      Press(Pin_Up);
    }
    else if (STEPS_TO_MAX_POWER < 0)
    {
      Press(Pin_Down);
    }
  }

}