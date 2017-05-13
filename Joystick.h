
#include <Microduino_Key.h>

Key KeyA(JOYSTICKPIN, INPUT);
Key KeyB(JOYSTICKPIN, INPUT);
Key KeyC(JOYSTICKPIN, INPUT);
Key KeyD(JOYSTICKPIN, INPUT);
Key KeyE(JOYSTICKPIN, INPUT);
Key KeyF(JOYSTICKPIN, INPUT);

Key KeyG(BACKPIN, INPUT);

#define JOYUP 1
#define JOYDOWN 2
#define JOYLEFT 3
#define JOYRIGHT 4
#define JOYOK 5
#define JOYBACK 6

uint8_t INjoystick()
{
  if (KeyA.read(0, 10) == SHORT_PRESS || mOK == 1) //按下
  {
    mOK = 0;
    return JOYOK;
  }
  else if (KeyB.read(650, 800) == SHORT_PRESS || mKey == 1) //上
  {
    mKey = 0;
    return JOYUP;
  }
  else if (KeyC.read(260, 450) == SHORT_PRESS || mKey == 2) //下
  {
    mKey = 0;
    return JOYDOWN;
  }
  else if (KeyD.read(450, 650) == SHORT_PRESS || mKey == 3) //左
  {
    mKey = 0;
    return JOYLEFT;
  }
  else if (KeyE.read(800, 1000) == SHORT_PRESS || mKey == 4) //右
  {
    mKey = 0;
    return JOYRIGHT;
  }
  else if (KeyG.read() == SHORT_PRESS || mBack == 1)   //返回
  {
    noTone(BUZZERPIN);
    mBack = 0;
    return JOYBACK;
  }
  else
    return 0;
}

void menukey(uint8_t _key)
{
  switch (_key)
  {
    case JOYLEFT:
      mode--;
      if (mode < 1)
        mode = MODESOUND;
      break;
    case JOYRIGHT:
      mode++;
      if (mode > MODESOUND)
        mode = 1;
      break;
    case JOYOK:
      intoitem = true;
      break;
    default:
      break;
  }
}

