void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13, HIGH); //将管脚设置为高电平, 则LED灯亮 
  delay(1000); //等待1000毫秒
  digitalWrite(13, LOW); //将管脚设置为低电平, 则LED灯灭 
  delay(2000); //等待2000毫秒

}
