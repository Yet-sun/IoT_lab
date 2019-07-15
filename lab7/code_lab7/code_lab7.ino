#include <SimpleDHT.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10); // RX, TX
int c = 0;
int h = 0;
int pinDHT11 = 2;
SimpleDHT11 dht11;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);
  mySerial.println("AT+CIPSTART=\"TCP\",\"192.168.43.59\",8090"); //连接tcp
  delay(1000);
  mySerial.println("AT+CIPMODE=1"); //设为透传模式
  delay(500);
  mySerial.println("AT+CIPSEND"); //开始传输
  delay(500);
}

void loop() { // run over and over
//  if (mySerial.available()) {
//    Serial.write(mySerial.read());
//  }
//  if (Serial.available()) {
//    mySerial.write(Serial.read());
//  }

    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
      return;
    } //读取dht11的温度。
      String str="";
    str.concat((int)temperature);
  str.concat("x");
  str.concat((int)humidity);//构造字符串，用”x”分割温湿度
   mySerial.print(str); //发送温度到tcp服务器。
    // DHT11 sampling rate is 1HZ.
    delay(1500);
}

