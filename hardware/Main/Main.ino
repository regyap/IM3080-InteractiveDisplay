#include <Adafruit_NeoPixel.h>
#include <Arduino_JSON.h>
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
#define echoPin1 4
#define echoPin2 7
#define echoPin3 2
#define echoPin4 9
#define echoPin5 13
#define echoPin6 11

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN1, NEO_BRG + NEO_KHZ800), strip3(LED_COUNT, LED_PIN2, NEO_BRG + NEO_KHZ800);

int brightness = 250;
uint32_t color = strip.Color(0, 0, 255);
int timeInterval = 300;

//For multithreading
long lastTime = 0;

// for beats
int beatIndex = 0;

//for sensors
int maxDistance = 30;
int triggeredNo = 0;


// beat array
long beat[] = {17, 484, 810, 2683, 4180, 4738, 6003, 6359, 6721, 7952, 8488,
               8809, 10204, 10698, 11459, 13676, 14699, 15996, 16768, 18746,
               20710, 22732, 23948, 24740, 26720, 27457, 29703, 30743, 31993,
               32771, 34720, 36717, 38087, 38702, 40486, 40796, 42714, 43461,
               44281, 45696, 46721, 47996, 48778, 50719, 52715, 54094, 54729,
               55946, 56719, 58734, 59457, 60227, 61719, 63985, 64789, 66706,
               68703, 70102, 70739, 71958, 72726, 74709, 75455, 76235, 77706,
               80682, 82678, 84685, 86694, 88692, 90674, 91495, 92213, 93699,
               94738, 95745, 96477, 96780, 97082, 98677, 100680, 102682, 103943,
               104470, 106687, 107498, 108237, 109702, 110692, 112674, 113444,
               114672, 116679, 117460, 118699, 119945, 120696, 121470, 122671,
               124225, 124695, 125463, 126687, 127979, 128670, 129438, 130667,
               132689, 133460, 34685, 135948, 136674, 137471, 138670, 140246,
               140685, 141458, 142686, 143996, 144682, 145456, 146672, 148687,
               149472, 150693, 152704, 154682
              };

long beat1[] = {15, 728, 1459, 2207, 2966, 3671, 4467, 4850, 5217, 5973, 6679,
                7489, 7861, 8968, 9672, 10463, 10850, 11954, 12664, 13490, 13850,
                14233, 14966, 15656, 16474, 16856, 17979, 18649, 19483, 19844,
                20218, 20978, 21673, 22469, 22854, 23221, 23978, 24659, 25475,
                25859, 26956, 27657, 28480, 28829, 29229, 29979, 30649, 31464,
                31844, 32239, 32967, 33668, 34480, 34843, 35982, 36671, 37489,
                37848, 38211, 38980, 39638, 40467, 40855, 41964, 42656, 43476,
                43853, 44229, 44966, 45674, 46479, 46837, 47222, 47982, 48655,
                49482, 49844, 51865, 52523, 53230, 54755, 55294, 55952, 56688,
                57791, 58151, 58512, 59201, 60748, 61283, 61983, 63903, 65244,
                66738, 67302, 67969, 68654, 69748, 70168, 71234, 72730, 73285,
                73950, 74964, 75669, 76469, 76852, 77209, 77976, 78664, 79451,
                79849, 80970, 81662, 82501, 82838, 83963, 84682, 85476, 85833,
                86219, 86973, 87650, 88457, 88842, 89966, 90673, 91472, 91855,
                92210, 92966, 93678, 94481, 94853, 95222, 95973, 96654, 97477,
                97842, 98964, 99660, 100468, 100852, 101232, 101971, 102655,
                103456, 103843, 104983, 105661, 106467, 106865, 107967, 108670,
                109476, 109847, 110216, 110962, 111648, 112486, 112848, 113982,
                114658, 115484, 115868, 116220, 116961, 117666, 118483, 118829,
                119981, 120657, 121483, 121846, 123889, 124506, 125253, 126768,
                127300, 127948, 129872
               };


void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  strip.setBrightness(brightness);

  strip3.begin();
  strip3.show();
  strip3.setBrightness(brightness);

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

// from rasberry pi to arduino
JSONVar payload;
String mode;

void loop() {
  if (Serial.available() > 0) {
    payload = JSON.parse(Serial.readStringUntil('\n'));
    mode = payload["mode"];
  }

  long elapsedTime = millis() - lastTime;
  lastTime = lastTime + elapsedTime;

  if (mode == "raise") {
    //  uint32_t color = strip.Color(int(payload["red"]), int(payload["green"]), int(payload["blue"]));
    //  raise(elapsedTime, color);

    raise(elapsedTime);
  }
  else if (mode == "ripple") {
    // ripple with sensor


    bool sensor1Triggered = SensorIsTriggered(trigPin1, echoPin1);
    bool sensor2Triggered = SensorIsTriggered(trigPin2, echoPin2);
    bool sensor3Triggered = SensorIsTriggered(trigPin3, echoPin3);
    bool sensor4Triggered = SensorIsTriggered(trigPin4, echoPin4);
    bool sensor5Triggered = SensorIsTriggered(trigPin5, echoPin5);
    bool sensor6Triggered = SensorIsTriggered(trigPin6, echoPin6);

    if (triggeredNo > 1) {
      CenterRipple(elapsedTime);
    } else if (triggeredNo == 1) {
      if (sensor1Triggered) {
        DirectionRipple1(elapsedTime);
      }
      if (sensor2Triggered) {
        DirectionRipple2(elapsedTime);
      }
      if (sensor3Triggered) {
        DirectionRipple3(elapsedTime);
      }
      if (sensor4Triggered) {
        DirectionRipple4(elapsedTime);
      }
      if (sensor5Triggered) {
        DirectionRipple5(elapsedTime);
      }
      if (sensor6Triggered) {
        DirectionRipple6(elapsedTime);
      }
    }

  }
  else if (mode == "centerRipple") {
    // centerripple only

    CenterRipple(elapsedTime);
    Serial.println("CenterRipple only");
  }
  else if (mode == "directionRipple") {
    // DirectionRipple5 only

    DirectionRipple5(elapsedTime);
    Serial.println("DirectionRipple5 only");
  }
  else if (mode == "storymode") {
    storymode(elapsedTime);
    Serial.println("Story Time");
  }
  else if (mode == "rgb") {
    uint32_t color = strip.Color(int(payload["red"]), int(payload["green"]), int(payload["blue"]));
    strip.setPin(2);
    strip.fill(color);
    strip.setPin(3);
    strip.fill(color);
    strip.setPin(4);
    strip.fill(color);
  } else if (mode == "test") {
    for (int i = 22; i <= 51; i++) {
      strip.setPin(i);
      strip.fill(strip.Color(255, 0, 0));
      strip.show();
    }
  }
  else if (mode == "Rainbow") {
    // --- [ just a placeholder ] ---
    for (int i = 22; i <= 51; i++) {
      strip.setPin(i);
      Serial.println(String(i));
      rainbow(elapsedTime);
    }
  }
}








// function      -------- raise --------

void raise(long elapsedTime) {
  static long ledTime = 0;
  static long raiseTime = 0;
  static long pixel = 0;

  ledTime += elapsedTime;

  if (ledTime >= beat[beatIndex] - 400) {
    raiseTime = ledTime - beat[beatIndex];
    if (raiseTime <= 1000) {

      if (raiseTime < 700) {
        setAllTubes_Beats(strip.Color(255, 0, 255), pixel);
        pixel++;
        setAllTubes_Beats(strip.Color(255, 0, 255), pixel);
        pixel++;
        setAllTubes_Beats(strip.Color(255, 0, 255), pixel);
        pixel++;
        setAllTubes_Beats(strip.Color(255, 0, 255), pixel);
        pixel++;
        setAllTubes_Beats(strip.Color(255, 0, 255), pixel);
        pixel++;
        Serial.println("===============");
      }
      else {
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
      }

      strip.show();
      strip3.show();
      //Serial.println("raiseTime :" + String(raiseTime));
    } else {
      strip.clear();
      strip.show();
      strip3.clear();
      strip3.show();
      pixel = 0;
      beatIndex += 1;
    }

  }
  else {
    strip.clear();
    strip.show();
    strip3.clear();
    strip3.show();
  }
}

void raiseColor(long elapsedTime, uint32_t color) {
  static long ledTime = 0;
  static long raiseTime = 0;
  static long pixel = 0;

  ledTime += elapsedTime;

  if (ledTime >= beat[beatIndex] - 400) {
    raiseTime = ledTime - beat[beatIndex];
    if (raiseTime <= 1000) {

      if (raiseTime < 800) {
        setAllTubes_Beats(color, pixel);
        pixel++;
        setAllTubes_Beats(color, pixel);
        pixel++;
        setAllTubes_Beats(color, pixel);
        pixel++;
        setAllTubes_Beats(color, pixel);
        pixel++;
        setAllTubes_Beats(color, pixel);
        pixel++;
        Serial.println("===============");
      }
      else {
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
        setAllTubes_Beats(strip.Color(0, 0, 0), pixel);
        pixel--;
      }

      strip.show();
      strip3.show();
      //Serial.println("raiseTime :" + String(raiseTime));
    } else {
      strip.clear();
      strip.show();
      strip3.clear();
      strip3.show();
      pixel = 0;
      beatIndex += 1;
    }

  }
  else {
    strip.clear();
    strip.show();
    strip3.clear();
    strip3.show();
  }
}





// function      -------- SensorIsTriggered & turnOn/Off --------

bool SensorIsTriggered(int trigPin, int echoPin) {
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
  strip.fill(color);
  strip.show();

}

void TurnOff(int pin) {
  strip.setPin(pin);
  strip.clear();
  strip.show();
}


// function      -------- CenterRipple --------

void CenterRipple(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  static int counter = 0;
  Serial.println(counter);
  if (counter % 5 == 0) {

    if (ledTime < timeInterval) {
      brightness = 255; //Brightness decreases for each ripple wave
      color = strip.Color(0, 0, 255); //Color changes for each ripple wave
      TurnOn(LED_PIN13);
    };
    if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
      brightness = 235;
      color = strip.Color(0, 50, 235);
      TurnOff(LED_PIN13);

      TurnOn(LED_PIN8);
      TurnOn(LED_PIN9);
      TurnOn(LED_PIN12);
      TurnOn(LED_PIN14);
      TurnOn(LED_PIN17);
      TurnOn(LED_PIN18);
    };
    if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
      brightness = 215;
      color = strip.Color(0, 100, 215);
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
    if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
      brightness = 195;
      color = strip.Color(0, 150, 195);
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
    if (ledTime >= timeInterval * 4) {
      TurnOff(LED_PIN1);
      TurnOff(LED_PIN2);
      TurnOff(LED_PIN6);
      TurnOff(LED_PIN20);
      TurnOff(LED_PIN24);
      TurnOff(LED_PIN25);

      ledTime -= timeInterval * 4;
      counter++;
    }
  }
}


// function      -------- DirectionRipple1 --------

void DirectionRipple1(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= timeInterval) {
    brightness = 255;
    color = strip.Color(0, 0, 255); //Color changes for each ripple wave
    TurnOn(LED_PIN1);
  };
  if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
    brightness = 240;
    color = strip.Color(0, 40, 235);
    TurnOff(LED_PIN1);

    TurnOn(LED_PIN2);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN6);
  };
  if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
    brightness = 225;
    color = strip.Color(0, 80, 215);
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
  if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
    brightness = 210;
    color = strip.Color(0, 120, 195);
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
  if (ledTime >= timeInterval * 4 && ledTime < timeInterval * 5) {
    brightness = 195;
    color = strip.Color(0, 160, 175);
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
  if (ledTime >= timeInterval * 5 && ledTime < timeInterval * 6) {
    brightness = 180;
    color = strip.Color(0, 200, 155);
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
  if (ledTime >= timeInterval * 6 && ledTime < timeInterval * 7) {
    brightness = 165;
    color = strip.Color(0, 240, 135);
    TurnOff(LED_PIN20);
    TurnOff(LED_PIN21);
    TurnOff(LED_PIN22);
    TurnOff(LED_PIN23);
    TurnOff(LED_PIN24);

    TurnOn(LED_PIN25);
  };
  if (ledTime >= timeInterval * 7) {
    TurnOff(LED_PIN25);

    ledTime -= timeInterval * 7;
  }
}


// function      -------- DirectionRipple2 --------

void DirectionRipple2(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;
  if (ledTime <= timeInterval) {
    brightness = 255;
    color = strip.Color(0, 0, 255);
    TurnOn(LED_PIN2);
  };
  if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
    brightness = 240;
    color = strip.Color(0, 40, 235);
    TurnOff(LED_PIN2);

    TurnOn(LED_PIN1);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN11);
  };
  if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
    brightness = 225;
    color = strip.Color(0, 80, 215);
    TurnOff(LED_PIN1);
    TurnOff(LED_PIN3);
    TurnOff(LED_PIN7);
    TurnOff(LED_PIN11);

    TurnOn(LED_PIN4);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN20);
  };
  if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
    brightness = 210;
    color = strip.Color(0, 120, 195);
    TurnOff(LED_PIN4);
    TurnOff(LED_PIN8);
    TurnOff(LED_PIN12);
    TurnOff(LED_PIN16);
    TurnOff(LED_PIN20);

    TurnOn(LED_PIN5);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN21);
  };
  if (ledTime >= timeInterval * 4 && ledTime < timeInterval * 5) {
    brightness = 195;
    color = strip.Color(0, 160, 175);
    TurnOff(LED_PIN5);
    TurnOff(LED_PIN9);
    TurnOff(LED_PIN13);
    TurnOff(LED_PIN17);
    TurnOff(LED_PIN21);

    TurnOn(LED_PIN6);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= timeInterval * 5 && ledTime < timeInterval * 6) {
    brightness = 180;
    color = strip.Color(0, 200, 155);
    TurnOff(LED_PIN6);
    TurnOff(LED_PIN10);
    TurnOff(LED_PIN14);
    TurnOff(LED_PIN18);
    TurnOff(LED_PIN22);

    TurnOn(LED_PIN15);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN23);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= timeInterval * 6 && ledTime < timeInterval * 7) {
    brightness = 165;
    color = strip.Color(0, 240, 135);
    TurnOff(LED_PIN15);
    TurnOff(LED_PIN19);
    TurnOff(LED_PIN23);
    TurnOff(LED_PIN25);

    TurnOn(LED_PIN24);
  };
  if (ledTime >= timeInterval * 7) {
    TurnOff(LED_PIN24);

    ledTime -= timeInterval * 7;
  }
}


// function      -------- DirectionRipple3 --------

void DirectionRipple3(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= timeInterval) {
    brightness = 255;
    color = strip.Color(0, 0, 255);
    TurnOn(LED_PIN6);
  };
  if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
    brightness = 240;
    color = strip.Color(0, 40, 235);
    TurnOff(LED_PIN6);

    TurnOn(LED_PIN1);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
    brightness = 225;
    color = strip.Color(0, 80, 215);
    TurnOff(LED_PIN1);
    TurnOff(LED_PIN5);
    TurnOff(LED_PIN10);
    TurnOff(LED_PIN15);

    TurnOn(LED_PIN4);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
    brightness = 210;
    color = strip.Color(0, 120, 195);
    TurnOff(LED_PIN4);
    TurnOff(LED_PIN9);
    TurnOff(LED_PIN14);
    TurnOff(LED_PIN19);
    TurnOff(LED_PIN24);

    TurnOn(LED_PIN3);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN23);
  };
  if (ledTime >= timeInterval * 4 && ledTime < timeInterval * 5) {
    brightness = 195;
    color = strip.Color(0, 160, 175);
    TurnOff(LED_PIN3);
    TurnOff(LED_PIN8);
    TurnOff(LED_PIN13);
    TurnOff(LED_PIN18);
    TurnOff(LED_PIN23);

    TurnOn(LED_PIN2);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= timeInterval * 5 && ledTime < timeInterval * 6) {
    brightness = 180;
    color = strip.Color(0, 200, 155);
    TurnOff(LED_PIN2);
    TurnOff(LED_PIN7);
    TurnOff(LED_PIN12);
    TurnOff(LED_PIN17);
    TurnOff(LED_PIN22);

    TurnOn(LED_PIN11);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= timeInterval * 6 && ledTime < timeInterval * 7) {
    brightness = 165;
    color = strip.Color(0, 240, 135);
    TurnOff(LED_PIN11);
    TurnOff(LED_PIN16);
    TurnOff(LED_PIN21);
    TurnOff(LED_PIN25);

    TurnOn(LED_PIN20);
  };
  if (ledTime >= timeInterval * 7) {
    TurnOff(LED_PIN20);

    ledTime -= timeInterval * 7;
  }
}


// function      -------- DirectionRipple4 --------

void DirectionRipple4(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= timeInterval) {
    brightness = 255;
    color = strip.Color(0, 0, 255);
    TurnOn(LED_PIN20);
  };
  if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
    brightness = 240;
    color = strip.Color(0, 40, 235);
    TurnOff(LED_PIN20);

    TurnOn(LED_PIN11);
    TurnOn(LED_PIN16);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
    brightness = 225;
    color = strip.Color(0, 80, 215);
    TurnOff(LED_PIN11);
    TurnOff(LED_PIN16);
    TurnOff(LED_PIN21);
    TurnOff(LED_PIN25);

    TurnOn(LED_PIN2);
    TurnOn(LED_PIN7);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN22);
  };
  if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
    brightness = 210;
    color = strip.Color(0, 120, 195);
    TurnOff(LED_PIN2);
    TurnOff(LED_PIN7);
    TurnOff(LED_PIN12);
    TurnOff(LED_PIN17);
    TurnOff(LED_PIN22);

    TurnOn(LED_PIN3);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN23);
  };
  if (ledTime >= timeInterval * 4 && ledTime < timeInterval * 5) {
    brightness = 195;
    color = strip.Color(0, 160, 175);
    TurnOff(LED_PIN3);
    TurnOff(LED_PIN8);
    TurnOff(LED_PIN13);
    TurnOff(LED_PIN18);
    TurnOff(LED_PIN23);

    TurnOn(LED_PIN4);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN19);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= timeInterval * 5 && ledTime < timeInterval * 6) {
    brightness = 180;
    color = strip.Color(0, 200, 155);
    TurnOff(LED_PIN4);
    TurnOff(LED_PIN9);
    TurnOff(LED_PIN14);
    TurnOff(LED_PIN19);
    TurnOff(LED_PIN24);

    TurnOn(LED_PIN1);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN10);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= timeInterval * 6 && ledTime < timeInterval * 7) {
    brightness = 165;
    color = strip.Color(0, 240, 135);
    TurnOff(LED_PIN1);
    TurnOff(LED_PIN5);
    TurnOff(LED_PIN10);
    TurnOff(LED_PIN15);

    TurnOn(LED_PIN6);
  };
  if (ledTime >= timeInterval * 7) {
    TurnOff(LED_PIN6);

    ledTime -= timeInterval * 7;
  }
}


// function      -------- DirectionRipple5 --------

void DirectionRipple5(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  static int counter = 0;
  Serial.println(counter);
  if (counter % 5 == 0) {

    if (ledTime <= timeInterval) {
      brightness = 255;
      color = strip.Color(0, 0, 255);
      TurnOn(LED_PIN24);
    };
    if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
      brightness = 240;
      color = strip.Color(0, 40, 235);
      TurnOff(LED_PIN24);

      TurnOn(LED_PIN15);
      TurnOn(LED_PIN19);
      TurnOn(LED_PIN23);
      TurnOn(LED_PIN25);
    };
    if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
      brightness = 225;
      color = strip.Color(0, 80, 215);
      TurnOff(LED_PIN15);
      TurnOff(LED_PIN19);
      TurnOff(LED_PIN23);
      TurnOff(LED_PIN25);

      TurnOn(LED_PIN6);
      TurnOn(LED_PIN10);
      TurnOn(LED_PIN14);
      TurnOn(LED_PIN18);
      TurnOn(LED_PIN22);
    };
    if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
      brightness = 210;
      color = strip.Color(0, 120, 195);
      TurnOff(LED_PIN6);
      TurnOff(LED_PIN10);
      TurnOff(LED_PIN14);
      TurnOff(LED_PIN18);
      TurnOff(LED_PIN22);

      TurnOn(LED_PIN5);
      TurnOn(LED_PIN9);
      TurnOn(LED_PIN13);
      TurnOn(LED_PIN17);
      TurnOn(LED_PIN21);
    };
    if (ledTime >= timeInterval * 4 && ledTime < timeInterval * 5) {
      brightness = 195;
      color = strip.Color(0, 160, 175);
      TurnOff(LED_PIN5);
      TurnOff(LED_PIN9);
      TurnOff(LED_PIN13);
      TurnOff(LED_PIN17);
      TurnOff(LED_PIN21);

      TurnOn(LED_PIN4);
      TurnOn(LED_PIN8);
      TurnOn(LED_PIN12);
      TurnOn(LED_PIN16);
      TurnOn(LED_PIN20);
    };
    if (ledTime >= timeInterval * 5 && ledTime < timeInterval * 6) {
      brightness = 180;
      color = strip.Color(0, 200, 155);
      TurnOff(LED_PIN4);
      TurnOff(LED_PIN8);
      TurnOff(LED_PIN12);
      TurnOff(LED_PIN16);
      TurnOff(LED_PIN20);

      TurnOn(LED_PIN1);
      TurnOn(LED_PIN3);
      TurnOn(LED_PIN7);
      TurnOn(LED_PIN11);
    };
    if (ledTime >= timeInterval * 6 && ledTime < timeInterval * 7) {
      brightness = 165;
      color = strip.Color(0, 240, 135);
      TurnOff(LED_PIN1);
      TurnOff(LED_PIN3);
      TurnOff(LED_PIN7);
      TurnOff(LED_PIN11);

      TurnOn(LED_PIN2);
    };
    if (ledTime >= timeInterval * 7) {
      TurnOff(LED_PIN2);

      ledTime -= timeInterval * 7;
      counter++;
    }
  }
}


// function      -------- DirectionRipple6 --------

void DirectionRipple6(long elapsedTime) {
  static long ledTime = 0;
  ledTime += elapsedTime;

  if (ledTime <= timeInterval) {
    brightness = 255;
    color = strip.Color(0, 0, 255);
    TurnOn(LED_PIN25);
  };
  if (ledTime >= timeInterval && ledTime < timeInterval * 2) {
    brightness = 240;
    color = strip.Color(0, 40, 235);
    TurnOff(LED_PIN25);

    TurnOn(LED_PIN20);
    TurnOn(LED_PIN21);
    TurnOn(LED_PIN22);
    TurnOn(LED_PIN23);
    TurnOn(LED_PIN24);
  };
  if (ledTime >= timeInterval * 2 && ledTime < timeInterval * 3) {
    brightness = 225;
    color = strip.Color(0, 80, 215);
    TurnOff(LED_PIN20);
    TurnOff(LED_PIN21);
    TurnOff(LED_PIN22);
    TurnOff(LED_PIN23);
    TurnOff(LED_PIN24);

    TurnOn(LED_PIN16);
    TurnOn(LED_PIN17);
    TurnOn(LED_PIN18);
    TurnOn(LED_PIN19);
  };
  if (ledTime >= timeInterval * 3 && ledTime < timeInterval * 4) {
    brightness = 210;
    color = strip.Color(0, 120, 195);
    TurnOff(LED_PIN16);
    TurnOff(LED_PIN17);
    TurnOff(LED_PIN18);
    TurnOff(LED_PIN19);

    TurnOn(LED_PIN11);
    TurnOn(LED_PIN12);
    TurnOn(LED_PIN13);
    TurnOn(LED_PIN14);
    TurnOn(LED_PIN15);
  };
  if (ledTime >= timeInterval * 4 && ledTime < timeInterval * 5) {
    brightness = 195;
    color = strip.Color(0, 160, 175);
    TurnOff(LED_PIN11);
    TurnOff(LED_PIN12);
    TurnOff(LED_PIN13);
    TurnOff(LED_PIN14);
    TurnOff(LED_PIN15);

    TurnOn(LED_PIN7);
    TurnOn(LED_PIN8);
    TurnOn(LED_PIN9);
    TurnOn(LED_PIN10);
  };
  if (ledTime >= timeInterval * 5 && ledTime < timeInterval * 6) {
    brightness = 180;
    color = strip.Color(0, 200, 155);
    TurnOff(LED_PIN7);
    TurnOff(LED_PIN8);
    TurnOff(LED_PIN9);
    TurnOff(LED_PIN10);

    TurnOn(LED_PIN2);
    TurnOn(LED_PIN3);
    TurnOn(LED_PIN4);
    TurnOn(LED_PIN5);
    TurnOn(LED_PIN6);
  };
  if (ledTime >= timeInterval * 6 && ledTime < timeInterval * 7) {
    brightness = 165;
    color = strip.Color(0, 240, 135);
    TurnOff(LED_PIN2);
    TurnOff(LED_PIN3);
    TurnOff(LED_PIN4);
    TurnOff(LED_PIN5);
    TurnOff(LED_PIN6);

    TurnOn(LED_PIN1);
  };
  if (ledTime >= timeInterval * 7) {
    TurnOff(LED_PIN1);
    ledTime -= timeInterval * 7;
  }
}



// function      -------- storymode --------

static unsigned long storymodeTime = 0;
// one cycle : 180s (180000ms)
// each sub-mode : 36s (36000ms)
void storymode(long elapsedTime) {

  //  static unsigned long storymodeTime = 0;
  storymodeTime += elapsedTime;

  if (storymodeTime < 36000) {  // 36000
    sky_storymode();

  } else if (storymodeTime < 47000) { //47000
    lightning_storymode();

  } else if (storymodeTime < 83000) { //83000
    rain_storymode();

  } else if (storymodeTime < 119000) {  //119000
    // sunshine
    sunshine_storymode();

  } else if (storymodeTime < 155000) {
    // rainbow
    rainbow_storymode();
  } else {
    storymodeTime = 0;
  }
  Serial.println("OUT : " + String(storymodeTime));

}

void sky_storymode() {
  //  Serial.println("SKY : " + String(storymodeTime));
  static boolean darken = true;
  static int skyIndex = 98;

  if (darken)
  {
    skyIndex -= 6;
    if (skyIndex <= 2) {
      darken = false;
    }
  } else {                 // lighten
    skyIndex += 6;
    if (skyIndex >= 254) {
      darken = true;
    }
  }
  setAllTubes(strip.Color(0, skyIndex, 255));
}

void lightning_storymode() {
  Serial.println("LIGHTNING : " + String(storymodeTime));
  // thunder/lightning (11s)

  if (storymodeTime > 37000 && storymodeTime < 37300) {            // lightning
    setAllTubes(strip.Color(255, 255, 255));
  } else if (storymodeTime < 40000) {     // dark blue
    strip.setBrightness(210);
    setAllTubes(strip.Color(0, 32, 127));
  } else if (storymodeTime < 40300) {     // lightning
    strip.setBrightness(brightness);
    setAllTubes(strip.Color(255, 255, 255));
  } else if (storymodeTime < 41000) {     // dark blue
    strip.setBrightness(10);
    setAllTubes(strip.Color(16, 0, 63));
  } else if (storymodeTime < 41300) {     // lightning
    strip.setBrightness(brightness);
    setAllTubes(strip.Color(255, 255, 255));
  } else if (storymodeTime < 41600) {     // dark blue
    strip.setBrightness(10);
    setAllTubes(strip.Color(16, 0, 63));
  } else if (storymodeTime < 42000) {     // lightning
    strip.setBrightness(brightness);
    setAllTubes(strip.Color(255, 255, 255));
  } else {      // no color
    setAllTubes(strip.Color(0, 0, 0));
  }
}

void rain_storymode() {
  Serial.println("RAINNNNNN : " + String(storymodeTime));
  const int maxpixels = 30;

  // rain (36s)
  static int pixelCount = 1; // x1,x2 : rain ; x3 : not rain
  //  Serial.println("RAIN  pixelCount: " + String(pixelCount));

  for (int i = (maxpixels / 2) - 1; i >= 0; i--) {
    if ((i + pixelCount) % 4 == 0 || (i + pixelCount) % 4 == 1) {
      setAllTubes_odd(strip.Color(0, 0, 0));
      setAllTubes_pixel_odd(strip.Color(255, 255, 255), i);
      setAllTubes_pixel_odd(strip.Color(255, 255, 255), i + (maxpixels / 2));
    } else if ((i + pixelCount) % 4 == 2 || (i + pixelCount) % 4 == 4) {
      setAllTubes_even(strip.Color(0, 0, 0));
      setAllTubes_pixel_even(strip.Color(255, 255, 255), i);
      setAllTubes_pixel_even(strip.Color(255, 255, 255), i + (maxpixels / 2));
    }
  }
  // increment
  if (pixelCount == 4) {
    pixelCount = 1;
  } else {
    pixelCount++;
  }
}

void sunshine_storymode() {
  //  Serial.println("SUNSHINEEEEEEEE : " + String(storymodeTime));
  static boolean begining = true;
  static int loopCount = 1;
  int maxpixels = 30;

  // flow down
  if (begining == true) {
    for (int i = maxpixels ; i >= 0 ; i--) {
      setAllTubes_pixel(strip.Color(255, 204, 0), i);
    }
    begining = false;
  }

  static boolean darken = true;
  static int sunIndex = 254;

  if (darken) {
    sunIndex -= 3;         // darken
    if (sunIndex <= 204) {
      darken = false;
    }
  } else {                 // lighten
    sunIndex += 3;
    if (sunIndex >= 254) {
      darken = true;
    }
  }
  setAllTubes(strip.Color(255, sunIndex, 0));
  loopCount++;
}

void rainbow_storymode() {
  //Serial.println("RAINBOWWWWWWWWW : " + String(storymodeTime));
  static int colorCount = 1;

  if (colorCount / 8 == 1) {
    setRow1Tubes(strip.Color(255, 0, 0));
    setRow2Tubes(strip.Color(255, 64, 0));
    setRow3Tubes(strip.Color(255, 128, 0));
    setRow4Tubes(strip.Color(255, 255, 0));
    setRow5Tubes(strip.Color(0, 255, 0));
    setRow6Tubes(strip.Color(0, 64, 255));
    setRow7Tubes(strip.Color(64, 0, 255));
  } else if (colorCount / 8 == 2) {
    setRow1Tubes(strip.Color(64, 0, 255));
    setRow2Tubes(strip.Color(255, 0, 0));
    setRow3Tubes(strip.Color(255, 64, 0));
    setRow4Tubes(strip.Color(255, 128, 0));
    setRow5Tubes(strip.Color(255, 255, 0));
    setRow6Tubes(strip.Color(0, 255, 0));
    setRow7Tubes(strip.Color(0, 64, 255));
  } else if (colorCount / 8 == 3) {
    setRow1Tubes(strip.Color(0, 64, 255));
    setRow2Tubes(strip.Color(64, 0, 255));
    setRow3Tubes(strip.Color(255, 0, 0));
    setRow4Tubes(strip.Color(255, 64, 0));
    setRow5Tubes(strip.Color(255, 128, 0));
    setRow6Tubes(strip.Color(255, 255, 0));
    setRow7Tubes(strip.Color(0, 255, 0));
  } else if (colorCount / 8 == 4) {
    setRow1Tubes(strip.Color(0, 255, 0));
    setRow2Tubes(strip.Color(0, 64, 255));
    setRow3Tubes(strip.Color(64, 0, 255));
    setRow4Tubes(strip.Color(255, 0, 0));
    setRow5Tubes(strip.Color(255, 64, 0));
    setRow6Tubes(strip.Color(255, 128, 0));
    setRow7Tubes(strip.Color(255, 255, 0));
  } else if (colorCount / 8 == 5) {
    setRow1Tubes(strip.Color(255, 255, 0));
    setRow2Tubes(strip.Color(0, 255, 0));
    setRow3Tubes(strip.Color(0, 64, 255));
    setRow4Tubes(strip.Color(64, 0, 255));
    setRow5Tubes(strip.Color(255, 0, 0));
    setRow6Tubes(strip.Color(255, 64, 0));
    setRow7Tubes(strip.Color(255, 128, 0));
  } else if (colorCount / 8 == 6) {
    setRow1Tubes(strip.Color(255, 128, 0));
    setRow2Tubes(strip.Color(255, 255, 0));
    setRow3Tubes(strip.Color(0, 255, 0));
    setRow4Tubes(strip.Color(0, 64, 255));
    setRow5Tubes(strip.Color(64, 0, 255));
    setRow6Tubes(strip.Color(255, 0, 0));
    setRow7Tubes(strip.Color(255, 64, 0));
  } else if (colorCount / 8 == 7) {
    setRow1Tubes(strip.Color(255, 64, 0));
    setRow2Tubes(strip.Color(255, 128, 0));
    setRow3Tubes(strip.Color(255, 255, 0));
    setRow4Tubes(strip.Color(0, 255, 0));
    setRow5Tubes(strip.Color(0, 64, 255));
    setRow6Tubes(strip.Color(64, 0, 255));
    setRow7Tubes(strip.Color(255, 0, 0));
  }

  // increment
  if (colorCount == 56) {
    colorCount = 1;
  } else {
    colorCount++;
  }
}



// function      -------- Set Tube --------

void setRow1Tubes(uint32_t color) {
  strip.setPin(32);
  strip.fill(color);
  strip.show();
}

void setRow2Tubes(uint32_t color) {
  strip.setPin(41);
  strip.fill(color);
  strip.show();
  strip.setPin(36);
  strip.fill(color);
  strip.show();
  strip.setPin(31);
  strip.fill(color);
  strip.show();
  strip.setPin(27);
  strip.fill(color);
  strip.show();
}
void setRow3Tubes(uint32_t color) {
  strip.setPin(50);
  strip.fill(color);
  strip.show();
  strip.setPin(45);
  strip.fill(color);
  strip.show();
  strip.setPin(40);
  strip.fill(color);
  strip.show();
  strip.setPin(35);
  strip.fill(color);
  strip.show();
  strip.setPin(30);
  strip.fill(color);
  strip.show();
}

void setRow4Tubes(uint32_t color) {
  strip.setPin(49);
  strip.fill(color);
  strip.show();
  strip.setPin(44);
  strip.fill(color);
  strip.show();
  strip.setPin(39);
  strip.fill(color);
  strip.show();
  strip.setPin(22);
  strip.fill(color);
  strip.show();
  strip.setPin(29);
  strip.fill(color);
  strip.show();
}

void setRow5Tubes(uint32_t color) {
  strip.setPin(28);
  strip.fill(color);
  strip.show();
  strip.setPin(48);
  strip.fill(color);
  strip.show();
  strip.setPin(43);
  strip.fill(color);
  strip.show();
  strip.setPin(38);
  strip.fill(color);
  strip.show();
  strip.setPin(33);
  strip.fill(color);
  strip.show();
}

void setRow6Tubes(uint32_t color) {
  strip.setPin(51);
  strip.fill(color);
  strip.show();
  strip.setPin(47);
  strip.fill(color);
  strip.show();
  strip.setPin(42);
  strip.fill(color);
  strip.show();
  strip.setPin(37);
  strip.fill(color);
  strip.show();
}

void setRow7Tubes(uint32_t color) {
  strip.setPin(46);
  strip.fill(color);
  strip.show();
}

void setAllTubes_odd(uint32_t color) {
  for (int i = 27; i <= 51; i++) {
    if (i % 2 == 1) {
      strip.setPin(i);
      strip.fill(color);
    }
  }
}

void setAllTubes_even(uint32_t color) {
  for (int i = 27; i <= 51; i++) {
    if (i == 34) {
      strip.setPin(22);
      strip.fill(color);
      continue;
    }
    if (i % 2 == 1) {
      strip.setPin(i);
      strip.fill(color);
    }
  }
}

void setAllTubes(uint32_t color) {
  for (int i = 27; i <= 51; i++) {
    if (i == 34) {
      strip.setPin(22);
      strip.fill(color);
      strip.show();
      continue;
    }
    strip.setPin(i);
    strip.fill(color);
    strip.show();
  }

}

void setAllTubes_pixel(uint32_t color, long pixel) {
  for (int i = 27; i <= 51; i++) {
    if (i == 34) {
      strip.setPin(22);
      strip.setPixelColor(pixel, color);
      strip.show();
      continue;
    }
    strip.setPin(i);
    strip.setPixelColor(pixel, color);
    strip.show();
  }
}

void setAllTubes_pixel_odd(uint32_t color, long pixel) {
  for (int i = 27; i <= 51; i++) {
    if (i % 2 == 1) {
      strip.setPin(i);
      strip.setPixelColor(pixel, color);
      strip.show();
    }
  }
}

void setAllTubes_pixel_even(uint32_t color, long pixel) {
  for (int i = 27; i <= 51; i++) {
    if (i == 34) {
      strip.setPin(22);
      strip.setPixelColor(pixel, color);
      strip.show();
      continue;
    }
    if (i % 2 == 0) {
      strip.setPin(i);
      strip.setPixelColor(pixel, color);
      strip.show();
    }
  }
}

void setAllTubes_Beats(uint32_t color, long pixel) {
  for (int i = 27; i <= 51; i++) {
    if (i == 34) {
      strip.setPin(22);
      strip.setPixelColor(pixel, color);
      strip.show();
      continue;
    } else if (i == 39) {
      strip3.setPin(i);
      int pi = pixel + 8;
      strip3.setPixelColor(pi, color);
      Serial.println(pi);
      strip3.show();
      continue;
    } else {
      strip.setPin(i);
      Serial.println("i" + String(pixel));
      strip.setPixelColor(pixel, color);
      strip.show();
    }
  }
}






// function      -------- Rainbow --------

void rainbow(long elapsedTime) {
  static int i = 0;
  static int j = 0 ;
  static long RainbowTime = 0;
  RainbowTime += elapsedTime;

  if (RainbowTime >= 300) {
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
    Serial.println(String(i + j));
    strip.show();

    RainbowTime -= 300;
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
