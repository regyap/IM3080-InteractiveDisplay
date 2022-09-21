#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

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


#define LED_COUNT 7

#define BUTTON_PIN 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);

int brightness = 50;;
int wait = 1000;
int buttonState = 0;

//For multithreading
long lastTime = millis();

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(brightness);
  pinMode(BUTTON_PIN, INPUT);
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

void loop() {
  // put your main code here, to run repeatedly:
  long elapsedTime = millis() - lastTime; //get time elapsed
  lastTime += elapsedTime;

  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    CenterRipple(elapsedTime);
  }else{
    strip.clear();
    strip.show();
  }
}
