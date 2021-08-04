/*
 * Copyright 2021 Animation Prep Studios - All rights reserved.
 * If you use this code in production or other products you must give attribution to Animation Prep Studios.
 * 
 * This example shows wireless communication using a Arduino Uno attached to a PC running Animation Prep Studio - Mocap Fusion (LUXOR) and receives data from wireless mocap gloves with nRF24+.
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[1] = "!";

const int ackDataSize = 8;
char data_right[ackDataSize] = {0, 0, 0, 0, 0, 0, 0, 0}; // to hold the acknowledgement data from the right glove controller.
char data_left[ackDataSize] = {0, 0, 0, 0, 0, 0, 0, 0}; // to hold the acknowledgement data from the left glove controller.

const byte controllerAddress_Right[5] = {'R','x','A','A','B'};
const byte controllerAddress_Left[5] = {'R','x','A','A','A'};

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
    sendForAck(controllerAddress_Right, data_right);
    sendForAck(controllerAddress_Left, data_left);
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
        Serial.write(data_right, 8);
        Serial.write(data_left, 8);
        Serial.println("");
        newData = false;
    }
}
