/**********************************************************************
 * PINS
 **********************************************************************/
int pins[4] = {5,6,7,8};
#define outputDevice 9
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
int correct[4] = {5,6,7,8}; 
int pressed[4] = {0,0,0,0};
int counter = 0;
#define SOUND_DELAY 200

/**********************************************************************
 * REPROGRAM BUTTONS
 * Waits for a 4 button sequence that becomes the new correct sequence,
 * the win sound plays as confirmation
 **********************************************************************/
void reprogramButtons() {
  int count = 0;
  while (count < 4) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(pins[i])) {
        correct[count] = pins[i];
        playSound(inputSound);
        count++;
      }
    }
  }
  playSound(correctSound);
}

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
 * CHECK WIN
 * Returns true if the correct and pressed arrays are equal
 **********************************************************************/
bool checkWin() {
  for (int i = 0; i < 4; i++) {
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
    }
  }
}

/**********************************************************************
 * SETUP
 * Initialize pins and initial states
 **********************************************************************/
void setup() {
  // Setup touch pins
  for (int i=0; i < 4; i++) {
    pinMode(pins[i], INPUT);
  }

  // Setup output pin
  pinMode(outputDevice, OUTPUT);
  digitalWrite(outputDevice, LOW);
  
  pinMode(wrongSound, OUTPUT);
  digitalWrite(wrongSound, LOW);
  
  pinMode(inputSound, OUTPUT);
  digitalWrite(inputSound, LOW);
  
  pinMode(correctSound, OUTPUT);
  digitalWrite(correctSound, LOW);
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
      pressed[counter] == pins[i];
      counter++;
    }
  }
  // If we've sequenced n times, we're done
  if (counter == 4) {
    if (checkWin()) {
      digitalWrite(outputDevice, HIGH);
      playSound(correctSound);
      counter = 0; 
      resetSequence();
      digitalWrite(outputDevice, LOW);
    }
    else {
      playSound(wrongSound);
      counter = 0;
    }
  }
}
