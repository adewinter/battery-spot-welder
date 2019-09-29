#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>

byte BLUE_LED_PIN = 7; // 'ready to fire' status LED
byte RED_LED_PIN = 6;  // 'power on' LED

byte BLE_RX_PIN = 2;
byte BLE_TX_PIN = 3;

byte SOLENOID_PIN = 12;
byte BUTTON_PIN = 13;

int FIRE_MS = 20; 
long last_pressed = 0;

String Serialdata = "";
bool dataflag = 0;

String appData = "";

void initializePins()
{
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void setupCommunications()
{
  Serial.begin(9600);    // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);    //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
}

void setup() 
{
    solenoidOFF();
    setupCommunications();
    initializePins();

    enableRedLED(); //Power indicator
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
  enableBlueLED();
}

void setReadyOFF() {
  disableBlueLED();
}

void fire() {
  solenoidON();
  delay(FIRE_MS);
  solenoidOFF();
}

void displayReadyState()
{
  if (isReadyToFire()) {
    setReadyON();
  } else {
    setReadyOFF();
  }
}

bool isReadyToFire()
{
  //This is basically just to ensure we "debounce" the button and it doesn't get
  //into a state where we're firing off a whole bunch when we don't mean to
  
  long now = millis();
  long time_since_last_press = now - last_pressed;
  
  return time_since_last_press > 1*1000; //button was last pressed more than 1 second ago
}

bool should_fire() {
  int button_state = digitalRead(BUTTON_PIN);
  
  if(button_state && isReadyToFire()) {
    last_pressed = millis();
    return true;
  } else {
    return false;
  }
}

void processTerminal() 
{
  //incoming data from phone
  if(Terminal.available())
  {
    while (Terminal.available() != 0)
    {
      appData = String(appData + char(Terminal.read()));
    }
    
    Serial.println(appData); //echo 

    int NEW_FIRE_MS = appData.toInt();
    if(NEW_FIRE_MS != 0) {
      Terminal.println("Firing time changed from: " + String(FIRE_MS) + " MS to: " + String(NEW_FIRE_MS) + " MS.");
      Serial.println("Firing time changed from: " + String(FIRE_MS) + " MS to: " + String(NEW_FIRE_MS) + " MS.");
      FIRE_MS = NEW_FIRE_MS;
    }
    
    appData = "";
  }
}
 
void loop() {
  Dabble.processInput(); // this function is used to refresh data obtained from smartphone.
                         // Hence calling this function is mandatory in order to get data
                         // properly from your mobile.
  processTerminal();      //so that we can change the firing time from the Dabble phone app
  displayReadyState();   // Turns on the "ready" LED on the device if we're ready to fire

  if(should_fire()) {    // Checks if button is being pressed and if we're ready to fire
    fire();
  }
}
