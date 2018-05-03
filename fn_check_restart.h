// Check if it is time to restart gadget
void check_restart()
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("Time remaining till Restart: ");
    Serial.print(float(float(TIME_RESTART)*1000*60 - (now - TIME_RESTART_OLD))/1000/60);
    Serial.println(" minutes");
  }

  if ((now - TIME_RESTART_OLD) >= float(TIME_RESTART)*1000*60)
  {
    if (DEBUG_MODE == 1)
    {
      Serial.print("Time for a fresh start. ");
      Serial.print(TIME_RESTART);
      Serial.println(" minutes have passed.");
      delay(5000);
    }

    TIME_RESTART_OLD = millis();

    if (DEBUG_MODE == 1)
    {
      Serial.print("TempState: ");
      Serial.println(TempState);
    }


    if (TempState == 0)
    {
        SwitchToPowerControl();
    }
    else if (TempState == 1)
    {
        SwitchToTempControl();
    }
  }
}