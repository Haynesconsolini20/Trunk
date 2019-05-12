/*
 * Press button to check inputs
 * Press button after all switches are high to reset
 * Hold button for 2 seconds, switch to desired config, then hold again to reprogram
 */


//Touch pins
int pins[9] = {3,4,5,6,7,8,9,10,11};
int correct[9] = {1,1,1,1,1,1,1,1,1};

//Output device
#define outputDevice 12
int counter = 0;
#define wrongSound 13
#define inputSound 14
#define correctSound 15
#define confirmInputs 16


bool checkInputs() {
  for (int i = 0; i < 9; i++) {
    if (digitalRead(pins[i]) != correct[i]) {
      return false;
    }
  }
  return true;
}
void reprogramSwitches() {
  playSound(correctSound);
  while (true) {
    if (digitalRead(confirmInputs)) {
      delay(2000);
      if (digitalRead(confirmInputs)) {
        for (int i = 0; i < 9; i++) {
          correct[i] = digitalRead(pins[i]);
        }
      }
      break;
    }
  }
  playSound(correctSound);
}

void playSound(int soundPin) {
  digitalWrite(soundPin, HIGH);
  delay(200);
  digitalWrite(soundPin, LOW);
}

bool checkWin() {
  for (int i = 0; i < 9; i++) {
    if (correct[i] != pressed[i]) {
      return false;
    }
  }
  return true;
}

void resetSequence() {
  while(true) {
    bool reset = true;
    //Check for reset break
    for (int i = 0; i < 9; i++) {
      if (digitalRead(pins[i]) != 1) {
        reset = false;
      }
    }
    if (reset) {
      break;
    }
    //Check for reprogram
    if (digitalRead(confirmInputs)) {
      delay(2000);
      if (digitalRead(confirmInputs)) {
        reprogramSwitches();
      }
    }
    
  }
}

void setup() {
  for (int i=0; i < 9; i++) {
    pinMode(pins[i], INPUT);
  }

  pinMode(confirmInputs, INPUT);
  
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

void loop() {
  //Loop through the 4 inputs
  if (digitalRead(confirmInputs)) {
    if (checkWin()) {
      playSound(correctSound);
      digitalWrite(outputDevice, HIGH);
      resetSequence();
      digitalWrite(outputDevice, LOW);
    }
    else {
      playSound(wrongSound);
    }
  }
  

  
  

}
