#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
int LED=D1;

// Define your WiFi credentials and ThingSpeak API key
const char* ssid = "123";
const char* password = "123456789";
const char* apiKey = "L3RV786O394UI7S6";

WiFiClient client;

// Create an MFRC522 instance
MFRC522 mfrc522(2, 4);  // Define the SDA and RST pins

void setup() {
  Serial.begin(1200);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED,OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);


  // Define the fields for your ThingSpeak channel
  int field1 = 0;  // RFID Tag ID

  // Set the fields
  ThingSpeak.setField(field1, 0);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String tagUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      tagUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      tagUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    tagUID.toUpperCase();

    Serial.print("Tag UID: ");
    Serial.println(tagUID);
    if (tagUID != 0) {
      digitalWrite(D1, HIGH);
      delay(500);
      digitalWrite(D1, LOW);

    }

    sendDataToThingSpeak(0);


    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}

void sendDataToThingSpeak(int tagID) {
  int field1 = tagID;  // Set the tag ID in field1

  // Update ThingSpeak fields
  ThingSpeak.setField(1, field1);

  // Write data to ThingSpeak
  int response = ThingSpeak.writeFields(2367912, apiKey);
  Serial.println(response);


  if (response == 200) {
    Serial.println("Data sent to ThingSpeak successfully!");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP error code: ");
    Serial.println(response);
  }
  response = 0;
  delay(1000);  // Update data every 5 seconds
}
