#define led 10

void setup()

{

  pinMode(led, OUTPUT);

}

void loop()

{

  int val = analogRead(3);

  val = map(val, 0, 1023, 0, 255);

  digitalWrite(10, val);

}



//
//int val = 0;
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  val = analogRead(A0);
//  Serial.println(val);
//  delay(1000);
//}
