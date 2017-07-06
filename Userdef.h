#define DEBUG  0

#define JOYSTICKPIN A6 //摇杆引脚
#define BACKPIN     10 //返回引脚
#define BUZZERPIN   8 //蜂鸣器引脚

#define SOILLED     A0 //土壤湿度灯引脚
#define SOILPIN     A1 //土壤湿度引脚

#define SUNLED      A2 //太阳能灯引脚
#define SUNPIN      A3 //太阳能光敏引脚

#define WEATHERLED  12  //气象站灯引脚

#define MODEHOME    1 //主基地 留言   7
#define MODELIGHT   2 //灯效         BREATH:8,9,10,11  BLINK:12,13,14,15
#define MODEWEATHER 3 //气象站       NO:16 alarmMIN:17 alarmMAX:18
#define MODESOIL    4 //绿植         NO:19 alarm:20
#define MODESUN     5 //太阳能       NO:21  alarm:22
#define MODESOUND   6 //声音         ON:23  OFF:24
#define MODEMATRIX  7 //主基地 画板

#define BRIGHT_MAX     100  //彩灯亮度
#define LIGHT_TRIGGER  300 //太阳能光线触发值

#define TEMMIN 10
#define TEMMAX 30

#define SOILMAX 55

#define LEDROLLTIME     200
#define WEATHERTIME     3*1000
