// Switches to Temperature Control Mode and sets the necessary temp
void SwitchToTempControl()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Switching to Temperature Control Mode");
  }

  restart();
  Press(Pin_SwitchPowerTemp);
  if (soll < START_TEMP)
  {
    n_Temp = int((START_TEMP - soll - OFFSET_TEMP) / INCREMENT_TEMP + 0.5);
    Serial.print("n_Temp1: ");
    Serial.println(n_Temp);
    for (int i = 0; i < n_Temp;  i++)
    {
      Press(Pin_Down);
    }
  }

  else if (soll > START_TEMP)
  {
    n_Temp = int((START_TEMP - soll - OFFSET_TEMP) / INCREMENT_TEMP + 0.5);
    Serial.print("n_Temp2: ");
    Serial.println(n_Temp);
    for (int i = 0; i <= -n_Temp; i++)
    {
      Press(Pin_Up);
    }
  }
  hold = 1;

}