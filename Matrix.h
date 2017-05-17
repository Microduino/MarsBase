#include <Microduino_Matrix.h>

uint8_t Addr[MatrixPix_X][MatrixPix_Y] = {  //1x1
  { 48}
};

Matrix display = Matrix(Addr, TYPE_S2);
//低位在前 逐行
static const uint8_t logo[] PROGMEM = {
  0x00, 0x18, 0x24, 0x42, 0x24, 0x24, 0x3C, 0x00
};

static const uint8_t snake[] PROGMEM = {
  0x00, 0x00, 0x04, 0x6E, 0x04, 0x18, 0x00, 0x00
};
static const uint8_t sankeinto[] PROGMEM = {
  0x00, 0x40, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00
};
static const uint8_t soilHum[] PROGMEM = {
  0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF
};

static const uint8_t light[] PROGMEM = {
  0x00, 0x5A, 0x24, 0x24, 0x7E, 0x18, 0x18, 0x7E
};
static const uint8_t lightinto[] PROGMEM = {
  0x00, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x00
};

static const uint8_t weather[] PROGMEM = {
  0x00, 0x3A, 0x44, 0x04, 0x04, 0x44, 0x38, 0x00
};

static const uint8_t news[] PROGMEM = {
  0x00, 0x00, 0x7E, 0x5A, 0x42, 0x42, 0x7E, 0x00
};

static const uint8_t sun[] PROGMEM = {
  0x18, 0x42, 0x18, 0xA5, 0xA5, 0x18, 0x42, 0x18
};
static const uint8_t suninto[] PROGMEM = {
  0x00, 0x00, 0x00, 0xB6, 0xB6, 0x00, 0x00, 0x00
};

static const uint8_t sound[] PROGMEM = {
  0x00, 0x30, 0x50, 0x10, 0x10, 0x1C, 0x1C, 0x00
};
static const uint8_t soundon[] PROGMEM = {
  0x00, 0x00, 0x97, 0xB5, 0xD5, 0x97, 0x00, 0x00
};
static const uint8_t soundoff[] PROGMEM = {
  0x78, 0x28, 0xFF, 0x2B, 0x2B, 0x2B, 0x28, 0x3C
};

int16_t tone_list[7] = {262, 294, 330, 349, 392, 440, 494};

int32_t weathermatrix, soilmatrix, msgmatrix;
uint8_t lednumber;
int32_t x = display.getWidth() * 8;
int32_t y = display.getWidth() * 8;
int32_t z = display.getWidth() * 8;

boolean soundsta, soundsta_c;

uint8_t key, keyC;

void initmatrix()
{
  //display.setBrightness(188);
  display.clearDisplay();
  x = display.getHeight() * 8;
  for (int y = 0; y < display.getHeight() * 8; y++) {
    for (int x = 0; x < display.getWidth() * 8; x++) {
      display.setLedBrightness(x, y, 100);   //x, y, brightness
      delay(15);
    }
  }
  delay(1000);
  display.clearDisplay();
}

void move_matrix(uint8_t wait)
{
  if (millis() - weathermatrix > wait)
  {
    if (x == display.getWidth() * 8)
    {
      uploaddata("temC", tem);
      delay(100);
      uploaddata("temF", temf);
    }
    x--;
    if (x < -(temlength * 5) - display.getWidth() * 8)
    {
      x = display.getWidth() * 8;
      display.clearDisplay();
      getweather();
    }
    display.setCursor(x, 0);   //x, y
    display.print(weathers);
    weathermatrix = millis();
  }
}

void soil_matrix(uint8_t wait)
{
  if (millis() - soilmatrix > wait)
  {
    if (y == display.getWidth() * 8)
    {
      uploaddata("soil", soils);
      delay(100);
    }
    y--;
    if (y < -(soillength * 5) - display.getWidth() * 8)
    {
      y = display.getWidth() * 8;
      display.clearDisplay();
      Soilmoisture();
    }
    display.setCursor(y, 0);   //x, y
    display.print(soils);
    soilmatrix = millis();
  }
}

void msg_matrix(uint8_t wait)
{
  if (millis() - msgmatrix > wait)
  {
    z--;
    if (z < -(msglength * 6) - display.getWidth() * 8)
    {
      z = display.getWidth() * 8;
      display.clearDisplay();
    }
    display.setCursor(z, 0);   //x, y
    display.print(myMsg);
    msgmatrix = millis();
  }
}

void menumatrix(uint8_t _mode)
{
  switch (_mode)
  {
    case MODEHOME:
      display.drawBMP(0, 0, 8, 8, logo);
      break;
    case MODESOIL:
      display.drawBMP(0, 0, 8, 8, soilHum);
      break;
    case MODELIGHT:
      display.drawBMP(0, 0, 8, 8, light);
      break;
    case MODESUN:
      display.drawBMP(0, 0, 8, 8, sun);
      break;
    case MODEWEATHER:
      display.drawBMP(0, 0, 8, 8, weather);
      break;
    case MODESOUND:
      display.drawBMP(0, 0, 8, 8, sound);
      break;
    case MODEMATRIX:
      mode = MODEHOME;
      break;
    default:
      break;
  }
}

void itemmatrix(uint8_t _mode)
{
  switch (_mode)
  {
    case MODEHOME:
      if (myMsgC != myMsg)
      {
        z = display.getWidth() * 8; //恢复留言起始坐标
        display.clearDisplay();
        myMsgC = myMsg;
      }
      msg_matrix(100);
      break;
    case MODESOIL:
      soil_matrix(120);
      break;
    case MODELIGHT:
      display.drawBMP(0, 0, 8, 8, lightinto);
      break;
    case MODESUN:
      display.drawBMP(0, 0, 8, 8, suninto);
      break;
    case MODEWEATHER:
      move_matrix(120);
      break;
    case MODESOUND:
      if (soundsta)
        display.drawBMP(0, 0, 8, 8, soundon);
      else
        display.drawBMP(0, 0, 8, 8, soundoff);
      break;
    case MODEMATRIX:
      display.setLed(mx, my, mval);
      break;
    default:
      break;
  }
}
