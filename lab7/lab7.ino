#include <stdlib.h>
#include <SoftwareSerial.h>
#include <dht.h>            
dht DHT;  
const int pin = 4;  // 将把 DHT11 的 data pin 連到 arduino Pin 4

#define SSID "captain"      //wifi名
#define PASS "12345678" //wifi密码
#define IP "183.230.40.39" // 连接服务器
String GET = "GET /update?key=4cROpRC4NVbzGbtNRbeUbGeXz2c="; //输入前面记下的API
SoftwareSerial monitor(10, 11); // 定义软串口RX, TX

//初始化-----------------------------------------
void setup()
{
    monitor.begin(9600);
    Serial.begin(9600);
    sendDebug("AT");        //指令测试
    delay(5000);
    if(Serial.find("OK"))   //接收指令正常则返回OK
    {
        monitor.println("RECEIVED: OK");
        Serial.print("ok");
        connectWiFi();
    }
}

//主循环-----------------------------------------
void loop()
{
    DHT.read11(pin);  // 读取 DHT11 传感器
    Serial.print(DHT.humidity,1);    //串口打印湿度
    Serial.print(",\t");  
    Serial.println(DHT.temperature,1);   //打印温度
    float tempH = DHT.humidity;
    float tempT = DHT.temperature;
    char buffer[10];
    String temph = dtostrf(tempH, 4, 1, buffer);    
    String tempt = dtostrf(tempT, 4, 1, buffer);    
    updateTemp(temph,tempt);
    delay(60000);
}


void updateTemp(String temph,String tempt)          
{               
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    sendDebug(cmd);                         //发送指令，链接服务器
    delay(2000);
    if(Serial.find("Error"))
    {
        monitor.print("RECEIVED: Error");
        return;
    }
    cmd = GET + "&field1=" + temph + "&field2=" + tempt +"\r\n";        //记录T和H的值
    Serial.print("AT+CIPSEND=");
    Serial.println(cmd.length());
    if(Serial.find(">"))
    {
        monitor.print(">");
        monitor.print(cmd);
        Serial.print(cmd);
    }
    else
    {
        sendDebug("AT+CIPCLOSE");
    }
    if(Serial.find("OK"))
    {
        monitor.println("RECEIVED: OK");
    }
    else
    {
        monitor.println("RECEIVED: Error");
    }
}

void sendDebug(String cmd)
{
    monitor.print("SEND: ");
    monitor.println(cmd);
    Serial.println(cmd);
}

boolean connectWiFi()
{
    Serial.println("AT+CIPMUX=0");
    Serial.println("AT+CWMODE=1");
    delay(2000);
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    sendDebug(cmd);
    delay(5000);
    if(Serial.find("OK"))
    {
        monitor.println("RECEIVED: OK");
        return true;
    }else
    {
        monitor.println("RECEIVED: Error");
        return false;
    }
}
