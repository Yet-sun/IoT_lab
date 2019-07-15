#include <IRremote.h>// 使用IRRemote函数库
const int irReceiverPin = 7;// 红外接收器的 DO 引脚接在 PIN7 接口 定义irReceiverPin变量为PIN7接口
const int ledPin = 13; //RGB灯接在PIN13接口
IRrecv irrecv(irReceiverPin);// 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;// 定义results变量为红外结果存放位置

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();// 启动红外解码
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
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
