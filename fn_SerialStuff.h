// Stuff for Serial Connection
void SerialStuff()
{
  if (Serial.available() > 0)
  {
    ist = Serial.parseInt();
    while (Serial.available() >0)
      rest = Serial.read();
  }
  Serial.print("ist: ");
  Serial.println(ist);
}