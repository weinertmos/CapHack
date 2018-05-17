void check_buttons(){
    adc_key_prev = lcd_key ;      
    lcd_key = read_LCD_buttons();  
    switch (lcd_key)
    {
    case btnRIGHT:
        {
            soll += 10;
        break;
        }
    case btnLEFT:
        {
            soll -= 10;
        break;
        }
    case btnUP:
     {
       soll += 1;
         break;
      }
    case btnDOWN:
      {
        soll -= 1;
          break;
       }
      case btnSELECT:
       {
        Press(Pin_OnOff);
         break;
        }
      case btnNONE:
       {
         break;
       }
      }
}

// source: https://create.arduino.cc/projecthub/niftyjoeman/osepp-lcd-and-keypad-shield-d5b46e