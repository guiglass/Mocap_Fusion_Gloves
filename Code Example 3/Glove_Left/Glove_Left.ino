/*
 * Copyright 2021 Animation Prep Studios - All rights reserved.
 * If you use this code in production or other products you must give attribution to Animation Prep Studios.
 * 
 * This example shows simple wireless communication using a Arduino Uno with nRF24+ radio that sends data to a Arduino Uno with nRF24+ attached to a PC running Animation Prep Studio - Mocap Fusion (LUXOR).
 * Each analog input reads the bend value of a SEN-08606 Flex Sensors (4.5" typical).
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  49
#define CSN_PIN 48

const byte thisSlaveAddress[5] = {'R','x','A','A','A'}; //LEFT HAND ADDRESS

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
char ackData[] = {0, 0, 0, 0, 0, 0, 0, 0};
bool newData = false;

//==============

void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);  
    pinMode(A4, INPUT);

    radio.begin();
    radio.setDataRate( RF24_1MBPS );
    radio.setPALevel(RF24_PA_HIGH);
    
    radio.openReadingPipe(1, thisSlaveAddress);

    radio.enableAckPayload();
    radio.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data

    radio.startListening();
}

//==========

void loop() {
    getData();
}

//============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        updateReplyData();
        newData = true;
    }
}

//================

void updateReplyData() {
    int _A0 = analogRead(A0);  
    int _A1 = analogRead(A1);  
    int _A2 = analogRead(A2);  
    int _A3 = analogRead(A3);
    int _A4 = analogRead(A4);
  
    ackData[0] = _A0 & 0b0000000011111111;
    ackData[1] = ((_A0 & 0b0000111100000000) >> 8) + ((_A1 & 0b0000000000001111) << 4);
    ackData[2] = ((_A1 & 0b0000111111110000) >> 4);
    ackData[3] = _A2 & 0b0000000011111111;
    ackData[4] = ((_A2 & 0b0000111100000000) >> 8) + ((_A3 & 0b0000000000001111) << 4);
    ackData[5] = ((_A3 & 0b0000111111110000) >> 4);
    ackData[6] = _A4 & 0b0000000011111111;
    ackData[7] = ((_A4 & 0b0000111100000000) >> 8) ;

    radio.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
}
