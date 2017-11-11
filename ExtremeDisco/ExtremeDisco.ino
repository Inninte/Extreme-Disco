const int sensorPin = A3;
int sensorValue = 0;

int mx = 0;
int mn = 1023;
short maxC = 0;
short minC = 0;
float range = 1;
float logSensor = 1;
float lnSensor = 1;

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;

const int RGB_1 = 1;
const int RGB_2 = 2;
const int RGB_3 = 3;
const int RGB_4 = 4;
const int RGB_5 = 5;

int strobeDelay = 50;

void setup() {
  Serial.begin (9600);
  // Start off with the LED off.
  setColourRgb(0,0,0);
  pinMode(RGB_1, OUTPUT);
  pinMode(RGB_2, OUTPUT);
  pinMode(RGB_3, OUTPUT);
  pinMode(RGB_4, OUTPUT);
  pinMode(RGB_5, OUTPUT);
  digitalWrite(RGB_1, LOW);
  digitalWrite(RGB_2, HIGH);
  digitalWrite(RGB_3, HIGH);
  digitalWrite(RGB_4, HIGH);
  digitalWrite(RGB_5, HIGH);
}

void loop() {
  
  unsigned int rgbColour[3];

  // Start off with red.
  rgbColour[0] = 0;
  rgbColour[1] = 0;
  rgbColour[2] = 255;  

  setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
  
  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;
  
    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;

      sensorValue = analogRead(sensorPin);
      Serial.println(sensorValue, DEC); 

      if(sensorValue > mn && sensorValue < mn + range) {
        switchLED(5);
      }
      else if(sensorValue > mn + .75*range && sensorValue < mn + 2*range) {
        switchLED(4);
      }
      else if(sensorValue > mn + (1.75*range) && sensorValue < mx) {
        switchLED(3);
      }
      else if(sensorValue > mn + (2.75*range) && sensorValue < mx + range) {
        switchLED(2);
      }
      else {
        switchLED(1);
      }

      if(sensorValue > mx){
        mx = sensorValue;
        maxC = 0;
      } else {
        maxC += 1;
        if (maxC > 20){
          mx = sensorValue;
          maxC = 0;
        }
      }
      
      if(sensorValue < mn){
        mn = sensorValue;
      } else {
        minC += 1;
        if (minC > 20){
          mn = sensorValue;
          minC = 0;
        }
      }
      
      range = (mx-mn)/3;
      
      
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(strobeDelay);
      }    
  }
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

void switchLED(int numLED){
  for(int i = 1; i<=numLED; i++){
    digitalWrite(i, LOW);
  }
  for(int i = numLED+1 ; i <= 5; i++){
    digitalWrite(i, HIGH);
  }
}

