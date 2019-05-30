#include <EEPROM.h>

/**********************************************************************
 * PINS
 **********************************************************************/
int pins[4] = {2,3,4,5};
#define wrongSound 10
#define inputSound 11
#define correctSound 12

/**********************************************************************
 * GLOBALS
 * correct - the correct sequence of buttons
 * pressed - the sequence pressed by the user
 * counter - keeps track of which index to write in the pressed array
 * SOUND_DELAY - milliseconds that sounds are played
 **********************************************************************/
int correct[4] = {2,3,4,5}; 
int pressed[4] = {0,0,0,0};
int counter = 0;
#define SOUND_DELAY 200

/**********************************************************************
 * REPROGRAM BUTTONS
 * Waits for a 4 button sequence that becomes the new correct sequence,
 * the win sound plays as confirmation
 **********************************************************************/
void reprogramButtons() {
  Serial.println("Reprogramming...");
  delay(500);
  int count = 0;
  while (count < 4) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(pins[i])) {
        correct[count] = pins[i];
        playSound(inputSound);
        count++;
        Serial.println("New index recorded");
      }
    }
  }
  Serial.println("Recording in memory");
  EEPROM.put(0, correct);
  Serial.println("Finished Reprogramming");
  playSound(correctSound);
}

/**********************************************************************
 * PLAY SOUND
 * Plays a sound for SOUND_DELAY milliseconds
 **********************************************************************/
void playSound(int soundPin) {
  digitalWrite(soundPin, LOW);
  delay(SOUND_DELAY);
  digitalWrite(soundPin, HIGH);
}

/**********************************************************************
 * CHECK WIN
 * Returns true if the correct and pressed arrays are equal
 **********************************************************************/
bool checkWin() {
  for (int i = 0; i < 4; i++) {
    Serial.print("Checking ");
    Serial.print(pressed[i]);
    Serial.print(" against ");
    Serial.println(correct[i]);
    if (correct[i] != pressed[i]) {
      return false;
    }
  }
  return true;
}

/**********************************************************************
 * RESET SEQUENCE
 * If buttons 1 & 3 are held, the game resets
 * If buttons 2 & 4 are held, the reprogram sequence begins
 **********************************************************************/
void resetSequence() {
  while(true) {
    if (digitalRead(pins[0]) && digitalRead(pins[2])) {
      break;
    }
    if (digitalRead(pins[1]) && digitalRead(pins[3])) {
      reprogramButtons();
      break;
    }
  }
}

/**********************************************************************
 * READ MEMORY
 * Reads byte 0 in arduino EEPROM, which is where any previous custom
 * sequence was stored. If a custom sequence is detected, it writes
 * that to the correct sequence.
 **********************************************************************/
void readMemory() {
  //Read sequence from memory 
  int seq[4];
  Serial.println("Checking memory for sequence");
  EEPROM.get(0, seq);
  Serial.println("Memory sequence:");
  for (int i = 0; i < 4; i++) {
    Serial.print(seq[i]);
  }
  Serial.println();
  Serial.println("********************");
  if (seq[0] != -1) {
    for (int i = 0; i < 4; i++) {
      correct[i] = seq[i];
    }
  }
}

/**********************************************************************
 * SETUP
 * Initialize pins and initial states
 **********************************************************************/
void setup() {
  Serial.begin(9600);
  readMemory();
  // Setup touch pins
  for (int i=0; i < 4; i++) {
    pinMode(pins[i], INPUT);
  }
  
  
  pinMode(wrongSound, OUTPUT);
  digitalWrite(wrongSound, HIGH);
  
  pinMode(inputSound, OUTPUT);
  digitalWrite(inputSound, HIGH);
  
  pinMode(correctSound, OUTPUT);
  digitalWrite(correctSound, HIGH);
}

/**********************************************************************
 * LOOP 
 * General game loop
 **********************************************************************/
void loop() {
  //Loop through the 4 inputs
  for (int i = 0; i < 4; i++) {
    if (digitalRead(pins[i]) == HIGH) {
      playSound(inputSound);
      pressed[counter] = pins[i];
      counter++;
      Serial.println("Button Pressed");
    }
  }
  // If we've sequenced n times, we're done
  if (counter == 4) {
    if (checkWin()) {
      Serial.println("Correct sequence, win!");
      playSound(correctSound);
      counter = 0; 
      resetSequence();
      Serial.println("Reset finished");
      delay(500);
    }
    else {
      Serial.println("Incorrect sequence, try again");
      playSound(wrongSound);
      counter = 0;
    }
  }
}
