#include "DHT.h"
#include <LiquidCrystal_I2C.h> // Libreria LCD_I2C
#include <Adafruit_NeoPixel.h>

LiquidCrystal_I2C lcd(0x3f,16,2);

#define DHTPIN 13     // Pin donde está conectado el sensor
#define TIERRA A0
float valorSensor=0;

#define DHTTYPE DHT22   // Sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

#define BRILLO   A1

#define PIXEL_PIN    11  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 8  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

#define triggerPin 2
#define echoPin 3

// Define variables:
long duracion;
int distancia;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int rojo = 0;
int verde = 0;
int azul = 0;

void setup() {
  Serial.begin(9600);
  //Serial.println("Iniciando...");
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(12, OUTPUT);
  digitalWrite(12,1);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,1);
  digitalWrite(S1,0);
  delay(2000);
  
}
void loop() {
  digitalWrite(12,1);
  //delay(1900);
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
  Serial.print(distancia);
  Serial.print("\t");

  
  int valorBrillo = map(analogRead(BRILLO), 0, 1024, 0, 255);
  ledSwitch(valorBrillo, lcd, distancia);
  float h = dht.readHumidity(); //Leemos la Humedad
  float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
  Serial.print(h);
  Serial.print("\t");
  Serial.print(t);
  Serial.print("\t");
  for(int i = 0;i <= 100; i++){
    valorSensor = valorSensor + analogRead(TIERRA);
    delay(1);
  }
  valorSensor = valorSensor/1023.00;
  Serial.print(valorSensor);
  Serial.println();
  lcd.setCursor(0,0);
  lcd.print("T:"); 
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor (0,1);
  lcd.print("H:"); 
  lcd.print(h);
  lcd.print("%");
  valorBrillo = map(analogRead(BRILLO), 0, 1024, 0, 255);
  //lcd.setCursor(9,0);
  //lcd.print(valorBrillo);
  lcd.setCursor(9,1);
  lcd.print(valorSensor);
  lcd.print("%");
  ledSwitch(valorBrillo, lcd, distancia);
}

void ledSwitch(int valorBrillo, LiquidCrystal_I2C lcd, int distancia){
  lcd.setCursor(9,0);
  lcd.print(distancia);
  if (distancia < 4){
      rojo = 0;
      verde = 0;
      azul = 0;
      colorWipe(strip.Color(0,   0,   0), 50);
  } else if (distancia <= 6 && distancia >= 4){
      digitalWrite(S2,0);
      digitalWrite(S3,0);
      // Reading the output frequency
      rojo = pulseIn(sensorOut, 0);
      delay(10);

      digitalWrite(S2,1);
      digitalWrite(S3,1);
      // Reading the output frequency
      verde = pulseIn(sensorOut, 0);
      delay(10);

      digitalWrite(S2,0);
      digitalWrite(S3,1);
      // Reading the output frequency
      azul = pulseIn(sensorOut, 0);
  }else if (rojo > 5 || verde > 5 || azul > 5) {
    colorWipe(strip.Color(rojo,   verde,   azul), 50);
  } else {
  if (valorBrillo <= 42.5) {
    colorWipe(strip.Color(valorBrillo,   valorBrillo,   valorBrillo), 50);
   }
   
   if ((valorBrillo > 42.5) && (valorBrillo <= 85)) {
    theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
    theaterChase(strip.Color(  0,   0, 127), 50);
    theaterChase(strip.Color(  0,   127, 0), 50);
    theaterChase(strip.Color(valorBrillo,   255-valorBrillo,   175+(valorBrillo/2)), 50);
   }
   
   if ((valorBrillo > 85) && (valorBrillo <= 127.5)) {
    rainbow(10);
   }
   
  if ((valorBrillo > 127.5) && (valorBrillo <= 170)) {
    theaterChaseRainbow(50);
  }
   
  if ((valorBrillo > 170) && (valorBrillo <= 212.5)) {
    if (distancia <= 6 && distancia >= 4){
      digitalWrite(S2,0);
      digitalWrite(S3,0);
      // Reading the output frequency
      rojo = pulseIn(sensorOut, 0);
      delay(10);

      digitalWrite(S2,1);
      digitalWrite(S3,1);
      // Reading the output frequency
      verde = pulseIn(sensorOut, 0);
      delay(10);

      digitalWrite(S2,0);
      digitalWrite(S3,1);
      // Reading the output frequency
      azul = pulseIn(sensorOut, 0);
    }
  }
  
  if ((valorBrillo > 212.5) && (valorBrillo <= 255)) {
    colorWipe(strip.Color(valorBrillo,   0,   0), 50); // Red
    colorWipe(strip.Color(  0, valorBrillo,   0), 50); // Green
    colorWipe(strip.Color(  0,   0, valorBrillo), 50);
  }
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
