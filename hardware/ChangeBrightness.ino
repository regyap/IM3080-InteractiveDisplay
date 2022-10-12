#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//LED pins [FILL IN THE PIN NO!!]
#define LED_PIN1 
#define LED_PIN2
#define LED_PIN3
#define LED_PIN4
#define LED_PIN5
#define LED_PIN6
#define LED_PIN7
#define LED_PIN8
#define LED_PIN9
#define LED_PIN10 
#define LED_PIN11
#define LED_PIN12
#define LED_PIN13
#define LED_PIN14
#define LED_PIN15
#define LED_PIN16
#define LED_PIN17
#define LED_PIN18
#define LED_PIN19 
#define LED_PIN20
#define LED_PIN21
#define LED_PIN22
#define LED_PIN23
#define LED_PIN24
#define LED_PIN25
int ledPin[25] = {};


#define LED_COUNT 20

//Ultrasonic sensor pins [FILL IN PIN NO!!!]
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

Adafruit_NeoPixel strip(LED_COUNT, ledPin[0], NEO_GRB + NEO_KHZ800);

int brightnessLow = 150;
int brightnessHigh = 255;
int wait = 1000;

//for sensors
int maxDistance = 10;
int triggeredNo = 0

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


// Determine if a sensor is triggered
bool SensorIsTriggered(int trigPin, int echoPin, long elapsedMS) {
  digitalWrite(trigPin, LOW);

  static long sensorTime = 0;
  sensorTime += elapsedMS;
  if (sensorTime >= 2 && sensorTime < 12) {
    digitalWrite(trigPin, HIGH);
  }
  if (sensorTime >= 12) {
    digitalWrite(trigPin, LOW);
  }
  
  unsigned duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  if (distance <= maxDistance) {
    triggeredNo += 1;
    return true;
  } else {
    return false;
  }
}

void ChangeBrightness(int pin, long elapsedMS) {
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


void CenterRipple(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[12], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
    ChangeBrightness(ledPin[10], elapsedTime);
    ChangeBrightness(ledPin[14], elapsedTime);
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[0], elapsedTime);
    ChangeBrightness(ledPin[1], elapsedTime);
    ChangeBrightness(ledPin[5], elapsedTime);
    ChangeBrightness(ledPin[19], elapsedTime);
    ChangeBrightness(ledPin[23], elapsedTime);
    ChangeBrightness(ledPin[24], elapsedTime);
  };
  if (ledTime >= 4000) {
    ledTime -= 4000;
  }
}

void DirectionRipple1(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[0], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[1], elapsedTime);
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[5], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
  };
  if (ledTime >= 2000) {
    ledTime -= 2000;
  }
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[10], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[12], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[14], elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[19], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
    ChangeBrightness(ledPin[23], elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[24], elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple2(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[1], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[0], elapsedTime);
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[10], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[19], elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[12], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    ChangeBrightness(ledPin[5], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[14], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
    ChangeBrightness(ledPin[24], elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[23], elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple3(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[5], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[0], elapsedTime);
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
    ChangeBrightness(ledPin[14], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);
    ChangeBrightness(ledPin[23], elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[12], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    ChangeBrightness(ledPin[1], elapsedTime);
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[10], elapsedTime);
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
    ChangeBrightness(ledPin[24], elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[19], elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple4(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[19], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[10], elapsedTime);
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
    ChangeBrightness(ledPin[24], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[1], elapsedTime);
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[12], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);
    ChangeBrightness(ledPin[23], elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[0], elapsedTime);
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
    ChangeBrightness(ledPin[14], elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[5], elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple5(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[23], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[14], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
    ChangeBrightness(ledPin[24], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[5], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[12], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[19], elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[0], elapsedTime);
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[10], elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[1], elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple6(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    ChangeBrightness(ledPin[24], elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    ChangeBrightness(ledPin[19], elapsedTime);
    ChangeBrightness(ledPin[20], elapsedTime);
    ChangeBrightness(ledPin[21], elapsedTime);
    ChangeBrightness(ledPin[22], elapsedTime);
    ChangeBrightness(ledPin[23], elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    ChangeBrightness(ledPin[15], elapsedTime);
    ChangeBrightness(ledPin[16], elapsedTime);
    ChangeBrightness(ledPin[17], elapsedTime);
    ChangeBrightness(ledPin[18], elapsedTime);    
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    ChangeBrightness(ledPin[10], elapsedTime);
    ChangeBrightness(ledPin[11], elapsedTime);
    ChangeBrightness(ledPin[12], elapsedTime);
    ChangeBrightness(ledPin[13], elapsedTime);
    ChangeBrightness(ledPin[14], elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    ChangeBrightness(ledPin[6], elapsedTime);
    ChangeBrightness(ledPin[7], elapsedTime);
    ChangeBrightness(ledPin[8], elapsedTime);
    ChangeBrightness(ledPin[9], elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[1], elapsedTime);
    ChangeBrightness(ledPin[2], elapsedTime);
    ChangeBrightness(ledPin[3], elapsedTime);
    ChangeBrightness(ledPin[4], elapsedTime);
    ChangeBrightness(ledPin[5], elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    ChangeBrightness(ledPin[0], elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void rainbow(long elapsedTime) {      //wait = 20
  static int i = 0;
  static int j = 0 ;
  static long RainbowTime = 0;
  RainbowTime += elapsedTime;

  if (RainbowTime >= 100) {
    for (int n=0; n<25; n++) {
      strip.setPin(ledPin[n]);
    }
    if (i <= strip.numPixels()) {
      i++;
    }
    else if (i >= strip.numPixels()) {
      j++;
    }
    if (i + j >= 256) {
      i = 0;
      j = 0;
    }
    strip.fill(Wheel((i + j)));
    //    Serial.println(String(i + j));
    strip.show();

    RainbowTime -= 100;
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    //    Serial.println("red to blue -" + String(WheelPos * 3));
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    //    Serial.println("blue to green =" + String(WheelPos * 3));
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  //  Serial.println("green to red _" + String(WheelPos * 3));
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  long elapsedTime = millis() - lastTime; //get time elapsed
  lastTime += elapsedTime;

  bool sensor1Triggered = SensorIsTriggered(trigPin1, echoPin1, elapsedTime);
  bool sensor2Triggered = SensorIsTriggered(trigPin2, echoPin2, elapsedTime);
  bool sensor3Triggered = SensorIsTriggered(trigPin3, echoPin3, elapsedTime);
  bool sensor4Triggered = SensorIsTriggered(trigPin4, echoPin4, elapsedTime);
  bool sensor5Triggered = SensorIsTriggered(trigPin5, echoPin5, elapsedTime);
  bool sensor6Triggered = SensorIsTriggered(trigPin6, echoPin6, elapsedTime);

  if (triggeredNo > 1) {
    CenterRipple(elapsedTime);
  }else if (triggeredNo == 1){
    if (sensor1Triggered){
      DirectionRipple1(elapsedTime);
    }
    if (sensor2Triggered){
      DirectionRipple2(elapsedTime);
    }
    if (sensor3Triggered){
      DirectionRipple3(elapsedTime);
    }
    if (sensor4Triggered){
      DirectionRipple4(elapsedTime);
    }
    if (sensor5Triggered){
      DirectionRipple5(elapsedTime);
    }
    if (sensor6Triggered){
      DirectionRipple6(elapsedTime);
    }
  }
  rainbow(20);

  triggeredNo = 0;
}
