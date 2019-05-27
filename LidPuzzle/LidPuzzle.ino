/**********************************************************************
 * PINS
 **********************************************************************/
int pins[4] = {2,3,4,5};
#define outputDevice 13
#define wrongSound 10
#define inputSound 11
#define correctSound 12

/**********************************************************************
 * GLOBALS
 * correct - correct sequence of presses
 * pressed - pressed sequence
 * counter - keeps track of index for pressed
 **********************************************************************/
int correct[4] = {5,3,2,4}; 
int pressed[4] = {0,0,0,0};
int counter = 0;
#define SOUND_DELAY 200

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
 * Returns true if the pressed and correct arrays are equal
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
 * Infinite loop until all 4 touch sensors are held
 **********************************************************************/
void resetSequence() {
  while(true) {
    int resetCount = 0;
    
    for (int i=0; i<4; i++) {
        if (digitalRead(pins[i])) {
          resetCount++;
          playSound(inputSound);
        }
    }
    if (resetCount == 4) break;
  }
}

/**********************************************************************
 * SETUP
 * Set up the pins and initial values
 **********************************************************************/
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], INPUT);
  }
  
  pinMode(outputDevice, OUTPUT);
  digitalWrite(outputDevice, HIGH);
  
  pinMode(wrongSound, OUTPUT);
  digitalWrite(wrongSound, HIGH);
  
  pinMode(inputSound, OUTPUT);
  digitalWrite(inputSound, HIGH);
  
  pinMode(correctSound, OUTPUT);
  digitalWrite(correctSound, HIGH);

}

void debug() {
  for (int i = 0; i < 4; i++) {
    Serial.println(digitalRead(pins[i]));
  }
  Serial.println("**************************************");
}

/**********************************************************************
 * LOOP
 * General game loop
 **********************************************************************/
void loop() {
  for (int i=0; i < 4; i++) {
    if (digitalRead(pins[i])) {
      pressed[counter] = pins[i];
      counter++;
      playSound(inputSound);
    }
  }
  // If we've gotten 4 inputs, check the win state
  if (counter == 4) {
    if (checkWin()) {
      digitalWrite(outputDevice, LOW);
      playSound(correctSound);
      counter = 0; 
      resetSequence();
      digitalWrite(outputDevice, HIGH);
    }
    else {
      playSound(wrongSound);
      counter = 0;
    }
  }
}
