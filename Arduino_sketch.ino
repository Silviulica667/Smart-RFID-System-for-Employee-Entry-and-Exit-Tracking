// RFID_MFRC522_UID_reader.ino
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9   // Configurable, pin connected to MFRC522 RST
#define SS_PIN  10  // Configurable, pin connected to MFRC522 SDA (SS)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);
  while (!Serial) { /* wait for serial on some boards */ }

  SPI.begin();              // Init SPI bus
  mfrc522.PCD_Init();       // Init MFRC522
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Print UID with ":" between bytes
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) Serial.print(":");
  }

  // Add a space (instead of newline) after each UID
  Serial.print("");

  // Halt PICC (stop it)
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();

  delay(500); // avoid flooding the serial monitor
}
