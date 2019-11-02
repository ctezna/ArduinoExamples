// Define Trig and Echo pin:
#define triggerPin 2
#define echoPin 3

// Define variables:
long duracion;
int distancia;

void setup() {
  // Define inputs and outputs:
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
}


void loop() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(triggerPin, 0);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(triggerPin, 1);
  delayMicroseconds(10);
  digitalWrite(triggerPin, 0);
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duracion = pulseIn(echoPin, 1);
  // Calculate the distance:
  distancia= duracion*0.034/2;
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  if (distancia < 30){
    Serial.print("Distancia = ");
    Serial.print(distancia);
    Serial.println(" cm");
  }
  delay(50);
}
