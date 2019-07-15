int sw = 4;//定义开关输入引脚
int state = 1; //控制开关状态
int val = 0;
int oldval = 0;
const int analogInPin = A0; //设置模拟信号的引脚
int outputValue = 0; //记录map()之后值的变量
int sensorValue = 0; //接受模拟信号
byte ledPin[] = {11, 10}; //设置2个灯的引脚

void setup()
{
  pinMode(sw, INPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(ledPin[i], OUTPUT);//设置11,10号为输出引脚
  }
  Serial.begin(9600);
}


void loop()
{
  val = digitalRead(sw);
  for (int i = 0; i < 2; i++) { //跑马灯循环
    if (val == LOW && oldval == HIGH) {
      digitalWrite(ledPin[i], LOW);
      oldval = val;
      state = 1 - state;
    }
    sensorValue = analogRead(A0);//设置Ao号为模拟输出引脚
    outputValue = map(sensorValue, 1023, 0, 0, 255); //把一个数从一个范围变换到另一个范围
    if (state == 1) { //判断开关状态
      analogWrite(ledPin[i], outputValue);
      delay(1000);
      digitalWrite(ledPin[i], LOW);
    }
    else { //跳出循环
      break;
    }
  }
}
