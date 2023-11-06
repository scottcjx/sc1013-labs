# sc1013-labs

code to be used for SC1013 Labs

## lab 3
<!-- MARKDOWN-AUTO-DOCS:START (CODE:src=./lab_3/main.ino) -->
<!-- The below code snippet is automatically added from ./lab_3/main.ino -->
```ino
// #include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// Uncomment this line for part 5.3
 #define IMPL_LOCK
const byte targetCardID[] = {0x90, 0x8F, 0x2A, 0x21};
//const byte targetCardID[] = {0x21, 0x2A, 0x8F, 0x90};

MFRC522 mfrc522(10, 9);
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

        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        Serial.print("\t Type: \t");
        Serial.print(mfrc522.PICC_GetTypeName(piccType));
        Serial.println();

        #ifdef IMPL_LOCK
            if ( *(uint32_t*) cardID == *(uint32_t*) targetCardID)
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
```
<!-- MARKDOWN-AUTO-DOCS:END -->

## License
This project is available under the GPL v3 license. See the [LICENSE](./LICENSE.md) file for more info.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) 