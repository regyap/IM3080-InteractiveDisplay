#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
int distance;
unsigned duration;

//LED pins
//first circle
#define LED_PIN13 
//second circle
#define LED_PIN8 
#define LED_PIN9 
#define LED_PIN12 
#define LED_PIN14 
#define LED_PIN17 
#define LED_PIN18 
//third circle
#define LED_PIN3
#define LED_PIN4 
#define LED_PIN5 
#define LED_PIN7 
#define LED_PIN10
#define LED_PIN11
#define LED_PIN15
#define LED_PIN16
#define LED_PIN19
#define LED_PIN21
#define LED_PIN22
#define LED_PIN23
//forth circle
#define LED_PIN1
#define LED_PIN2
#define LED_PIN6
#define LED_PIN20
#define LED_PIN24
#define LED_PIN25



#define LED_COUNT 20

//Ultrasonic sensor pins
#define trigPin1 
#define trigPin2 
#define trigPin3 
#define trigPin4 
#define trigPin5 
#define trigPin6 
#define echoPin1
#define echoPin2
#define echoPin3
#define echoPin4
#define echoPin5
#define echoPin6

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);

int brightnessLow = 150;
int brightnessHigh = 255;
int wait = 1000;

//for sensors
int maxDistance = 250;
int triggeredNo = 0;
int distance1, distance2, distance3, distance4, distance5, distance6;
long duration1, duration2, duration3, duration4, duration5, duration6;

//For multithreading
long lastTime = millis();

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(brightnessLow);

  Serial.begin(9600);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  pinMode(echoPin5, INPUT);
  pinMode(echoPin6, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(trigPin6, OUTPUT);
}

void dist() {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);  
  digitalWrite(trigPin2, LOW);  
  digitalWrite(trigPin3, LOW);  
  digitalWrite(trigPin4, LOW);
  digitalWrite(trigPin5, LOW);
  digitalWrite(trigPin6, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);  
  digitalWrite(trigPin2, HIGH);  
  digitalWrite(trigPin3, HIGH);  
  digitalWrite(trigPin4, HIGH);
  digitalWrite(trigPin5, HIGH);
  digitalWrite(trigPin6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);  
  digitalWrite(trigPin2, LOW);  
  digitalWrite(trigPin3, LOW);  
  digitalWrite(trigPin4, LOW);
  digitalWrite(trigPin5, LOW);
  digitalWrite(trigPin6, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  duration3 = pulseIn(echoPin3, HIGH);
  duration4 = pulseIn(echoPin4, HIGH);
  duration5 = pulseIn(echoPin5, HIGH);
  duration6 = pulseIn(echoPin6, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.34 / 2;
  distance2 = duration2 * 0.34 / 2;
  distance3 = duration3 * 0.34 / 2;
  distance4 = duration4 * 0.34 / 2;
  distance5 = duration5 * 0.34 / 2;
  distance6 = duration6 * 0.34 / 2;

  if (distance1 <= maxDistance) {
    triggeredNo += 1;
  }   if (distance2 <= maxDistance) {
    triggeredNo += 1;
  }   if (distance3 <= maxDistance) {
    triggeredNo += 1;
  }   if (distance4 <= maxDistance) {
    triggeredNo += 1;
  }   if (distance5 <= maxDistance) {
    triggeredNo += 1;
  }   if (distance6 <= maxDistance) {
    triggeredNo += 1;
  } 
}

void TurnOnBlue(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(0, 0, 127));
  strip.setBrightness(brightnessHigh);
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.setBrightness(brightnessLow);
    strip.show();
    ledTime -= wait;
  }
}

void TurnOnRed(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(127, 0, 0));
  strip.setBrightness(brightnessHigh);
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.setBrightness(brightnessLow);
    strip.show();
    ledTime -= wait;
  }
}

void TurnOnGreen(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(0, 127, 0));
  strip.setBrightness(brightnessHigh);
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.setBrightness(brightnessLow);
    strip.show();
    ledTime -= wait;
  }
}

void TurnOnYellow(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(64, 63, 0));
  strip.setBrightness(brightnessHigh);
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.setBrightness(brightnessLow);
    strip.show();
    ledTime -= wait;
  }
}

void TurnOnPurple(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(53, 0, 74));
  strip.setBrightness(brightnessHigh);
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.setBrightness(brightnessLow);
    strip.show();
    ledTime -= wait;
  }
}

void TurnOnOrange(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(101, 26, 0));
  strip.setBrightness(brightnessHigh);
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.setBrightness(brightnessLow);
    strip.show();
    ledTime -= wait;
  }
}

void TurnOffAll() {
  for (int i = 0; i <= 9; i++) {
    strip.setPin(i);
    strip.fill(strip.Color(0, 0, 0));
    strip.setBrightness(brightnessLow);
    strip.show();
  }
}


void CenterRipple(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOnRed(LED_PIN13, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOffAll();
    TurnOnYellow(LED_PIN8, elapsedTime);
    TurnOnYellow(LED_PIN9, elapsedTime);
    TurnOnYellow(LED_PIN12, elapsedTime);
    TurnOnYellow(LED_PIN14, elapsedTime);
    TurnOnYellow(LED_PIN17, elapsedTime);
    TurnOnYellow(LED_PIN18, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOffAll();
    TurnOnGreen(LED_PIN3, elapsedTime);
    TurnOnGreen(LED_PIN4, elapsedTime);
    TurnOnGreen(LED_PIN5, elapsedTime);
    TurnOnGreen(LED_PIN7, elapsedTime);
    TurnOnGreen(LED_PIN10, elapsedTime);
    TurnOnGreen(LED_PIN11, elapsedTime);
    TurnOnGreen(LED_PIN15, elapsedTime);
    TurnOnGreen(LED_PIN16, elapsedTime);
    TurnOnGreen(LED_PIN19, elapsedTime);
    TurnOnGreen(LED_PIN21, elapsedTime);
    TurnOnGreen(LED_PIN22, elapsedTime);
    TurnOnGreen(LED_PIN23, elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOffAll();
    TurnOnBlue(LED_PIN1, elapsedTime);
    TurnOnBlue(LED_PIN2, elapsedTime);
    TurnOnBlue(LED_PIN6, elapsedTime);
    TurnOnBlue(LED_PIN20, elapsedTime);
    TurnOnBlue(LED_PIN24, elapsedTime);
    TurnOnBlue(LED_PIN25, elapsedTime);
  };
  if (ledTime >= 4000) {
    TurnOffAll();
    ledTime -= 4000;
  }
}

void DirectionRipple1(int distance1, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance1 <= 60) {
    TurnOffAll();
    TurnOnRed(LED_PIN1, elapsedTime);
  };
  if (distance1 > 60 && distance1 <= 100) {
    TurnOffAll();
    TurnOnRed(LED_PIN2, elapsedTime);
    TurnOnRed(LED_PIN3, elapsedTime);
    TurnOnRed(LED_PIN4, elapsedTime);
    TurnOnRed(LED_PIN5, elapsedTime);
    TurnOnRed(LED_PIN6, elapsedTime);
  };
  if (distance1 > 100 && distance1 <= 130) {
    TurnOffAll();
    TurnOnRed(LED_PIN7, elapsedTime);
    TurnOnRed(LED_PIN8, elapsedTime);
    TurnOnRed(LED_PIN9, elapsedTime);
    TurnOnRed(LED_PIN10, elapsedTime);
  };
  if (distance1 > 130 && distance1 <= 160) {
    TurnOffAll();
    TurnOnRed(LED_PIN11, elapsedTime);
    TurnOnRed(LED_PIN12, elapsedTime);
    TurnOnRed(LED_PIN13, elapsedTime);
    TurnOnRed(LED_PIN14, elapsedTime);
    TurnOnRed(LED_PIN15, elapsedTime);
  };
  if (distance1 > 160 && distance1 <= 190) {
    TurnOffAll();
    TurnOnRed(LED_PIN16, elapsedTime);
    TurnOnRed(LED_PIN17, elapsedTime);
    TurnOnRed(LED_PIN18, elapsedTime);
    TurnOnRed(LED_PIN19, elapsedTime);
  };
  if (distance1 > 190 && distance1 <= 220) {
    TurnOffAll();
    TurnOnRed(LED_PIN20, elapsedTime);
    TurnOnRed(LED_PIN21, elapsedTime);
    TurnOnRed(LED_PIN22, elapsedTime);
    TurnOnRed(LED_PIN23, elapsedTime);
    TurnOnRed(LED_PIN24, elapsedTime);
  };
  if (distance1 > 220 && distance1 <= 250) {
    TurnOffAll();
    TurnOnRed(LED_PIN25, elapsedTime);
  };
}

void DirectionRipple2(int distance2, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (distance1 <= 60) {
    TurnOffAll();
    TurnOnOrange(LED_PIN2, elapsedTime);
  };
  if (distance2 > 60 && distance2 <= 100) {
    TurnOffAll();
    TurnOnOrange(LED_PIN1, elapsedTime);
    TurnOnOrange(LED_PIN3, elapsedTime);
    TurnOnOrange(LED_PIN7, elapsedTime);
    TurnOnOrange(LED_PIN11, elapsedTime);
  };
  if (distance2 > 100 && distance2 <= 130) {
    TurnOffAll();
    TurnOnOrange(LED_PIN4, elapsedTime);
    TurnOnOrange(LED_PIN8, elapsedTime);
    TurnOnOrange(LED_PIN12, elapsedTime);
    TurnOnOrange(LED_PIN16, elapsedTime);
    TurnOnOrange(LED_PIN20, elapsedTime);
  };
  if (distance2 > 130 && distance2 <= 160) {
    TurnOffAll();
    TurnOnOrange(LED_PIN5, elapsedTime);
    TurnOnOrange(LED_PIN9, elapsedTime);
    TurnOnOrange(LED_PIN13, elapsedTime);
    TurnOnOrange(LED_PIN17, elapsedTime);
    TurnOnOrange(LED_PIN21, elapsedTime);
  };
  if (distance2 > 160 && distance2 <= 190) {
    TurnOffAll();
    TurnOnOrange(LED_PIN6, elapsedTime);
    TurnOnOrange(LED_PIN10, elapsedTime);
    TurnOnOrange(LED_PIN14, elapsedTime);
    TurnOnOrange(LED_PIN18, elapsedTime);
    TurnOnOrange(LED_PIN22, elapsedTime);
  };
  if (distance2 > 190 && distance2 <= 220) {
    TurnOffAll();
    TurnOnOrange(LED_PIN15, elapsedTime);
    TurnOnOrange(LED_PIN19, elapsedTime);
    TurnOnOrange(LED_PIN23, elapsedTime);
    TurnOnOrange(LED_PIN25, elapsedTime);
  };
  if (distance2 > 220 && distance2 <= 250) {
    TurnOffAll();
    TurnOnOrange(LED_PIN24, elapsedTime);
  };
}

void DirectionRipple3(int distance3, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance3 <= 60) {
    TurnOffAll();
    TurnOnYellow(LED_PIN6, elapsedTime);
  };
  if (distance3 > 60 && distance3 <= 100) {
    TurnOffAll();
    TurnOnYellow(LED_PIN1, elapsedTime);
    TurnOnYellow(LED_PIN5, elapsedTime);
    TurnOnYellow(LED_PIN10, elapsedTime);
    TurnOnYellow(LED_PIN15, elapsedTime);
  };
  if (distance3 > 100 && distance3 <= 130) {
    TurnOffAll();
    TurnOnYellow(LED_PIN4, elapsedTime);
    TurnOnYellow(LED_PIN9, elapsedTime);
    TurnOnYellow(LED_PIN14, elapsedTime);
    TurnOnYellow(LED_PIN19, elapsedTime);
    TurnOnYellow(LED_PIN24, elapsedTime);
  };
  if (distance3 > 130 && distance3 <= 160) {
    TurnOffAll();
    TurnOnYellow(LED_PIN3, elapsedTime);
    TurnOnYellow(LED_PIN8, elapsedTime);
    TurnOnYellow(LED_PIN13, elapsedTime);
    TurnOnYellow(LED_PIN18, elapsedTime);
    TurnOnYellow(LED_PIN23, elapsedTime);
  };
  if (distance3 > 160 && distance3 <= 190) {
    TurnOffAll();
    TurnOnYellow(LED_PIN2, elapsedTime);
    TurnOnYellow(LED_PIN7, elapsedTime);
    TurnOnYellow(LED_PIN12, elapsedTime);
    TurnOnYellow(LED_PIN17, elapsedTime);
    TurnOnYellow(LED_PIN22, elapsedTime);
  };
  if (distance3 > 190 && distance3 <= 220) {
    TurnOffAll();
    TurnOnYellow(LED_PIN11, elapsedTime);
    TurnOnYellow(LED_PIN16, elapsedTime);
    TurnOnYellow(LED_PIN21, elapsedTime);
    TurnOnYellow(LED_PIN25, elapsedTime);
  };
  if (distance3 > 220 && distance3 <= 250) {
    TurnOffAll();
    TurnOnYellow(LED_PIN20, elapsedTime);
  };
}

void DirectionRipple4(int distance4, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance4 > 60) {
    TurnOffAll();
    TurnOnGreen(LED_PIN20, elapsedTime);
  };
  if (distance4> 60 && distance4 <= 100) {
    TurnOffAll();
    TurnOnGreen(LED_PIN11, elapsedTime);
    TurnOnGreen(LED_PIN16, elapsedTime);
    TurnOnGreen(LED_PIN21, elapsedTime);
    TurnOnGreen(LED_PIN25, elapsedTime);
  };
  if (distance4> 100 && distance4 <= 130) {
    TurnOffAll();
    TurnOnGreen(LED_PIN2, elapsedTime);
    TurnOnGreen(LED_PIN7, elapsedTime);
    TurnOnGreen(LED_PIN12, elapsedTime);
    TurnOnGreen(LED_PIN17, elapsedTime);
    TurnOnGreen(LED_PIN22, elapsedTime);
  };
  if (distance4> 130 && distance4 <= 160) {
    TurnOffAll();
    TurnOnGreen(LED_PIN3, elapsedTime);
    TurnOnGreen(LED_PIN8, elapsedTime);
    TurnOnGreen(LED_PIN13, elapsedTime);
    TurnOnGreen(LED_PIN18, elapsedTime);
    TurnOnGreen(LED_PIN23, elapsedTime);
  };
  if (distance4> 160 && distance4 <= 190) {
    TurnOffAll();
    TurnOnGreen(LED_PIN4, elapsedTime);
    TurnOnGreen(LED_PIN9, elapsedTime);
    TurnOnGreen(LED_PIN14, elapsedTime);
    TurnOnGreen(LED_PIN19, elapsedTime);
    TurnOnGreen(LED_PIN24, elapsedTime);
  };
  if (distance4> 190 && distance4 <= 220) {
    TurnOffAll();
    TurnOnGreen(LED_PIN1, elapsedTime);
    TurnOnGreen(LED_PIN5, elapsedTime);
    TurnOnGreen(LED_PIN10, elapsedTime);
    TurnOnGreen(LED_PIN15, elapsedTime);
  };
  if (distance4> 220 && distance4 <= 250) {
    TurnOffAll();
    TurnOnGreen(LED_PIN6, elapsedTime);
  };
}

void DirectionRipple5(int distance5, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (distance5 <= 60) {
    TurnOffAll();
    TurnOnBlue(LED_PIN24, elapsedTime);
  };
  if (distance5> 60 && distance5 <= 100) {
    TurnOffAll();
    TurnOnBlue(LED_PIN15, elapsedTime);
    TurnOnBlue(LED_PIN19, elapsedTime);
    TurnOnBlue(LED_PIN23, elapsedTime);
    TurnOnBlue(LED_PIN25, elapsedTime);
  };
  if (distance5> 100 && distance5 <= 130) {
    TurnOffAll();
    TurnOnBlue(LED_PIN6, elapsedTime);
    TurnOnBlue(LED_PIN10, elapsedTime);
    TurnOnBlue(LED_PIN14, elapsedTime);
    TurnOnBlue(LED_PIN18, elapsedTime);
    TurnOnBlue(LED_PIN22, elapsedTime);
  };
  if (distance5> 130 && distance5 <= 160) {
    TurnOffAll();
    TurnOnBlue(LED_PIN5, elapsedTime);
    TurnOnBlue(LED_PIN9, elapsedTime);
    TurnOnBlue(LED_PIN13, elapsedTime);
    TurnOnBlue(LED_PIN17, elapsedTime);
    TurnOnBlue(LED_PIN21, elapsedTime);
  };
  if (distance5> 160 && distance5 <= 190) {
    TurnOffAll();
    TurnOnBlue(LED_PIN4, elapsedTime);
    TurnOnBlue(LED_PIN8, elapsedTime);
    TurnOnBlue(LED_PIN12, elapsedTime);
    TurnOnBlue(LED_PIN16, elapsedTime);
    TurnOnBlue(LED_PIN20, elapsedTime);
  };
  if (distance5> 190 && distance5 <= 220) {
    TurnOffAll();
    TurnOnBlue(LED_PIN1, elapsedTime);
    TurnOnBlue(LED_PIN3, elapsedTime);
    TurnOnBlue(LED_PIN7, elapsedTime);
    TurnOnBlue(LED_PIN11, elapsedTime);
  };
  if (distance5> 220 && distance5 <= 250) {
    TurnOffAll();
    TurnOnBlue(LED_PIN2, elapsedTime);
  };
}

void DirectionRipple6(int distance6, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance5 <= 60) {
    TurnOffAll();
    TurnOnPurple(LED_PIN25, elapsedTime);
  };
  if (distance5> 60 && distance5 <= 100) {
    TurnOffAll();
    TurnOnPurple(LED_PIN20, elapsedTime);
    TurnOnPurple(LED_PIN21, elapsedTime);
    TurnOnPurple(LED_PIN22, elapsedTime);
    TurnOnPurple(LED_PIN23, elapsedTime);
    TurnOnPurple(LED_PIN24, elapsedTime);
  };
  if (distance5> 100 && distance5 <= 130) {
    TurnOffAll();
    TurnOnPurple(LED_PIN16, elapsedTime);
    TurnOnPurple(LED_PIN17, elapsedTime);
    TurnOnPurple(LED_PIN18, elapsedTime);
    TurnOnPurple(LED_PIN19, elapsedTime);
  };
  if (distance5> 130 && distance5 <= 160) {
    TurnOffAll();
    TurnOnPurple(LED_PIN11, elapsedTime);
    TurnOnPurple(LED_PIN12, elapsedTime);
    TurnOnPurple(LED_PIN13, elapsedTime);
    TurnOnPurple(LED_PIN14, elapsedTime);
    TurnOnPurple(LED_PIN15, elapsedTime);
  };
  if (distance5> 160 && distance5 <= 190) {
    TurnOffAll();
    TurnOnPurple(LED_PIN7, elapsedTime);
    TurnOnPurple(LED_PIN8, elapsedTime);
    TurnOnPurple(LED_PIN9, elapsedTime);
    TurnOnPurple(LED_PIN10, elapsedTime);
  };
  if (distance5> 190 && distance5 <= 220) {
    TurnOffAll();
    TurnOnPurple(LED_PIN2, elapsedTime);
    TurnOnPurple(LED_PIN3, elapsedTime);
    TurnOnPurple(LED_PIN4, elapsedTime);
    TurnOnPurple(LED_PIN5, elapsedTime);
    TurnOnPurple(LED_PIN6, elapsedTime);
  };
  if (distance5> 220 && distance5 <= 250) {
    TurnOffAll();
    TurnOnPurple(LED_PIN1, elapsedTime);
  };
}


void loop() {
  // put your main code here, to run repeatedly:
  long elapsedTime = millis() - lastTime; //get time elapsed
  lastTime += elapsedTime;
  dist();
  // Prints the distance on the Serial Monitor
  Serial.print("Distance1: ");
  Serial.println(distance1);
  Serial.print("Distance2: ");
  Serial.println(distance2);
  Serial.print("Distance3: ");
  Serial.println(distance3);
  Serial.print("Distance4: ");
  Serial.println(distance4);
  Serial.print("Distance5: ");
  Serial.println(distance5);
  Serial.print("Distance6: ");
  Serial.println(distance6);
  if (triggeredNo > 1){
    CenterRipple(elapsedTime);
  } else{
  if (distance1 < 250) {
    DirectionRipple1(distance1, elapsedTime);
  } 
  if (distance2 < 250) {
    DirectionRipple2(distance2, elapsedTime);
  }
  if (distance3 < 250) {
    DirectionRipple3(distance3, elapsedTime);
  }  
  if (distance4 < 250) {
    DirectionRipple4(distance4, elapsedTime);
  }
  if (distance5 < 250) {
    DirectionRipple5(distance5, elapsedTime);
  }
  if (distance6 < 250) {
    DirectionRipple6(distance6, elapsedTime);
  }
}
}
