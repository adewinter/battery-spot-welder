byte BLUE_LED_PIN = 7;
byte RED_LED_PIN = 6;
byte BLE_RX_PIN = 2;
byte BLE_TX_PIN = 3;
byte SOLENOID_PIN = 12;
byte BUTTON_PIN = 13;
byte FIRE_MS = 20; 
long last_pressed = 0;

void initialize_pins()
{
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void setup() 
{
    initialize_pins();
    setReadyON();
    disableSolenoid();
}

void enableBlueLED(){
  digitalWrite(BLUE_LED_PIN, HIGH);
}

void disableBlueLED(){
  digitalWrite(BLUE_LED_PIN, LOW);
}

void enableRedLED(){
  digitalWrite(RED_LED_PIN, HIGH);
}

void disableRedLED(){
  digitalWrite(RED_LED_PIN, LOW);
}

void solenoidON() {
  digitalWrite(SOLENOID_PIN, HIGH);
}

void solenoidOFF() {
  digitalWrite(SOLENOID_PIN, LOW);
}

void setReadyON() {
  digitalWrite(LED, HIGH);
}

void setReadyOFF() {
  digitalWrite(LED, LOW);
}

void fire() {
  setReadyOFF();
  solenoidON();
  delay(FIRE_MS);
  solenoidOFF();
  setReadyON();
}

bool should_fire() {
  int button_state = digitalRead(BUTTON_PIN);
  long now = millis();
  long time_since_last_press = now - last_pressed;
  
  if(button_state && time_since_last_press > 1*1000){ //button is currently being pressed and was last pressed more than 1 second ago
    last_pressed = now;
    return true;
  } else {
    return false;
  }
}
 
void loop() {
  if(should_fire()) {
    fire();
  }
}