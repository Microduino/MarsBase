
uint32_t sunlebroll;
uint32_t weatherroll;
uint8_t lighthousemode = 1, lighthousecolor = 1;

uint8_t sunsend, sunsendC;
uint8_t soilsta, soilstaC;
uint8_t temsta, temstaC;

void runlight()
{
  switch (key)
  {
    case JOYLEFT:
      lighthousecolor++;
      if (lighthousecolor > 4)
        lighthousecolor = 1;
      break;
    case JOYRIGHT:
      lighthousecolor--;
      if (lighthousecolor < 1)
        lighthousecolor = 4;
      break;
    case JOYUP:
      lighthousemode--;
      if (lighthousemode < 1 )
        lighthousemode = 2;
      break;
    case JOYDOWN:
      lighthousemode++;
      if (lighthousemode > 2)
        lighthousemode = 1;
      break;
    default:
      break;
  }
  lighthouse(lighthousemode, lighthousecolor);
}

void runsun()
{
  if (analogRead(SUNPIN) > LIGHT_TRIGGER)
  {
    noTone(BUZZERPIN);
    sunshow(COLOR_COLD);
    sunsend = 1;
    sunlebroll = millis();
  }
  else
  {
    sunsend = 2;
    sunshow(COLOR_WARM);
    if (millis() - sunlebroll > 3000)
      tone(BUZZERPIN, 1000);
  }

  if (sunsendC != sunsend)
  {
    switch (sunsend)
    {
      case 1:
        uploaddata("mode", 21);
        delay(30);
        uploaddata("sun", "true");
        delay(30);
        break;
      case 2:
        uploaddata("mode", 22);
        delay(30);
        uploaddata("sun", "false");
        delay(30);
        break;
      default:
        break;
    }
    sunsendC = sunsend;
  }
}

void runweather()
{
  if (tem < TEMMIN || tem > TEMMAX)
  {
    weathershow(COLOR_WARM);
    tone(BUZZERPIN, 1000);
  }
  else
  {
    weathershow(COLOR_COLD);
    noTone(BUZZERPIN);
  }

  if (tem < TEMMIN)
    temsta = 2;
  else if (tem > TEMMAX)
    temsta = 3;
  else
    temsta = 1;

  if (temstaC != temsta)
  {
    switch (temsta)
    {
      case 1:
        uploaddata("mode", 16);
        break;
      case 2:
        uploaddata("mode", 17);
        break;
      case 3:
        uploaddata("mode", 18);
        break;
      default:
        break;
    }
    temstaC = temsta;
  }
}

void runsoil()
{
  if (soil > SOILMAX)
  {
    soilshow(COLOR_WARM);
    tone(BUZZERPIN, 1200);
    soilsta = 2;
  }
  else
  {
    soilshow(COLOR_COLD);
    noTone(BUZZERPIN);
    soilsta = 1;
  }

  if (soilstaC != soilsta)
  {
    switch (soilsta)
    {
      case 1:
        uploaddata("mode", 19);
        break;
      case 2:
        uploaddata("mode", 20);
        break;
      default:
        break;
    }
    soilstaC = soilsta;
  }
}

void runsound()
{
  if (key == JOYUP || key == JOYDOWN)
    soundsta = !soundsta;
}

void runmatrix()
{
  //  if (mMatrix == -1)
  //  {
  //    display.clearDisplay();
  //    mode = MODEHOME;
  //    intoitem = 0;
  //  }
  //  else
  //  {
  mx = mMatrix / 100;
  my = (mMatrix % 100) / 10;
  mval = mMatrix % 10;
  //  }

  if (KeyG.read() == SHORT_PRESS || mBack == 1)  //返回
  {
    intoitem = false;
    mBack = 0;
  }
}

