//DICE
#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
#define NUM_LEDS_PER_STRIP 144
#define NUM_STRIPS 8
#define num_worms NUM_LEDS_PER_STRIP/7
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
int myworms[num_worms][2];
int fadeconstant = 50;

void setup() {
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);

  for (int i = 0; i < num_worms; i++) {
    myworms[i][0] = random8(NUM_STRIPS * NUM_LEDS_PER_STRIP);
    myworms[i][1] = 0;
  }
}
int t = 0;

void loop() {
  for (int j = 0; j < NUM_STRIPS * NUM_LEDS_PER_STRIP; j++) {

    //colors
    for (int i = 0; i < num_worms; i++)
      leds[myworms[i][0]] = CHSV(((0.3 * i) + 1) * t/10, 255, 255);

    //Movement
    for (int i = 0; i < num_worms; i++) {
      if (myworms[i][1] == 0) {
        myworms[i][1] = random(-NUM_STRIPS * NUM_LEDS_PER_STRIP / 2, NUM_STRIPS * NUM_LEDS_PER_STRIP / 2);
      }
      if (myworms[i][1] > 0) {
        myworms[i][0] += 1;
        myworms[i][1] -= 1;
      }
      if (myworms[i][1] < 0) {
        myworms[i][0] -= 1;
        myworms[i][1] += 1;
      }
      if (myworms[i][0] == NUM_STRIPS * NUM_LEDS_PER_STRIP) {
        myworms[i][0] = 1;
      }
      if (myworms[i][0] == 0) {
        myworms[i][0] = NUM_STRIPS * NUM_LEDS_PER_STRIP - 1;
      }
    }



  

  //Fade
  for (int i = 0; i < NUM_STRIPS * NUM_LEDS_PER_STRIP; i++)
  {
    leds[i] -= CHSV(0, 0, fadeconstant) ;
  }


t += 1;


FastLED.show();
//delay(1);
  }
}

