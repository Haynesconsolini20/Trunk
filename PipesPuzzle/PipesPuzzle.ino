#include <Adafruit_NeoPixel.h>

    // Which pin on the Arduino is connected to the NeoPixels?
    // On a Trinket or Gemma we suggest changing this to 1:
    #define pipe_1    3
    #define pipe_2    4
    #define pipe_3    5

    #define inputSound 11
    #define winSound 13

    #define basket_1  6
    #define basket_2  7
    #define basket_3  8

    #define b1_receiver 10

    #define b2_receiver 12

    #define b3_receiver 14

    // How many NeoPixels are attached to the Arduino?
    #define pipe_counts 5
    #define basket_counts 12

    
     
    // Declare pipes
    Adafruit_NeoPixel pipe_1_strip(pipe_counts, pipe_1, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel pipe_2_strip(pipe_counts, pipe_2, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel pipe_3_strip(pipe_counts, pipe_3, NEO_GRB + NEO_KHZ800);

    //Declare baskets
    Adafruit_NeoPixel basket_1_strip(basket_counts, basket_1, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel basket_2_strip(basket_counts, basket_2, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel basket_3_strip(basket_counts, basket_3, NEO_GRB + NEO_KHZ800);

    uint32_t red = pipe_1_strip.Color(255, 0, 0);
    uint32_t green = pipe_1_strip.Color(0, 255, 0);
    uint32_t blue = pipe_1_strip.Color(0, 0, 255);

    
void playSound(int soundPin) {
  digitalWrite(soundPin, HIGH);
  delay(200);
  digitalWrite(soundPin, LOW);
}
void resetSequence() {
  int resetCount = 0;
  while (resetCount < 2) {
    if (!digitalRead(b2_receiver)) {
      resetCount++;
    }
  }
  initialColors(); 
}

void initialColors() {
    pipe_1_strip.fill(red);
    pipe_1_strip.show(); 
    
    pipe_2_strip.fill(green);
    pipe_2_strip.show(); 
    
    pipe_3_strip.fill(blue);
    pipe_3_strip.show(); 

    delay(5000);

    basket_1_strip.fill(blue);
    basket_1_strip.show(); 
    
    basket_1_strip.fill(green);
    basket_2_strip.show(); 
    
    basket_3_strip.fill(red);
    basket_3_strip.show(); 
}

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

void rotateBaskets() {
  uint32_t color_a = basket_1_strip.getPixelColor(1);
  basket_1_strip.fill(basket_2_strip.getPixelColor(1));
  basket_2_strip.fill(basket_3_strip.getPixelColor(1));
  basket_3_strip.fill(color_a);

  basket_1_strip.show();
  basket_2_strip.show();
  basket_3_strip.show();
}

void swapPipes(Adafruit_NeoPixel pipe_a, Adafruit_NeoPixel pipe_b) {
      uint32_t color_a = pipe_a.getPixelColor(1);
      pipe_a.fill(pipe_b.getPixelColor(1));
      pipe_b.fill(color_a);

      pipe_a.show();
      pipe_b.show();
}
   
void setup() {
    pipe_1_strip.begin();
    pipe_1_strip.show();
    pipe_2_strip.begin();
    pipe_2_strip.show();
    pipe_3_strip.begin();
    pipe_3_strip.show();
    
    /*basket_1_strip.begin();
    basket_2_strip.begin();
    basket_3_strip.begin(); */

    initialColors();
    

    /*pinMode(b1_receiver, INPUT);
    pinMode(b2_receiver, INPUT);
    pinMode(b3_receiver, INPUT);

    pinMode(inputSound, OUTPUT);
    pinMode(winSound, OUTPUT);*/
    

    
}

void loop() {
  /*if (digitalRead(b1_receiver)) {
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
  }*/

}
