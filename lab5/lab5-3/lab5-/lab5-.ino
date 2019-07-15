#include<OneWire.h>
#include<DallasTemperature.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define ONE_WIRE_BUS 4//温度传感器接PIN4接口
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin();
  lcd.init();
  lcd.backlight();
}

void loop(void) {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures();//发送命令获取温度
  lcd.setCursor(0,0);
  lcd.print("TemC:");
  lcd.print(sensors.getTempCByIndex(0));

  Serial.print(sensors.getTempCByIndex(0));//打印温度
  Serial.println("C");
  delay(1000);
  lcd.print(char(223));//在LCD屏幕上打印°C
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("TemF:");
  lcd.print(1.8*sensors.getTempCByIndex(0) + 32.0);//计算华氏温度
  lcd.print(char(223));
  lcd.print(" F");
}
