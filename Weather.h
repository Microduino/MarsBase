#include <Wire.h>
#include <lm75.h>

TempI2C_LM75 termo = TempI2C_LM75(0x48, TempI2C_LM75::nine_bits);

String weathers = "";
String soils = "";
float  tem, temf;
int soil;

int16_t soillength;
int16_t temlength;

void getweather()
{
  tem = termo.getTemp();
  temf = tem * 1.8 + 32;
  weathers = "Tem:";
  weathers += String(tem);
  weathers += "'C ";
  weathers += String(temf);
  weathers += "'F";
  temlength = weathers.length();
}

void Soilmoisture()
{
  soil = map(analogRead(SOILPIN), 0, 1023, 0, 100);
  soils = "Soil Hum:";
  soils += String(soil);
  soils += "%";
  soillength = soils.length();
}
