#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

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
                1, 20978, 21673, 22469, 22854, 23221, 23978, 24659, 25475,
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

long test[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};

int LED_COUNT = 60;
unsigned long lastTime = 0;
int brightness = 200;
int ledPinMin = 27;
int ledPinMax = 51;
int duration = 1000;

Adafruit_NeoPixel strip(LED_COUNT, ledPinMin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(brightness);
  Serial.begin(9600);
  Serial.println("SETUP");
}

void loop() {
  // put your main code here, to run repeatedly:
  long elapsedTime = millis() - lastTime;
  lastTime = lastTime + elapsedTime;

  raise(elapsedTime, test);
}

////////////////////////////
//  | 3 | 4 | 5 |   |   |
//    ^           ^
//    |           |
//  popNum      pushNum
////////////////////////////
void raise(long elapsedTime, long beat[]) {
  static long ledsTime[25]; //Keep track of all the LED times
  static long queue[25]; //Queue to keep track of what tube is still doing patterns
  static int popNum = 0; //Variable to deal with Queue implementation
  static int pushNum = 0; //Variable to deal with Queue implementation
  static int beatCounter = 0; //Track which beat is it on
  static long functionTime = 0; //Track how long this function has been running

  functionTime = functionTime + elapsedTime;


  if (functionTime > beat[beatCounter]) {
    Serial.println("Inside functiontime to get beats");
    queue[pushNum] = 0;

    //Managing random number
    int randNumber = random(ledPinMin, ledPinMax); //Choose random tube to light up

    //Checking for duplicate rand num

    if (pushNum == popNum) {
      Serial.println("here");
    } else if (pushNum > popNum) { //Handle normal case
      for (int j = popNum; j < pushNum; j++) {
        if (queue[j] == randNumber) {
          randNumber = random(ledPinMin, ledPinMax);
          j = 0;
        }
      }
    } else if (pushNum < popNum) { //Handle Circular Buffer situation
      for (int j = popNum; j <= 25; j++) {
        if (queue[j] == randNumber) {
          randNumber = random(ledPinMin, ledPinMax);
          j = 0;
        }
      }
      for (int j = 0; j < pushNum; j++) {
        if (queue[j] == randNumber) {
          randNumber = random(ledPinMin, ledPinMax);
          j = 0;
        }
      }
    }



    //Pushing Random number to queue
    Serial.println("Tube Number: " + String(pushNum));
    Serial.println("Random Number: " + String(randNumber));
    queue[pushNum] = randNumber;  //Add the tube number to queue to keep track
    strip.setPin(randNumber);
    strip.fill(strip.Color(255, 255, 255));
    //    strip.setBrightness(200);
    //    strip.show();

    // --- brightness zero ---
    strip.setBrightness(0);
    strip.show();

    //Update push variable
    if (pushNum == 25) {
      pushNum = 0;
    } else {
      pushNum++;
    }
    //Update beats variable
    beatCounter++;
  } else if (pushNum == popNum) { //When theres no tube running pattern, end function
    return;
  }


  //Else, manage tube still in pattern
  if (pushNum > popNum) { //Handle normal case
    //    Serial.println("  HELOOOOOOOOOOOOOOOOOOOOOOOO  ");
    for (int j = popNum; j < pushNum; j++) {
      int tube = queue[j];
      //      Serial.println("light, tube :" + String(tube));
      strip.setPin(tube);
      ledsTime[tube] += elapsedTime;
      int tubeTime = ledsTime[tube];
      if (tubeTime > duration) { //if the tube exceeded 1000ms(the duration)
        ledsTime[tube] = 0;
        strip.clear();
        strip.show();
        if (popNum == 25) { //Update pop variable (due to circular)
          popNum = 0;
        } else {
          popNum++;
        }
      } else {  //else, change brightness of tube in pattern
        // --- added colour + change to int ---
        strip.fill(strip.Color(0, 0, 255));
        strip.setBrightness(int((double(tubeTime) / duration) * 255));
        Serial.println("brightness :" + String((double(tubeTime) / duration) * 255));
        strip.show();
      }
    }
  } else if (pushNum < popNum) { //Handle Circular Buffer situation
    for (int j = popNum; j <= 25; j++) {
      int tube = queue[j];
      strip.setPin(tube);
      ledsTime[tube] += elapsedTime;
      int tubeTime = ledsTime[tube];
      if (tubeTime > duration) { //if the tube exceeded 1000ms(the duration)
        ledsTime[tube] = 0;
        strip.clear();
        strip.show();
        if (popNum == 25) { //Update pop variable (due to circular)
          popNum = 0;
        } else {
          popNum++;
        }
      } else {  //else, change brightness of tube in pattern
        // --- added colour + change to int ---
        strip.fill(strip.Color(0, 0, 255));
        strip.setBrightness(int((double(tubeTime) / duration) * 255));
        strip.show();
      }
    }

    for (int j = 0; j < pushNum; j++) {
      int tube = queue[j];
      strip.setPin(tube);
      ledsTime[tube] += elapsedTime;
      int tubeTime = ledsTime[tube];
      if (tubeTime > duration) { //if the tube exceeded 1000ms(the duration)
        ledsTime[tube] = 0;
        strip.clear();
        strip.show();
        if (popNum == 25) { //Update pop variable (due to circular)
          popNum = 0;
        } else {
          popNum++;
        }
      } else {  //else, change brightness of tube in pattern
        // --- added colour + change to int ---
        strip.fill(strip.Color(0, 0, 255));
        strip.setBrightness(int((double(tubeTime) / duration) * 255));
        strip.show();
      }
    }
  }

}
