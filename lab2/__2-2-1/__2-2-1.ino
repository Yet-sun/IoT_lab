void setup() {

// initialize digital pin LED_BUILTIN as an output.

pinMode(13, OUTPUT);

pinMode(12, OUTPUT);

pinMode(11, OUTPUT);

pinMode(10, OUTPUT);

}


// the loop function runs over and over again forever

void loop() {

for(int i=13;i>=10;i-- ){
digitalWrite(i, LOW);

digitalWrite(i, HIGH);

delay(1000);

digitalWrite(i, LOW);

}

}
