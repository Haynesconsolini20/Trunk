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
    if (digitalRead(pins[0]) && digitalRead(pins[2])) {
      break;
    }
    if (digitalRead(pins[1]) && digitalRead(pins[3])) {
      reprogramButtons();
    }
  }
}

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
