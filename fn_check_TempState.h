// check if current temp is close to target temp
int check_TempState()
{
  if (DEBUG_MODE == 1)
  {
    // Serial.print("TempState =  ");
    // Serial.println((TempState));
    // Serial.println(ist);
    // Serial.println(long(HOLY_TEMP) - long(RANGE_TEMP));
  }

  if (ist >= (float(HOLY_TEMP) - float(RANGE_TEMP)))
  {
    // Serial.println("returning 1");
    return 1;
  }
  else
  {
    // Serial.println("returning 0");
    return 0;
  }
}