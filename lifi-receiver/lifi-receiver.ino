#include <LiquidCrystal.h>

#define FIRE_ALARM 6
#define ULTRASONIC_ALARM 10
#define MAGNETIC_ALARM 11
#define BUTTON_PIN 12

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);
int buttonVal;
unsigned long duration;
unsigned long buttonPressedTime = 0; // Variable to store the time when the button was pressed
bool buttonPressed = false; // Flag to indicate if the button is pressed
bool muteTriggered = false; // Flag to indicate if mute function has been triggered

// Enum to represent the state of each alarm
enum AlarmState {
  IDLE,
  TRIGGERED,
};

// State variables for each alarm
AlarmState fireAlarmState = IDLE;
AlarmState ultrasonicAlarmState = IDLE;
AlarmState magneticAlarmState = IDLE;

void fire_alarm() {
  if (fireAlarmState == TRIGGERED) {
    lcd.clear();
    lcd.print("Fire Detected");
    analogWrite(FIRE_ALARM, 1000);  // Beep the buzzer with changing frequency
  }
}

void ultrasonic_alarm() {
  if (ultrasonicAlarmState == TRIGGERED) {
    lcd.clear();
    lcd.print("Sonic Detected");
    analogWrite(ULTRASONIC_ALARM, 1000);  // Beep the buzzer with changing frequency
  }
}

void magnetic_alarm() {
  if (magneticAlarmState == TRIGGERED) {
    lcd.clear();
    lcd.print("Magnet Detected");
    analogWrite(MAGNETIC_ALARM, 1000);  // Beep the buzzer with changing frequency
  }
}

void mute() {
  lcd.clear();
  lcd.print("Alarms Muted");
  muteTriggered = true; // Set the mute triggered flag
  // Reset all alarms to IDLE
  fireAlarmState = IDLE;
  ultrasonicAlarmState = IDLE;
  magneticAlarmState = IDLE;

  // Turn off all buzzers
  noTone(FIRE_ALARM);
  noTone(ULTRASONIC_ALARM);
  noTone(MAGNETIC_ALARM);
}

void setup() {
  pinMode(9, INPUT);
  pinMode(FIRE_ALARM, OUTPUT);
  pinMode(MAGNETIC_ALARM, OUTPUT);
  pinMode(ULTRASONIC_ALARM, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("LiFi System");
  lcd.setCursor(0, 1);
  lcd.print("CSE211: Embedded");
}

void loop() {
  duration = pulseIn(9, HIGH);
  buttonVal = digitalRead(BUTTON_PIN);

  if (duration > 15000 && duration < 30000) {
    fireAlarmState = TRIGGERED;
  }
  else if (duration > 35000 && duration < 50000) {
    ultrasonicAlarmState = TRIGGERED;
  }
  else if (duration > 75000 && duration < 90000) {
    magneticAlarmState = TRIGGERED;
  }

  if (buttonVal == LOW && !buttonPressed) {
    buttonPressedTime = millis(); // Record the time when the button was pressed
    buttonPressed = true; // Set the button pressed flag
  }

  // Check if 3 seconds have passed since the button was pressed
  if (buttonPressed && millis() - buttonPressedTime >= 3000) {
    mute();
  }

  // Call alarm functions in a non-blocking way (with 25ms short delay)
  fire_alarm();
  ultrasonic_alarm();
  magnetic_alarm();

  // Reset button pressed flag and mute triggered flag after mute function is called
  if (muteTriggered) {
    buttonPressed = false;
    muteTriggered = false;
  }
}
