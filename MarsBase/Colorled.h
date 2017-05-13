#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel  pixsoil = Adafruit_NeoPixel(10, SOILLED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel  pixsun = Adafruit_NeoPixel(10, SUNLED, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel  pixweather = Adafruit_NeoPixel(10, WEATHERLED, NEO_GRB + NEO_KHZ800);

#define COLOR_MAX 255   //Max value for ColorLED 
#define COLOR_MIN 0     //Min value for ColorLED

#define COLOR_NONE    0    //colorLED OFF
#define COLOR_RED     1
#define COLOR_ORANGE  2
#define COLOR_BLUE    3
#define COLOR_GREEN   4
#define COLOR_YELLOW  5
#define CoLOR_LIME    6
#define COLOR_INDIGO  7
#define COLOR_WARM    8
#define COLOR_COLD    9

#define LEDMODEBREATH   1
#define LEDMODEBLINK    2

//Array to hold preset colors.
const uint16_t colorArray[10][3] = {
  {0,   0,   0   },        //colorLED OFF
  {255, 0,   0   },        //Red
  {234, 139, 0   },        //Orange
  {0,   0,   255 },        //Blue
  {0,   255, 0   },        //Green
  {255, 255, 0   },        //Yellow
  {0,   255, 255 },        //Lime
  {255, 0,   255 },        //Purple
  {155, 100, 0   },        //Warm
  {100, 130, 100 }        //Cold
};

uint32_t breathTimer;
uint32_t blinkTimer;

int8_t num = 5, lednum = 5;

void soilshow(uint8_t color)
{
  for (uint8_t i = 0; i < pixsoil.numPixels(); i++)
    pixsoil.setPixelColor(i, pixsoil.Color(colorArray[color][0], colorArray[color][1], colorArray[color][2]));
  pixsoil.show();
}
void soilall(uint32_t c)
{
  for (uint8_t i = 0; i < pixsoil.numPixels(); i++)
    pixsoil.setPixelColor(i, c);
  pixsoil.show();
}

void sunshow(uint8_t color)
{
  for (uint8_t i = 0; i < pixsun.numPixels(); i++)
    pixsun.setPixelColor(i, pixsun.Color(colorArray[color][0], colorArray[color][1], colorArray[color][2]));
  pixsun.show();
}
void sunall(uint32_t c)
{
  for (uint8_t i = 0; i < pixsun.numPixels(); i++)
    pixsun.setPixelColor(i, c);
  pixsun.show();
}

void weathershow(uint8_t color)
{
  for (uint8_t i = 0; i < pixweather.numPixels(); i++)
    pixweather.setPixelColor(i, pixweather.Color(colorArray[color][0], colorArray[color][1], colorArray[color][2]));
  pixweather.show();
}

void weatherall(uint32_t c)
{
  for (uint8_t i = 0; i < pixweather.numPixels(); i++)
    pixweather.setPixelColor(i, c);
  pixweather.show();
}

//------------Breath Effect-------------//
void ledBreath(uint8_t color, uint8_t wait) {
  if (millis() - breathTimer > wait)
  {
    if (lednum < 5 || lednum > 250)
      num = -num;
    lednum += num;
    soilall(pixsoil.Color(map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][0]), map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][1]), map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][2])));
    sunall(pixsun.Color(map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][0]), map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][1]), map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][2])));
    weatherall(pixweather.Color(map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][0]), map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][1]), map(lednum, COLOR_MIN, COLOR_MAX, 0, colorArray[color][2])));
    breathTimer = millis();
  }
}

//------------Blink Effect-------------//
void ledBlink( uint8_t color, int16_t wait)
{
  if (millis() - blinkTimer > wait)
  {
    if ((millis() / wait) % 2)
    {
      soilshow(color);
      sunshow(color);
      weathershow(color);
    }
    else
    {
      soilshow(COLOR_NONE);
      sunshow(COLOR_NONE);
      weathershow(COLOR_NONE);
    }
    blinkTimer = millis();
  }
}

void ledinit()
{
  pixsoil.begin();
  pixsun.begin();
  pixweather.begin();
  pixsoil.setBrightness(BRIGHT_MAX);
  pixsun.setBrightness(BRIGHT_MAX);
  pixweather.setBrightness(BRIGHT_MAX);

  soilshow(COLOR_NONE);
  sunshow(COLOR_NONE);
  weathershow(COLOR_NONE);
}

void modeled(uint8_t _mode, uint8_t color, uint8_t wait)
{
  switch (_mode)
  {
    case MODESOIL:
      soilshow(color);
      delay(wait);
      soilshow(COLOR_NONE);
      break;
    case MODELIGHT:
      soilshow(color);
      sunshow(color);
      weathershow(color);
      delay(wait);
      soilshow(COLOR_NONE);
      sunshow(COLOR_NONE);
      weathershow(COLOR_NONE);
      break;
    case MODESUN:
      sunshow(color);
      delay(wait);
      sunshow(COLOR_NONE);
      break;
    case MODEWEATHER:
      weathershow(COLOR_GREEN);
      delay(wait);
      weathershow(COLOR_NONE);
      break;
    default:
      soilshow(COLOR_NONE);
      sunshow(COLOR_NONE);
      weathershow(COLOR_NONE);
  }
}

void offled(uint8_t _mode)
{
  switch (_mode)
  {
    case MODESOIL:
      soilshow(COLOR_NONE);
      break;
    case MODELIGHT:
      soilshow(COLOR_NONE);
      sunshow(COLOR_NONE);
      weathershow(COLOR_NONE);
      break;
    case MODESUN:
      sunshow(COLOR_NONE);
      break;
    case MODEWEATHER:
      weathershow(COLOR_NONE);
      break;
    default:
      soilshow(COLOR_NONE);
      sunshow(COLOR_NONE);
      weathershow(COLOR_NONE);
  }
}

void lighthouse(uint8_t _mode, uint8_t color)
{
  switch (_mode)
  {
    case LEDMODEBREATH:
      ledBreath(color, 60);
      break;
    case LEDMODEBLINK:
      ledBlink(color, 500);
      break;
    default:
      break;
  }
}

