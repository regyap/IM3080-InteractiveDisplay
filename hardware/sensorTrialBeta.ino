#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
int distance;
unsigned duration;

//LED pins
//first circle
#define LED_PIN13 22
//second circle
#define LED_PIN8 9
#define LED_PIN9 10
#define LED_PIN12 13
#define LED_PIN14 23
#define LED_PIN17 26
#define LED_PIN18 27
//third circle
#define LED_PIN3 4
#define LED_PIN4 5
#define LED_PIN5 6
#define LED_PIN7 8
#define LED_PIN10 11
#define LED_PIN11 12
#define LED_PIN15 24
#define LED_PIN16 25
#define LED_PIN19 28
#define LED_PIN21 30
#define LED_PIN22 31
#define LED_PIN23 32
//forth circle
#define LED_PIN1 2
#define LED_PIN2 3
#define LED_PIN6 7
#define LED_PIN20 29
#define LED_PIN24 33
#define LED_PIN25 34



#define LED_COUNT 20

//Ultrasonic sensor pins
#define trigPin1 10
#define trigPin2 11
#define trigPin3 12
#define trigPin4 13
#define trigPin5 14
#define trigPin6 15
#define echoPin1 6
#define echoPin2 7
#define echoPin3 8
#define echoPin4 9
#define echoPin5 16
#define echoPin6 17

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

  if (distance <= maxDistance) {
    triggeredNo += 1;
  } 
}

void TurnOn(int pin, long elapsedMS) {
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
    TurnOn(LED_PIN13, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN6, elapsedTime);
    TurnOn(LED_PIN20, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (ledTime >= 4000) {
    ledTime -= 4000;
  }
}

void DirectionRipple1(int distance1, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance1 <= 60) {
    TurnOffAll();
    TurnOn(LED_PIN1, elapsedTime);
  };
  if (distance1 > 60 && distance1 <= 100) {
    TurnOffAll();
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN6, elapsedTime);
  };
  if (distance1 > 100 && distance1 <= 130) {
    TurnOffAll();
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
  };
  if (distance1 > 130 && distance1 <= 160) {
    TurnOffAll();
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (distance1 > 160 && distance1 <= 190) {
    TurnOffAll();
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
  };
  if (distance1 > 190 && distance1 <= 220) {
    TurnOffAll();
    TurnOn(LED_PIN20, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (distance1 > 220 && distance1 <= 250) {
    TurnOffAll();
    TurnOn(LED_PIN25, elapsedTime);
  };
}

void DirectionRipple2(int distance2, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (distance1 <= 60) {
    TurnOffAll();
    TurnOn(LED_PIN2, elapsedTime);
  };
  if (distance2 > 60 && distance2 <= 100) {
    TurnOffAll();
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN11, elapsedTime);
  };
  if (distance2 > 100 && distance2 <= 130) {
    TurnOffAll();
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (distance2 > 130 && distance2 <= 160) {
    TurnOffAll();
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
  };
  if (distance2 > 160 && distance2 <= 190) {
    TurnOffAll();
    TurnOn(LED_PIN6, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (distance2 > 190 && distance2 <= 220) {
    TurnOffAll();
    TurnOn(LED_PIN15, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (distance2 > 220 && distance2 <= 250) {
    TurnOffAll();
    TurnOn(LED_PIN24, elapsedTime);
  };
}

void DirectionRipple3(int distance3, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance3 <= 60) {
    TurnOffAll();
    TurnOn(LED_PIN6, elapsedTime);
  };
  if (distance3 > 60 && distance3 <= 100) {
    TurnOffAll();
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (distance3 > 100 && distance3 <= 130) {
    TurnOffAll();
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (distance3 > 130 && distance3 <= 160) {
    TurnOffAll();
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
  };
  if (distance3 > 160 && distance3 <= 190) {
    TurnOffAll();
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (distance3 > 190 && distance3 <= 220) {
    TurnOffAll();
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (distance3 > 220 && distance3 <= 250) {
    TurnOffAll();
    TurnOn(LED_PIN20, elapsedTime);
  };
}

void DirectionRipple4(int distance4, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance4 > 60) {
    TurnOffAll();
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (distance4> 60 && distance4 <= 100) {
    TurnOffAll();
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (distance4> 100 && distance4 <= 130) {
    TurnOffAll();
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (distance4> 130 && distance4 <= 160) {
    TurnOffAll();
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
  };
  if (distance4> 160 && distance4 <= 190) {
    TurnOffAll();
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (distance4> 190 && distance4 <= 220) {
    TurnOffAll();
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (distance4> 220 && distance4 <= 250) {
    TurnOffAll();
    TurnOn(LED_PIN6, elapsedTime);
  };
}

void DirectionRipple5(int distance5, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (distance5 <= 60) {
    TurnOffAll();
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (distance5> 60 && distance5 <= 100) {
    TurnOffAll();
    TurnOn(LED_PIN15, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (distance5> 100 && distance5 <= 130) {
    TurnOffAll();
    TurnOn(LED_PIN6, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (distance5> 130 && distance5 <= 160) {
    TurnOffAll();
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
  };
  if (distance5> 160 && distance5 <= 190) {
    TurnOffAll();
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (distance5> 190 && distance5 <= 220) {
    TurnOffAll();
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN11, elapsedTime);
  };
  if (distance5> 220 && distance5 <= 250) {
    TurnOffAll();
    TurnOn(LED_PIN2, elapsedTime);
  };
}

void DirectionRipple6(int distance6, long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (distance5 <= 60) {
    TurnOffAll();
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (distance5> 60 && distance5 <= 100) {
    TurnOffAll();
    TurnOn(LED_PIN20, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (distance5> 100 && distance5 <= 130) {
    TurnOffAll();
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
  };
  if (distance5> 130 && distance5 <= 160) {
    TurnOffAll();
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (distance5> 160 && distance5 <= 190) {
    TurnOffAll();
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
  };
  if (distance5> 190 && distance5 <= 220) {
    TurnOffAll();
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN6, elapsedTime);
  };
  if (distance5> 220 && distance5 <= 250) {
    TurnOffAll();
    TurnOn(LED_PIN1, elapsedTime);
  };
}

void rainbow(uint8_t wait) {
  uint16_t i;
  uint16_t j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {


      strip.setPixelColor(i, Wheel((i + j)));
    }
    strip.show();
//    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
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
  }
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
