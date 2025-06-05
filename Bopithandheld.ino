#include <Adafruit_CircuitPlayground.h>

enum GameState { START, BOP_IT, SWITCH_IT, YELL_AT_IT, SHROUD_IT, SUCCESS, FAIL };
GameState gameState = START;

unsigned long roundDelay = 5000;  // 5 seconds per challenge
unsigned long delayBetweenRounds = 1000;  // 1-second delay between rounds
unsigned long lastMillis = 0;
int level = 1;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  randomSeed(analogRead(0));
  Serial.println("Start Game");
}

void loop() {
  switch (gameState) {
    case START:
      delay(delayBetweenRounds); // Add delay before the next challenge
      gameState = generateCommand();
      break;
    case BOP_IT:
      if (waitForButton()) { gameState = SUCCESS; } else { gameState = FAIL; }
      break;
    case SWITCH_IT:
      if (waitForSwitch()) { gameState = SUCCESS; } else { gameState = FAIL; }
      break;
    case YELL_AT_IT:
      if (waitForYell()) { gameState = SUCCESS; } else { gameState = FAIL; }
      break;
    case SHROUD_IT:
      if (waitForShroud()) { gameState = SUCCESS; } else { gameState = FAIL; }
      break;
    case SUCCESS:
      successFunction();
      level++;
      gameState = START;
      break;
    case FAIL:
      failFunction();
      level = 1;
      gameState = START;
      break;
  }
}

GameState generateCommand() {
  int command = random(4);
  switch (command) {
    case 0: Serial.println("Bop it!"); return BOP_IT;
    case 1: Serial.println("Switch it!"); return SWITCH_IT;
    case 2: Serial.println("Yell at it!"); return YELL_AT_IT;
    case 3: Serial.println("Shroud it!"); return SHROUD_IT;
  }
}

bool waitForButton() {
  lastMillis = millis();
  while (millis() - lastMillis < roundDelay) {
    if (CircuitPlayground.leftButton() || CircuitPlayground.rightButton()) {
      Serial.println("Success: Button Pressed!");
      return true;
    }
  }
  Serial.println("Fail: No button pressed in time.");
  return false;
}

bool waitForSwitch() {
  int initialState = CircuitPlayground.slideSwitch();  // Capture initial switch state
  Serial.print("Initial Switch State: ");
  Serial.println(initialState);
  
  lastMillis = millis();
  
  while (millis() - lastMillis < roundDelay) {
    int currentState = CircuitPlayground.slideSwitch();


    if (currentState != initialState) {
      Serial.println("Success: Switch state changed!");
      return true;  // Success only if switch is toggled
    }
  }
  
  Serial.println("Fail: Switch was not toggled.");
  return false;  // Fail if switch state remains unchanged
}

bool waitForYell() {
  int baseSound = CircuitPlayground.soundSensor();  // Capture initial sound level
  Serial.print("Initial Sound Level: ");
  Serial.println(baseSound);
  
  lastMillis = millis();
  
  while (millis() - lastMillis < roundDelay) {
    int currentSound = CircuitPlayground.soundSensor();
    Serial.print("Current Sound Level: ");
    Serial.println(currentSound);

    if (currentSound - baseSound >= 75) {
      Serial.println("Success: Sound level increased by at least 75!");
      return true;  // Success if sound increases by 100
    }
    delay(350);
  }
  
  Serial.println("Fail: Sound level did not increase enough.");
  return false;  // Fail if sound does not increase enough
}

bool waitForShroud() {
  int baseLight = CircuitPlayground.lightSensor();  // Capture initial light level
  Serial.print("Initial Light Level: ");
  Serial.println(baseLight);
  
  lastMillis = millis();
  
  while (millis() - lastMillis < roundDelay) {
    int currentLight = CircuitPlayground.lightSensor();
    Serial.print("Current Light Level: ");
    Serial.println(currentLight);

    if (baseLight - currentLight >= 25) {
      Serial.println("Success: Light level dropped by at least 25!");
      return true;  // Success if light level drops by 50
    }
    delay(350);
  }

  Serial.println("Fail: Light level did not drop enough.");
  return false;  // Fail if light does not drop enough
}

void successFunction() {
  Serial.print("You had ");
  Serial.print(roundDelay / 1000);  // Convert milliseconds to seconds
  Serial.println(" seconds to complete the challenge.\n");
  roundDelay = max(2000, roundDelay - 500); 
  CircuitPlayground.playTone(1000, 100);
}

void failFunction() {
  Serial.println("\n");
  roundDelay = 5000;
  CircuitPlayground.playTone(200, 100);
}