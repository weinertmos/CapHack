// Switches to Temperature Control Mode and sets the necessary temp
void SwitchToTempControl()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Switching to Temperature Control Mode");
  }

  restart();
  Press(Pin_SwitchPowerTemp);
  if (HOLY_TEMP < START_TEMP)
  {
    n_Temp = (START_TEMP - HOLY_TEMP - OFFSET_TEMP) % INCREMENT_TEMP;
    for (int i = 0; i < n_Temp;  i++)
    {
      Press(Pin_Down);
    }
  }

  else if (HOLY_TEMP > START_TEMP)
  {
    n_Temp = (START_TEMP - HOLY_TEMP + OFFSET_TEMP) % INCREMENT_TEMP;
    for (int i = 0; i < -n_Temp; i++)
    {
      Press(Pin_Up);
    }
  }

}