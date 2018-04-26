// check if current temp is close to target temp
bool check_TempState()
{
  if (ist >= (HOLY_TEMP - RANGE_TEMP))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}