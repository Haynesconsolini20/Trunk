
unsigned long startTimes[4] = {0,0,0,0};
unsigned long elapsed_time[4] = {0,0,0,0};
int pins[4] = {1,2,3,4};
int sounds[4] = {5,6,7,8};


void swapSounds(int pin1, int pin2) {
  return;
}

void playSound(int soundPin) {
  digitalWrite(soundPin, LOW);
  delay(200);
  digitalWrite(soundPin, HIGH);
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {

  //Read pins, record time elapsed and play sound if button is released
  for (int i = 0; i < 4; i++) {
    if (digitalRead(pins[i] && startTimes[i] > 0)
      elapsed_time[i] = millis() - startTimes[index];
    else if (digitalRead(pins[i]) && startTimes[i] == 0)
      startTimes[index] = millis();
    else if (!digitalRead(pins[i]) && startTime[i] > 0) {
      playSound(sounds[i]);
      elapsed_time[i] = 0;
      startTimes[i] = 0;
    }
  }

  int hold1, hold2, holdCount = 0;
  for (int i = 0; i < 4; i++) {
    if (elapsed_time[i] > 2000) {
      heldCount ? hold1 = pins[i] : hold2 = pins[i];
      heldCount++;
    }
  }

  if (heldCount == 2) 
    swapSounds(hold1, hold2);
  else if (heldCount > 2)
    playSound(wrongSound);

  if (digitalRead(submitButton) AND checkWin()) {
    play(winSound);
    digitalWrite(outputDevice, LOW);
    resetSequence();
  }

}
