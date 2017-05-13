#include "Userdef.h"
#include "BLEJson.h"
#include "Joystick.h"
#include "Weather.h"
#include "Colorled.h"
#include "Servo.h"
#include "Matrix.h"
#include "Itemrun.h"

void setup() {
  Serial.begin(57600);

  //delay(5000);
  Wire.begin();

  ledinit();

  initmatrix();

  getweather();
  Soilmoisture();

  //Serial.println("------Start-------");
}

void loop() {

#if DEBUG
  Serial.print("Joystick:");
  Serial.println(analogRead(JOYSTICKPIN));
#endif

  readserail();

  key = INjoystick();

  if (!intoitem)
  {
    menukey(key);
    menumatrix(mode);
    offled(mode);
    noTone(BUZZERPIN);
  }
  else
  {
    itemmatrix(mode);
    switch (mode)
    {
      case MODEHOME:
        runmatrix();
        break;
      case MODESOIL:
        runsoil();
        break;
      case MODELIGHT:
        runlight();
        break;
      case MODESUN:
        runsun();
        break;
      case MODEWEATHER:
        runweather();
        break;
      case MODESOUND:
        runsound();
        break;
      case MODEMATRIX:
        runmatrix();
        break;
      default:
        break;
    }
    if (key == JOYBACK)
    {
      if (mode == MODESUN)
        uploaddata("sun", "false");
      x = display.getWidth() * 8; //恢复气象站起始坐标
      y = display.getWidth() * 8; //恢复土壤湿度起始坐标
      z = display.getWidth() * 8; //恢复留言起始坐标
      temsta = 0;  //恢复温度发送
      temstaC = 0; //恢复温度发送
      soilsta = 0;
      soilstaC = 0;
      sunsend = 0;
      sunsendC = 0;
      intoitem = false;           //退出项目
    }
  }

  if (mode_c != mode || intoitem_c != intoitem || soundsta_c != soundsta )
  {
    display.clearDisplay();
    if (soundsta)
      tone(BUZZERPIN, tone_list[mode] , 300);
    mode_c = mode;
    intoitem_c = intoitem;
    soundsta_c = soundsta;
  }

  if (key != keyC)
  {
    if (key && intoitem)
    {
      switch (mode)
      {
        case MODEHOME:
          uploaddata("mode", 7);//into home
          break;
        case MODELIGHT:
          uploaddata("mode", 7 + lighthousecolor + 4 * (lighthousemode - 1)); //LEDMODEBREATH:8,9,10,11 LEDMODEBLINK:12,13,14,15
          break;
        case MODESOUND:
          if (soundsta)
            uploaddata("mode", 23);
          else
            uploaddata("mode", 24);
          break;
        default:
          break;
      }
    }
    else if (key && !intoitem)
    {
      uploaddata("mode", mode);
      modeled(mode, COLOR_GREEN, 200);
    }
    keyC = key;
  }

  delay(20);
}
