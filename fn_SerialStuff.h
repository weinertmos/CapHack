// Stuff for Serial Connection
void SerialStuff()
{
  if (Serial.available() > 0)
  {
    ist = Serial.parseInt();
    while (Serial.available() >0)
      rest = Serial.read();
  }
  if (DEBUG_MODE == 1)
  {
  Serial.print("ist: ");
  Serial.println(ist);
  Serial.print("soll: ");
  Serial.println(soll);
    }
}