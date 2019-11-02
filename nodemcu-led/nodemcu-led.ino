int roja = 14;
int amarilla=12;
int verde=13;

void setup() {
  // initialize digital pin 13 as an output.
  // roja 14
  // amarilla 12
  // verde 13
  pinMode(roja, OUTPUT);
  pinMode(amarilla,OUTPUT);
  pinMode(verde,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(roja, 1); 
  delay(300);
  digitalWrite(amarilla,1);
  delay(5000);
  digitalWrite(roja,0);
  digitalWrite(amarilla,0);
  digitalWrite(verde,1);
  delay(5000);
  digitalWrite(verde,0);
 
}
