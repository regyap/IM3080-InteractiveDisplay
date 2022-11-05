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

//Max led pixels number [FILL IN MAX LED PIXELS NO!!!]
#define LED_COUNT 

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

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);

int brightness = 250;
int wait = 1000;

//for sensors
int maxDistance = 30;
int triggeredNo = 0;

//For multithreading
long lastTime = millis();

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(brightness);

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

void TurnOn(int pin, long elapsedMS) {
  strip.setPin(pin);
  strip.fill(strip.Color(0, 0, 127));
  strip.show();

  static long ledTime = 0;
  ledTime += elapsedMS;
  if (ledTime >= wait) {
    strip.clear();
    strip.show();
    ledTime -= wait;
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

void DirectionRipple1(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN1, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN6, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
  };
  if (ledTime >= 2000) {
    ledTime -= 2000;
  }
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN20, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple2(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= 1000) {
    TurnOn(LED_PIN2, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN11, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN6, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN15, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple3(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN6, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple4(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN6, elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple5(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= 1000) {
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN15, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN6, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN20, elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN1, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN11, elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN2, elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple6(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN25, elapsedTime);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN20, elapsedTime);
    TurnOn(LED_PIN21, elapsedTime);
    TurnOn(LED_PIN22, elapsedTime);
    TurnOn(LED_PIN23, elapsedTime);
    TurnOn(LED_PIN24, elapsedTime);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN16, elapsedTime);
    TurnOn(LED_PIN17, elapsedTime);
    TurnOn(LED_PIN18, elapsedTime);
    TurnOn(LED_PIN19, elapsedTime);    
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN11, elapsedTime);
    TurnOn(LED_PIN12, elapsedTime);
    TurnOn(LED_PIN13, elapsedTime);
    TurnOn(LED_PIN14, elapsedTime);
    TurnOn(LED_PIN15, elapsedTime);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN7, elapsedTime);
    TurnOn(LED_PIN8, elapsedTime);
    TurnOn(LED_PIN9, elapsedTime);
    TurnOn(LED_PIN10, elapsedTime);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN2, elapsedTime);
    TurnOn(LED_PIN3, elapsedTime);
    TurnOn(LED_PIN4, elapsedTime);
    TurnOn(LED_PIN5, elapsedTime);
    TurnOn(LED_PIN6, elapsedTime);
  };  
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN1, elapsedTime);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
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

  triggeredNo = 0;
}
