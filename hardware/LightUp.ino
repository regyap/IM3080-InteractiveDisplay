#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//LED pins [FILL IN THE PIN NO!!]
#define LED_PIN1 27
#define LED_PIN2 28
#define LED_PIN3 29
#define LED_PIN4 30
#define LED_PIN5 31
#define LED_PIN6 32
#define LED_PIN7 33
#define LED_PIN8 22
#define LED_PIN9 35
#define LED_PIN10 36
#define LED_PIN11 37
#define LED_PIN12 38
#define LED_PIN13 39
#define LED_PIN14 40
#define LED_PIN15 41
#define LED_PIN16 42
#define LED_PIN17 43
#define LED_PIN18 44
#define LED_PIN19 45
#define LED_PIN20 46
#define LED_PIN21 47
#define LED_PIN22 48
#define LED_PIN23 49
#define LED_PIN24 50
#define LED_PIN25 51

//Max led pixels number [FILL IN MAX LED PIXELS NO!!!]
#define LED_COUNT 50

//Ultrasonic sensor pins [FILL IN PIN NO!!!]
#define trigPin1 5
#define trigPin2 8
#define trigPin3 3
#define trigPin4 10
#define trigPin5 14
#define trigPin6 12
#define echoPin1 6
#define echoPin2 7
#define echoPin3 2
#define echoPin4 9
#define echoPin5 13
#define echoPin6 11

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);

int brightness = 250;
int wait = 1000;

//for sensors
int maxDistance = 30;
int triggeredNo = 0;

//For multithreading
long lastTime = millis();


void setup() {
  //  Reset();
  //  delay(1000);
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

bool SensorIsTriggered(int trigPin, int echoPin) {
  //
  //  Serial.println(String(trigPin) + "..." + String(echoPin));

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned duration = pulseIn(echoPin, HIGH);


  Serial.println(duration);


  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= maxDistance) {
    triggeredNo += 1;
    return true;
  } else {
    return false;
  }
}

void TurnOn(int pin) {
  strip.setPin(pin);
  strip.fill(strip.Color(0, 0, 127));
  strip.show();

}

void TurnOff(int pin) {
  strip.setPin(pin);
  strip.clear();
  strip.show();
}


void CenterRipple(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime < 2000) {
    TurnOn(LED_PIN13);
  };
  if (ledTime >= 2000 && ledTime < 4000) {
    TurnOff(LED_PIN13);

    TurnOn(LED_PIN8);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN18);
  };
  if (ledTime >= 4000 && ledTime < 6000) {
    TurnOff(LED_PIN8);
    TurnOff(LED_PIN9);
    TurnOff(LED_PIN12);
    TurnOff(LED_PIN14);
    TurnOff(LED_PIN17);
    TurnOff(LED_PIN18);

    TurnOn(LED_PIN3);
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN11);
    TurnOn(LED_PIN15);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN22);
    TurnOn(LED_PIN23);
  };
  if (ledTime >= 6000 && ledTime < 8000) {
    TurnOff(LED_PIN3);
    TurnOff(LED_PIN4);
    TurnOff(LED_PIN5);
    TurnOff(LED_PIN7);
    TurnOff(LED_PIN10);
    TurnOff(LED_PIN11);
    TurnOff(LED_PIN15);
    TurnOff(LED_PIN16);
    TurnOff(LED_PIN19);
    TurnOff(LED_PIN21);
    TurnOff(LED_PIN22);
    TurnOff(LED_PIN23);

    TurnOn(LED_PIN1);
    TurnOn(LED_PIN2);
    TurnOn(LED_PIN6);
    TurnOn(LED_PIN20);
    TurnOn(LED_PIN24);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 8000) {
    TurnOff(LED_PIN1);
    TurnOff(LED_PIN2);
    TurnOff(LED_PIN6);
    TurnOff(LED_PIN20);
    TurnOff(LED_PIN24);
    TurnOff(LED_PIN25);

    ledTime -= 8000;
  }
}

void DirectionRipple1(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN1);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOff(LED_PIN1);

    TurnOn(LED_PIN2);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN6);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOff(LED_PIN2);
    TurnOff(LED_PIN3);
    TurnOff(LED_PIN4);
    TurnOff(LED_PIN5);
    TurnOff(LED_PIN6);

    TurnOn(LED_PIN7);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN10);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOff(LED_PIN7);
    TurnOff(LED_PIN8);
    TurnOff(LED_PIN9);
    TurnOff(LED_PIN10);

    TurnOn(LED_PIN11);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOff(LED_PIN11);
    TurnOff(LED_PIN12);
    TurnOff(LED_PIN13);
    TurnOff(LED_PIN14);
    TurnOff(LED_PIN15);
    
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN19);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOff(LED_PIN16);
    TurnOff(LED_PIN17);
    TurnOff(LED_PIN18);
    TurnOff(LED_PIN19);
    
    TurnOn(LED_PIN20);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN22);
    TurnOn(LED_PIN23);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOff(LED_PIN20);
    TurnOff(LED_PIN21);
    TurnOff(LED_PIN22);
    TurnOff(LED_PIN23);
    TurnOff(LED_PIN24);
    
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 6000) {
    TurnOff(LED_PIN25);
    
    ledTime -= 6000;
  }
}

void DirectionRipple2(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= 1000) {
    TurnOn(LED_PIN2);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN1);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN11);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN20);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN21);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN6);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN15);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN23);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN24);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple3(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN6);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN1);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN23);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN2);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN11);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN20);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple4(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN20);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN11);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN2);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN23);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN1);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN6);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple5(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= 1000) {
    TurnOn(LED_PIN24);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN15);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN23);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN6);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN21);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN20);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN1);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN11);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN2);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void DirectionRipple6(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= 1000) {
    TurnOn(LED_PIN25);
  };
  if (ledTime >= 1000 && ledTime < 2000) {
    TurnOn(LED_PIN20);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN22);
    TurnOn(LED_PIN23);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= 2000 && ledTime < 3000) {
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN19);
  };
  if (ledTime >= 3000 && ledTime < 4000) {
    TurnOn(LED_PIN11);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= 4000 && ledTime < 5000) {
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN10);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN2);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN6);
  };
  if (ledTime >= 5000 && ledTime < 6000) {
    TurnOn(LED_PIN1);
  };
  if (ledTime >= 6000) {
    ledTime -= 6000;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  long elapsedTime = millis() - lastTime; //get time elapsed
  lastTime += elapsedTime;
  //  CenterRipple(elapsedTime);


  //  bool sensor1Triggered = SensorIsTriggered(trigPin1, echoPin1);
  //  bool sensor2Triggered = SensorIsTriggered(trigPin2, echoPin2);
  //  bool sensor3Triggered = SensorIsTriggered(trigPin3, echoPin3);
  //  bool sensor4Triggered = SensorIsTriggered(trigPin4, echoPin4);
  //  bool sensor5Triggered = SensorIsTriggered(trigPin5, echoPin5);
  //  bool sensor6Triggered = SensorIsTriggered(trigPin6, echoPin6);

  //  if (triggeredNo > 1) {
  //    CenterRipple(elapsedTime);
  //  }else if (triggeredNo == 1){
  //    if (sensor1Triggered){
  //      DirectionRipple1(elapsedTime);
  //    }
  //    if (sensor2Triggered){
  //      DirectionRipple2(elapsedTime);
  //    }
  //    if (sensor3Triggered){
  //      DirectionRipple3(elapsedTime);
  //    }
  //    if (sensor4Triggered){
  //      DirectionRipple4(elapsedTime);
  //    }
  //    if (sensor5Triggered){
  //      DirectionRipple5(elapsedTime);
  //    }
  //    if (sensor6Triggered){
  //      DirectionRipple6(elapsedTime);
  //    }
  //  }
  //
  if (SensorIsTriggered(trigPin3, echoPin3)) {

    DirectionRipple1(elapsedTime);
  }
  //
  //  triggeredNo = 0;
}
