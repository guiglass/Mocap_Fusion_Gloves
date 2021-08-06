// SimpleTxAckPayload - the master base receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[1] = "!";

const int ackDataSize = 16;
char data[ackDataSize] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // to hold the acknowledgement data from the glove controller.

const byte controllerAddress[5] = {'R','x','A','A','A'};

bool newData = false;

//===============

void setup() {
    Serial.begin(115200);

    radio.begin();
    radio.setDataRate( RF24_1MBPS );
    radio.setPALevel(RF24_PA_HIGH);
    
    radio.enableAckPayload();
}

//=============

void loop() {
    sendForAck(controllerAddress, data);
    writeData();
}

//================

void sendForAck(byte *controllerAddress, char *buff) {
    radio.openWritingPipe(controllerAddress);

    bool rslt = radio.write( &dataToSend, sizeof(dataToSend) );

    if (rslt) {
        if ( radio.isAckPayloadAvailable()) {
            radio.read(buff, ackDataSize);
            newData = true;
        }
    }

}

//=================

void writeData() {
    if (newData == true) {
        Serial.write(data, 16);
        Serial.println("");
        newData = false;
    }
}
