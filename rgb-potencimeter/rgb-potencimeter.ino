
// Pins of the RGB LED.
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

// Analog input from the potentiometer
const int potPin = A0;

// Values for each pin of the RGB LED.
int currentColorValueRed;
int currentColorValueGreen;
int currentColorValueBlue;
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}
 
void loop()
{
  // Reading the value of the pot pin (it's always 0 - 1024) 
  // and converting it to a RGB range (0 - 255).
  int potPinValue = map(analogRead(potPin), 0, 1024, 0, 255);
  
  // Explanation of the code can be found on this link or on our blog:
  // https://electronics.stackexchange.com/questions/240185/controlling-color-and-brightness-of-rgb-led-strip-using-one-potentiometer
  // Note: 1/6th of 255 is 42.5
  if (potPinValue <= 42.5) {
    currentColorValueRed = 255;
    currentColorValueGreen = potPinValue * 6;
    currentColorValueBlue = 0;
   }
   
   if ((potPinValue > 42.5) && (potPinValue <= 85)) {
    currentColorValueRed = 255 - (potPinValue - 43) * 6;
    currentColorValueGreen = 255;
    currentColorValueBlue = 0;
   }
   
   if ((potPinValue > 85) && (potPinValue <= 127.5)) {
    currentColorValueRed = 0;
    currentColorValueGreen = 255;
    currentColorValueBlue = (potPinValue - 85) * 6;
   }
   
  if ((potPinValue > 127.5) && (potPinValue <= 170)) {
    currentColorValueRed = 0;
    currentColorValueGreen = 255 - (potPinValue - 127.5) * 6;
    currentColorValueBlue = 255;
  }
   
  if ((potPinValue > 170) && (potPinValue <= 212.5)) {
    currentColorValueRed = (potPinValue - 170) * 6;
    currentColorValueGreen = 0;
    currentColorValueBlue = 255;
  }
  
  if ((potPinValue > 212.5) && (potPinValue <= 255)) {
    currentColorValueRed = 255;
    currentColorValueGreen = 0;
    currentColorValueBlue = 255 - (potPinValue - 212.5) * 6;
  }
  analogWrite(redPin, currentColorValueRed);
  analogWrite(bluePin, currentColorValueBlue);
  analogWrite(greenPin, currentColorValueGreen);



}
