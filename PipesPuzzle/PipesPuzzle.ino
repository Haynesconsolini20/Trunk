#include <Adafruit_NeoPixel.h>

/**********************************************************************
 * PINS
 **********************************************************************/
//Neopixel pipes
#define pipe_1    3
#define pipe_2    4
#define pipe_3    5
//Sounds
#define inputSound 11
#define winSound 13
//Neopixel baskets
#define basket_1  6
#define basket_2  7
#define basket_3  8
//Photodiodes
#define b1_receiver 10
#define b2_receiver 12
#define b3_receiver 14

/**********************************************************************
 * NEOPIXEL SETUP
 **********************************************************************/
//Pixel counts
#define pipe_counts 5
#define basket_counts 12
//Pipe setup
Adafruit_NeoPixel pipe_1_strip(pipe_counts, pipe_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pipe_2_strip(pipe_counts, pipe_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pipe_3_strip(pipe_counts, pipe_3, NEO_GRB + NEO_KHZ800);
//Basket setup
Adafruit_NeoPixel basket_1_strip(basket_counts, basket_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel basket_2_strip(basket_counts, basket_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel basket_3_strip(basket_counts, basket_3, NEO_GRB + NEO_KHZ800);

/**********************************************************************
 * GLOBALS
 * red,green,blue - colors to simplify neopixel code
 * SOUND_DELAY - duration to play sounds in milliseconds
 **********************************************************************/
uint32_t red = pipe_1_strip.Color(255, 0, 0);
uint32_t green = pipe_1_strip.Color(0, 255, 0);
uint32_t blue = pipe_1_strip.Color(0, 0, 255);
#define SOUND_DELAY 200

/**********************************************************************
 * PLAY SOUND
 * Plays a sound for SOUND_DELAY milliseconds
 **********************************************************************/ 
void playSound(int soundPin) {
  digitalWrite(soundPin, HIGH);
  delay(SOUND_DELAY);
  digitalWrite(soundPin, LOW);
}

/**********************************************************************
 * RESET SEQUENCE
 * Loops until two marbles are put down the second pipe, then
 * resets the colors to the initial values
 **********************************************************************/
void resetSequence() {
  int resetCount = 0;
  while (resetCount < 2) {
    if (!digitalRead(b2_receiver)) {
      resetCount++;
    }
  }
  initialColors(); 
}

/**********************************************************************
 * INITIAL COLORS
 * Sets the pipes and baskets to their initial state
 **********************************************************************/
void initialColors() {
    pipe_1_strip.fill(red);
    pipe_1_strip.show(); 
    
    pipe_2_strip.fill(green);
    pipe_2_strip.show(); 
    
    pipe_3_strip.fill(blue);
    pipe_3_strip.show(); 

    basket_1_strip.fill(blue);
    basket_1_strip.show(); 
    
    basket_1_strip.fill(green);
    basket_2_strip.show(); 
    
    basket_3_strip.fill(red);
    basket_3_strip.show(); 
}

/**********************************************************************
 * CHECK WIN
 * Returns true if each pipe/basket pair is the same color
 **********************************************************************/
bool checkWin() {
  if (pipe_1_strip.getPixelColor(1) != basket_1_strip.getPixelColor(1)) {
    return false;
  }
  if (pipe_2_strip.getPixelColor(1) != basket_2_strip.getPixelColor(1)) {
    return false;
  }
  if (pipe_3_strip.getPixelColor(1) != basket_3_strip.getPixelColor(1)) {
    return false;
  }
  return true;
}

/**********************************************************************
 * ROTATE BASKETS
 * Rotates the colors of the baskets to the "left"(3->2->->1->3)
 **********************************************************************/
void rotateBaskets() {
  uint32_t color_a = basket_1_strip.getPixelColor(1);
  basket_1_strip.fill(basket_2_strip.getPixelColor(1));
  basket_2_strip.fill(basket_3_strip.getPixelColor(1));
  basket_3_strip.fill(color_a);

  basket_1_strip.show();
  basket_2_strip.show();
  basket_3_strip.show();
}

/**********************************************************************
 * SWAP PIPES
 * Swaps the colors of two pipes
 **********************************************************************/
void swapPipes(Adafruit_NeoPixel pipe_a, Adafruit_NeoPixel pipe_b) {
      uint32_t color_a = pipe_a.getPixelColor(1);
      pipe_a.fill(pipe_b.getPixelColor(1));
      pipe_b.fill(color_a);

      pipe_a.show();
      pipe_b.show();
}

/**********************************************************************
 * SETUP
 * Begin and clear all neopixels, then initialize the colors
 * Initialize all pins and initial states
 **********************************************************************/
void setup() {
    pipe_1_strip.begin();
    pipe_1_strip.show();
    pipe_2_strip.begin();
    pipe_2_strip.show();
    pipe_3_strip.begin();
    pipe_3_strip.show();
    
    basket_1_strip.begin();
    basket_2_strip.begin();
    basket_3_strip.begin();

    initialColors();
    
    pinMode(b1_receiver, INPUT);
    pinMode(b2_receiver, INPUT);
    pinMode(b3_receiver, INPUT);

    pinMode(inputSound, OUTPUT);
    digitalWrite(inputSound, LOW);
    
    pinMode(winSound, OUTPUT);  
    digitalWrite(winSound, LOW);
}

/**********************************************************************
 * LOOP 
 * General game loop
 **********************************************************************/
void loop() {
  if (digitalRead(b1_receiver)) {
    playSound(inputSound);
    swapPipes(pipe_1_strip,pipe_2_strip);
  }
  if (digitalRead(b2_receiver)) {
    playSound(inputSound);
    swapPipes(pipe_1_strip,pipe_3_strip);
    rotateBaskets();
  }
  if (digitalRead(b3_receiver)) {
    playSound(inputSound);
    swapPipes(pipe_2_strip,pipe_3_strip);
  }
  if (checkWin()) {
    playSound(winSound);
    resetSequence();
  }

}
