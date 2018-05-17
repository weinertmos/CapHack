// Switch between Power Control Mode and Temperature Control Mode
void check_switch()
{
  // If threshold (RANGE_TEMP) is reached change to Temperature Control Mode
  if ((TempState_OLD == 0) and (TempState == 1) and (hold == 0))
  {
    SwitchToTempControl();
  }

  // If difference in target vs. actual temp gets greater than RANGE_TEMP switch to Power Control Mode
  if ((TempState_OLD == 1) and (TempState == 0) and (hold == 1))
  {
    SwitchToPowerControl();
  }

  TempState_OLD = TempState; // store value for comparison in next loop
}