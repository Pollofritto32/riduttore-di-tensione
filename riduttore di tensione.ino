void setup()
{
  pinMode (6, OUTPUT);   //setta la porta 11 come uscita
  setPwmFrequency(6, 8); //applica il divisore 64 sul timer del pin 11
}

void loop()
{
  int val = analogRead(1);                            //leggi valore potenziometro

  int conv= val / 4;                    // trasforma il segnale massimo da 1024 a 256

  analogWrite (6, conv); //genera  sul pin 11 un segnale con duty cicle 50% (127 nel range 0-255)
}

void setPwmFrequency(int pin, int divisor) //funzione per modificare la frequenza del PWM
{
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) //se il pin è uno di questi
  {
    switch (divisor) //in base al divisore scelto viene dato un valore esadecimale a "mode"
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6) //se il pin è il 5 o il 6 cambio il valore del registro TCCR0B
    {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else                    //altrimenti cambio il valore del registro TCCR1B
    {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if (pin == 3 || pin == 11) //se il pin è il 3 o 11 cambio il valore del registro TCCR2B
  {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
8kHz
