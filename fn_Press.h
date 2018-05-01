// Pushes a button, holds it and releases it
void Press(int button)
{
  digitalWrite(button, LOW);
  delay(DURATION_PRESS);
  digitalWrite(button, HIGH);
  delay(DURATION_WAIT);
}