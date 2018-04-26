// Check if it is time to restart gadget
void check_restart()
{
  if ((now - TIME_RESTART_OLD) >= TIME_RESTART)
  {
    if (TempState = 0)
    {
        SwitchToPowerControl();
    }
    else if (TempState = 1)
    {
        SwitchToTempControl();
    }
  }
}