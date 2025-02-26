#include <LiquidCrystal.h>

// Permently save a variable library
#include <EEPROM.h>

// Define the LED strip pins
#define LED_STRIP_PIN_1 27  
#define LED_STRIP_PIN_2 26  
#define LED_STRIP_PIN_3 25  
#define LED_STRIP_PIN_4 33  
#define LED_STRIP_PIN_5 32  

// Define the buzzer pin
#define BUZZER_PIN 4        

// Define the button pins
#define BUTTON_PIN_1 22     
#define BUTTON_PIN_2 21     
#define BUTTON_PIN_3 13      
#define BUTTON_PIN_4 14      
#define BUTTON_PIN_5 35      

// Updated ESP32 pin definitions from the schematic
const int LCD_RS = 19; // RS pin connected 
const int LCD_EN = 23;  // Enable pin connected 
const int LCD_D4 = 18; // D4 pin connected 
const int LCD_D5 = 17; // D5 pin connected 
const int LCD_D6 = 16; // D6 pin connected 
const int LCD_D7 = 15; // D7 pin connected 

// Initialize the EEPROM address
const int address = 0;

int speed = 500;
int ledIndex = 0;
int score = 0;
int millisDelay = 0;

bool direction = true;

int leds[] = {LED_STRIP_PIN_1, LED_STRIP_PIN_2, LED_STRIP_PIN_3, LED_STRIP_PIN_4, LED_STRIP_PIN_5};

// Initialize the LiquidCrystal library
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// "unsigned long currentMillis = millis()" to check delay

void setup() {
  Serial.begin(9600);

 // Set the LED strip pins as outputs
  pinMode(LED_STRIP_PIN_1, OUTPUT);
  pinMode(LED_STRIP_PIN_2, OUTPUT);
  pinMode(LED_STRIP_PIN_3, OUTPUT);
  pinMode(LED_STRIP_PIN_4, OUTPUT);
  pinMode(LED_STRIP_PIN_5, OUTPUT);

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);

  // Set the button pins as inputs
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);
  pinMode(BUTTON_PIN_4, INPUT);
  pinMode(BUTTON_PIN_5, INPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("   Welcome to");
  lcd.setCursor(2, 1);
  lcd.print("  \"SPEED\"");
  delay(3000);
  lcd.clear();
  lcd.print("Press the first");
  lcd.setCursor(0, 1);
  lcd.print("button to begin");
  while (digitalRead(BUTTON_PIN_1) != HIGH) {}

  for (int countDown = 3; countDown > 0; countDown --) {
    lcd.clear();
    lcd.print("  Starting in:");
    lcd.setCursor(7, 1);
    lcd.print(countDown);
    delay(1000);
  }
  lcd.clear();
  lcd.print("     Score:");
  lcd.setCursor(7, 1);
  lcd.print(score);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[ledIndex], LOW);    
  }
  digitalWrite(leds[ledIndex], HIGH);
  Serial.println("hi");
  checkDelay(BUTTON_PIN_3, 500, ledIndex);

  if (direction == true) {
    ledIndex += 1;
  } else {
    ledIndex -= 1;
  }
}

void checkDelay(int pin, int checkTime, int ledIndex) {
  unsigned long oldMillis = millis();

  while (true) {
    unsigned long newMillis = millis();
    
    if (newMillis - oldMillis >= checkTime) {
      digitalWrite(LED_STRIP_PIN_3, HIGH);
      break;
    }

    if (digitalRead(pin) == HIGH  && ledIndex == 3) {
      lcd.clear();
      lcd.print(newMillis);
    }
  }
}
