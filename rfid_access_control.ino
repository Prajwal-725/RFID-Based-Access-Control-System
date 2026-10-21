#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

// Pin configuration
#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 6

// RFID reader
MFRC522 rfid(SS_PIN, RST_PIN);

// I2C LCD
hd44780_I2Cexp lcd;

// Authorized card UID: D7 DF 49 A2
byte authorizedUID[] = {
  0xD7, 0xDF, 0x49, 0xA2
};

const byte authorizedUIDSize = 4;

// LCD dimensions
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

// Check whether the card is authorized
bool isAuthorized() {

  if (rfid.uid.size != authorizedUIDSize) {
    return false;
  }

  for (byte i = 0; i < authorizedUIDSize; i++) {

    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }

  return true;
}

// Print UID in Serial Monitor
void printCardUID() {

  Serial.print("Card UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      Serial.print(" ");
    }
  }

  Serial.println();
}

// Authorized: one long beep
void accessGrantedSound() {

  tone(BUZZER_PIN, 2000);
  delay(500);
  noTone(BUZZER_PIN);
}

// Unauthorized: three short beeps
void accessDeniedSound() {

  for (byte i = 0; i < 3; i++) {

    tone(BUZZER_PIN, 500);
    delay(150);

    noTone(BUZZER_PIN);
    delay(100);
  }
}

// Display welcome message
void showWelcome() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Welcome Prajwal");

  lcd.setCursor(0, 1);
  lcd.print("Scanned");

  accessGrantedSound();
}

// Display unknown user message
void showUnknownUser() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Unknown User");

  lcd.setCursor(0, 1);
  lcd.print("Scanned");

  accessDeniedSound();
}

// Return to the home screen
void showHomeScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("RFID SYSTEM");

  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card");
}

void setup() {

  Serial.begin(9600);

  // Initialize buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();

  // Initialize LCD
  Wire.begin();

  int lcdStatus = lcd.begin(LCD_COLS, LCD_ROWS);

  if (lcdStatus) {
    Serial.print("LCD initialization failed. Error: ");
    Serial.println(lcdStatus);

    while (true) {
      delay(100);
    }
  }

  lcd.backlight();

  showHomeScreen();

  Serial.println("========================");
  Serial.println(" RFID ACCESS CONTROL");
  Serial.println("========================");
  Serial.println("System Ready");
  Serial.println("Scan your RFID card");
}

void loop() {

  // Detect a new RFID card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read the card UID
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  printCardUID();

  // Check authorization
  if (isAuthorized()) {

    Serial.println("ACCESS GRANTED");

    showWelcome();

  } else {

    Serial.println("ACCESS DENIED");

    showUnknownUser();
  }

  // Stop communication with the card
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  // Display result for 3 seconds
  delay(3000);

  showHomeScreen();

  Serial.println("Scan your card again");
}
