int sw = 4;//定义开关输入引脚

void setup()
{
  pinMode(sw, INPUT);
  //定义为输出
  for (int i = 12; i < 14; i++) //依次循环四盏灯
  {
    pinMode(i, OUTPUT);
  }

}


void loop()
{
  int state = digitalRead(sw);
  
  if (state == 0)
  {
    int sensorRead = analogRead(A0); // 获取A0端口的模拟量值
    Serial.println(A0);
    int ledLevel = map(sensorRead, 0, 1023, 12, 14);
    for (int i = 12 ; i < 14; i++) //依次循环四盏灯
    {
      if (state == 0)    {
        digitalWrite(i, ledLevel); //点亮LED
        delay(1000);
        digitalWrite(i, LOW); //熄灭LED      delay(1000);  //持续1秒
      }
    }
  }

}
