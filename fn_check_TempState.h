// check if current temp is close to target temp
int check_TempState(){
  if (ist >= (float(soll) + (float(RANGE_TEMP)/2)))
  {
    // Serial.println("returning 1");
    return 1;
  }
  else if (ist <= (float(soll) - (float(RANGE_TEMP)/2)))
  {
    // Serial.println("returning 0");
    return 0;
  }
  else{
    return TempState;
  }
}