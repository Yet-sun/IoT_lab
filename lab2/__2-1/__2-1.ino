int button=4; //设置第4脚为按钮输入引脚
int LED=13; //设置第13脚为LED输出引脚，内部连上板上的LED灯。
void setup()
{ pinMode(button,INPUT); //设置为输入
  pinMode(LED,OUTPUT);  //设置为输出
}
void loop()
{ if(digitalRead(button)==LOW) //如果读取低电平
        digitalWrite(LED,HIGH);  //13脚输出高电平
   else
        digitalWrite(LED,LOW); //否则输出低电平
}
