//Touch pins
int pins[4] = {5,6,7,8};
int correct[4] = {5,6,7,8}; 
int pressed[4] = {0,0,0,0};

//Output device
#define outputDevice 9
int counter = 0;
#define wrongSound 10
#define inputSound 11
#define correctSound 12


void playSound(int soundPin) {
  digitalWrite(soundPin, HIGH);
  delay(200);
  digitalWrite(soundPin, LOW);
}
bool checkWin() {
  for (int i = 0; i < 4; i++) {
    if (correct[i] != pressed[i]) {
      return false;
    }
  }
  return true;
}

void resetSequence() {
  while(true) {
    bool finished = true;
    for (int i = 0; i < 4; i++) {
      if (!digitalRead(pins[i])) {
        finished = false;
      }
    }
    if (finished) break;
  }
}

void setup() {
  // Setup touch pins
  for (int i=0; i < 4; i++) {
    pinMode(pins[i], INPUT);
  }

  // Setup output pin
  pinMode(outputDevice, OUTPUT);
  pinMode(wrongSound, OUTPUT);
  pinMode(inputSound, OUTPUT);
  pinMode(correctSound, OUTPUT);

}

void loop() {
  int resetCount = 0;
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
      playSound(correctSound);
      counter = 0; 
      resetSequence();
    }
    else {
      playSound(wrongSound);
      counter = 0;
    }
  }

  
  

}
