// Pushes a button, holds it and releases it
void Press(int button)
{
  digitalWrite(button, HIGH);
  delay(DURATION_PRESS);
  digitalWrite(button, LOW);
  delay(DURATION_WAIT);
}