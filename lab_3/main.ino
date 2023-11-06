// #include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Uncomment this line for part 5.3
// #define IMPL_LOCK
#define targetCardID (uint32_t) 0x850A734D

MFRC552 mfrc522(10, 9);
byte cardID[4];

void setup() 
{
    Serial.begin(115200);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Ready! Present NFC Card");
}

void loop()
{
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    else if (!mfrc522.PICC_ReadCardSerial()) return;
    else 
    {
        Serial.print("Card ID: ");
        for (byte i = 0; i < 4; i++)
        {
            cardID[i] = mfrc522.uid.uidByte[i];
            Serial.print(cardID[i] < 0x10 ? " 0" : " ");
            Serial.print(cardID[i], HEX);
        }

        byte piccType = mfrc522.PICC_GetType(mfrc.uid.sak);
        Serial.print("\t Type: \t");
        Serial.print(mfrc522.PICC_GetTypeName(piccType));
        Serial.println();

        #ifdef IMPL_LOCK
            if ( *(uint32_t*) cardID[4] == targetCardID)
            {
                Serial.println("Correct Card: Unlocked");
            }
            else
            {
                Serial.println("Unknown Card: Access Denied");
            }
        #endif

        mfrc522.PICC_HaltA();
    }
}
