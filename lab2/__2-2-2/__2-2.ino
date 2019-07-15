int sw = 8;//定义开关输入引脚
void setup()
{  pinMode(sw, INPUT);
  //定义为输出
  for (int i = 2; i < 6; i++) //依次循环四盏灯
  {    pinMode(i, OUTPUT);  }}
void loop()
{  int state = digitalRead(sw);
  for (int i = 2; i < 6; i++) //依次循环四盏灯
  {    if (state == 0)    {digitalWrite(i, HIGH); //点亮LED
      delay(1000); digitalWrite(i, LOW); //熄灭LED      delay(1000);  //持续1秒
    }
  }
}
