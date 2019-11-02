#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int rojo = 0;
int verde = 0;
int azul = 0;



// Pins of the RGB LED.
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,1);
  digitalWrite(S1,0);



  Serial.begin(9600);
}
 
void loop()
{
  digitalWrite(S2,0);
  digitalWrite(S3,0);
  // Reading the output frequency
  rojo = pulseIn(sensorOut, 0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(rojo);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  digitalWrite(S2,1);
  digitalWrite(S3,1);
  // Reading the output frequency
  verde = pulseIn(sensorOut, 0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(verde);//printing RED color frequency
  Serial.print("  ");
  delay(100);


  digitalWrite(S2,0);
  digitalWrite(S3,1);
  // Reading the output frequency
  azul = pulseIn(sensorOut, 0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(azul);//printing RED color frequency
  Serial.println("  ");
  delay(100);

  
  analogWrite(redPin, rojo);
  analogWrite(bluePin, azul);
  analogWrite(greenPin, verde);



}
