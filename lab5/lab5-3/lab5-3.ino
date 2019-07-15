//#include<OneWire.h>
//#include<DallasTemperature.h>
#include<DHT.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht;
const int DHT11_PIN = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  D:int chk = DHT.read11(DHT11_PIN);
  switch(chk){
    case DHTLIB_OK:
      break;
    case DHTLIB_ERROR_CHECKSUM:
      break;
    case DHTLIB_ERROR_TIMEOUT:
      goto D;
      break;
    default:
      break;
  }
  lcd.setCursor(0,0);
  lcd.print("Tem:);
  lcd.print(dht.temperature,1);
  lcd.print(char(223));
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Hum");
  lcd.print(dht.humidity,1);
  lcd.print(" %");
  delay(200);
}
