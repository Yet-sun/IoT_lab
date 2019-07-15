#include<OneWire.h>
#include<DallasTemperature.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <IRremote.h>// 使用IRRemote函数库
#define ONE_WIRE_BUS 4//温度传感器接PIN4接口
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int irReceiverPin = 5;// 红外接收器的 DO 引脚接在 PIN5 接口 定义irReceiverPin变量为PIN5接口
const int motorIn1 = 9;
const int motorIn2 = 10;
const int buttonPin = 7;
const int avoidPin = 3;
int stat = 0;

int buttonState;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;//抖动

#define rank1 150
#define rank2 250
#define rank3 400

IRrecv irrecv(irReceiverPin);// 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;// 定义results变量为红外结果存放位置

void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();// 启动红外解码

  pinMode(buttonPin, INPUT);
  pinMode(avoidPin, INPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

  sensors.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) { // 解码成功，把数据放入results变量中
    Serial.print("irCode:");
    Serial.print(results.value, HEX); // 显示红外编码
    Serial.print(",bits:");
    Serial.println(results.bits);// 显示红外编码位数
    irrecv.resume();// 继续等待接收下一组信号
  }
  delay(600);//延时600毫秒，做一个简单的消抖

  if (results.value == 0xFFA25D) {
    sensors.requestTemperatures();//发送命令获取温度
    lcd.setCursor(0, 0);
    lcd.print("TemC:");
    lcd.print(sensors.getTempCByIndex(0));
    boolean avoidVal = digitalRead(avoidPin);
    Serial.print(sensors.getTempCByIndex(0));//打印温度
    Serial.println("C");
    lcd.print(char(223));//在LCD屏幕上打印°C
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("TemF:");
    lcd.print(1.8 * sensors.getTempCByIndex(0) + 32.0); //计算华氏温度
    lcd.print(char(223));
    lcd.print(" F");
    delay(500);

    if (sensors.getTempCByIndex(0) >= 35) {
      clockwise(rank3);
    } else if (sensors.getTempCByIndex(0) >= 30) {
      clockwise(rank2);
    } else if (sensors.getTempCByIndex(0) >= 25) {
      clockwise(rank1);
    } else {
      Serial.print("value:");
      Serial.println(results.value);
      int reading = digitalRead(buttonPin);
      Serial.print("button:");
      Serial.println(reading);
      fengShan(reading);
      if (avoidVal == LOW) {
        clockwise(rank1);
      }
      //      else {
      //        clockwise(0);//关闭风扇
      //      }
    }
  } else {
    clockwise(0);
  }
}

void fengShan(int reading) {
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  Serial.print("buttonState:");
  Serial.println(buttonState);
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        stat = stat + 1;
        if (stat >= 4) {
          stat = 0;
        }
      }
      else
        clockwise(0);
    }
  }
  switch (stat) {
    case 1:
      clockwise(rank1);
      break;
    case 2:
      clockwise(rank2);
      break;
    case 3:
      clockwise(rank3);
      break;
    default:
      clockwise(0);
  }
  lastButtonState = reading;
}

void clockwise(int Speed) {
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, Speed);
}
