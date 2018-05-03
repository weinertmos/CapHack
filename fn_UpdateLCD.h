void UpdateLCD()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println(" ");
    Serial.println("Updating Display...");
  }
lcd.clear();
lcd.setCursor(0,0);
lcd.print("i:");
lcd.print(ist);
lcd.print((char)223);
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("s:");
lcd.print(soll);
lcd.print((char)223);
lcd.print("C");
if (TempState == 0)
{
  lcd.setCursor(12,1);
  lcd.print("Heat");
}
else if (TempState == 1)
{
  lcd.setCursor(12,1);
  lcd.print("Hold");
}
}