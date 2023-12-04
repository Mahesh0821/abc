#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9        // Define the RFID reader reset pin.
#define SS_PIN          10       // Define the RFID reader SS pin.
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an MFRC522 instance.

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initiate SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Scan RFID tags to identify them...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return;

  // Print the UID of the card
  Serial.print("UID Tag: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Compare the UID with known values to identify the tags
  if (isTag1(mfrc522.uid.uidByte) ) {
    Serial.println("Tag 1 detected.");
  } else if (isTag2(mfrc522.uid.uidByte)) {
    Serial.println("Tag 2 detected.");
  } else if (isTag3(mfrc522.uid.uidByte)) {
    Serial.println("Tag 3 detected.");
  } else {
    Serial.println("Unknown tag.");
  }

  delay(1000);  // Pause for a moment to avoid reading the same card multiple times.
}

bool isTag1(byte uid[]) {
  // Replace with the UID of the first tag you want to identify
  byte knownUID[] = {0x5C, 0x0A, 0x79, 0x6E};

  for (int i = 0; i < 4; i++) {
    if (uid[i] != knownUID[i]) {
      return false;
    }
  }
  return true;
}

bool isTag2(byte uid[]) {
  // Replace with the UID of the second tag you want to identify
  byte knownUID[] = {0x03, 0x2F, 0xB8, 0x0B};

  for (int i = 0; i < 4; i++) {
    if (uid[i] != knownUID[i]) {
      return false;
    }
  }
  return true;
}

bool isTag3(byte uid[]) {
  // Replace with the UID of the third tag you want to identify
  byte knownUID[] = {0x9C, 0xCE, 0x72, 0x6E};

  for (int i = 0; i < 4; i++) {
    if (uid[i] != knownUID[i]) {
      return false;
    }
  }
  return true;
}
