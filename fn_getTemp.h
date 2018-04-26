// Temperatursensor auslesen
float getTemp() {
  byte i;
  byte present = 0;
  byte type_s = 0; // für DS18B20
  byte data[12];
  byte addr[8];
  float celsius;

  if ( !ds.search(addr)) {
    //Serial.println("No more addresses.");
    //Serial.println();
    ds.reset_search();
    //delay(2000);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
  }

  now = millis();
  if ((now - TIME_SENSOR_OLD) >= TIME_SENSOR) { // Wenn Wartezeit abgelaufen ist, soll neue Temperatur angefragt werden
    TIME_SENSOR_OLD = millis(); // Vergleichszeit neu setzen, damit nicht staendig angefragt wird
    //Serial.println();

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1); //Konversion starten = Befehl an Sensor, Temperatur zu ermitteln
  }


  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Befehl an Sensor, Temperatur (bitweise) zu uebermitteln

  for ( i = 0; i < 9; i++) { //9 bytes auslesen = Temperatur in Empfang nehmen
    data[i] = ds.read();
  }


  // Daten in Temperatur umwandeln

  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw & ~7; //9 bit Auflösung, 93,75ms
  else if (cfg == 0x20) raw = raw & ~3; //10 bit Auflösung, 187,5ms
  else if (cfg == 0x40) raw = raw & ~1; //11 bit Auflösung, 375ms

  // Sollte es nicht gehen, mit 12 bit Auflösung probieren:
  /*
  if (type_s){
   raw = raw << 3; // noch 9 bit Auflösung
   if (data[7] == 0x10) {
   raw = (raw & 0xFFF0) +12 -data[6];
   }
   }
   */
  celsius = (float)raw / 16.0;
  return (celsius);
}
