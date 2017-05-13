/*
  {"ID":"project"}
  {"point":"111"}
  {"Back":"1"}
  {"OK":"1"}
  {"key":"3"}
  {"msg":"mCookie Microduino mPuzzle mPie"}
*/

String inputCMD = "";
String inputValue = "";
String outputValue = "";
char inByte;

int readValue = 0, readdata = 0;
boolean jsonready, jsonname;
long timer;

char mId[10];
uint16_t mMatrix;
int8_t mBack, mKey, mOK;
int8_t mBack_C, mKey_C, mOK_C;

uint8_t mx, my, mval;

#define timeout 300

uint8_t mode = 1, mode_c = 1;
boolean intoitem, intoitem_c;
boolean snackone;
boolean play_game;

String mname[6] = {"ID", "point", "Back", "OK", "key", "msg"};

String ID = "{\"ID\":\"591411ebd4e8860001bc437b\"}";

String myMsg = "Hello MarsBase!";
String myMsgC = "";

int16_t msglength = myMsg.length();

void IDupload()
{
  Serial.print(ID.substring(0, 17));
  delay(100);
  Serial.println(ID.substring(17, 33));
  delay(100);
}

void uploaddata(String _st, int _data)
{
  String send_data;
  int number;
  send_data = "{\"";
  send_data += _st;
  send_data += "\":\"";
  send_data += _data;
  send_data += "\"\}";
  number = send_data.length() / 17;

  if (number == 0)
  {
    Serial.println(send_data);
    delay(30);
  }
  else
  {
    while (number >= 0)
    {
      Serial.print(send_data.substring(0, 17));
      send_data = send_data.substring(17, send_data.length());
      delay(30);
      number--;
    }
    Serial.print("\n");
  }
}

void uploaddata(String _st, String _data)
{
  String send_data;
  int number;
  send_data = "{\"";
  send_data += _st;
  send_data += "\":\"";
  send_data += _data;
  send_data += "\"\}";
  number = send_data.length() / 17;

  if (number == 0)
  {
    Serial.println(send_data);
    delay(30);
  }
  else
  {
    while (number >= 0)
    {
      Serial.print(send_data.substring(0, 17));
      send_data = send_data.substring(17, send_data.length());
      delay(30);
      number--;
    }
    Serial.print("\n");
  }
}

void solutiondata(String _data)
{
  if (_data == mname[0])
  {
    sscanf(inputCMD.c_str(), "ID:%s", &mId);
    if (String(mId) == "project")
    {
      IDupload();
      uploaddata("mode", mode);
    }
  }
  else if (_data == mname[1])
  {
    sscanf(inputCMD.c_str(), "point:%d", &mMatrix);
    if (mMatrix == -1)
    {
      intoitem = false;
      mode = MODEHOME;
    }
    else
    {
      intoitem = true;
      mode = MODEMATRIX;
    }
  }
  else if (_data == mname[2])
    sscanf(inputCMD.c_str(), "Back:%d", &mBack);
  else if (_data == mname[3])
    sscanf(inputCMD.c_str(), "OK:%d", &mOK);
  else if (_data == mname[4])
    sscanf(inputCMD.c_str(), "key:%d", &mKey);
  else if (_data == mname[5])
  {
    intoitem = true;
    mode = MODEHOME;
    myMsg = inputCMD.substring(4, inputCMD.length());
    msglength = myMsg.length();
  }

  //#if DEBUG
  //  Serial.print("   mId:");
  //  Serial.println(mId);
  //  Serial.print("   mMatrix:");
  //  Serial.println(mMatrix);
  //  Serial.print("   mBack:");
  //  Serial.println(mBack);
  //  Serial.print("   mKey:");
  //  Serial.println(mKey);
  //#endif

}

void readserail()
{
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == '{')
      readValue++;
    else if (inByte == '}')
      readValue--;
    else if (readValue > 0 && inByte != '"')
    {
      jsonready = true;
      inputCMD += inByte;
      if (inByte == ':')
        jsonname = true;
      if (!jsonname)
        inputValue += inByte;
    }
    if (jsonready && readValue == 0)
    {
      //Serial.println("--------Json ok---------");
      //Serial.println(inputCMD);
      //Serial.println("------------------------");
      solutiondata(inputValue);
      //Serial.println("------------------------");
      inputCMD = "";
      inputValue = "";
      jsonready = false;
      jsonname = false;
    }
    timer = millis();
  }
  if (millis() - timer > timeout && readValue > 0)
  {
    readValue = 0;
    inputCMD = "";
    inputValue = "";
    jsonready = false;
    jsonname = false;
    //Serial.println("--------Json fail---------");
  }
}
