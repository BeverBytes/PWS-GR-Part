#include <fxcg/keyboard.h>
#include <fxcg/serial.h>
#include <fxcg/display.h>
#include "jaevan.h"
#include <string.h>
#include "mandelbrot.h"

void sendPacket(const JaevanPacket& p) {
    unsigned char TXbuffer[8 + p.dataLength];
    TXbuffer[0] = p.sync1;
    TXbuffer[1] = p.sync2;
    TXbuffer[2] = p.destination;
    TXbuffer[3] = p.command;
    TXbuffer[4] = (p.dataLength >> 8) & 0xFF;
    TXbuffer[5] = p.dataLength & 0xFF;
    for (int i = 0; i < p.dataLength; i++) {
        TXbuffer[i+6] = p.data[i];
    }
    TXbuffer[p.dataLength+6] = p.checksumA;
    TXbuffer[p.dataLength+7] = p.checksumB;
    Serial_Write(TXbuffer, (p.dataLength+8));
}

void sendResults(const uint8_t* results, const uint8_t pointCount) {
    JaevanProtocol jaevan;
    JaevanPacket p;
    p.sync1 = SYNC1;
    p.sync2 = SYNC2;
    p.destination = JaevanProtocol::Direction::toUSB;
    p.command = 0x04;
    p.dataLength = pointCount + 2;
    p.data[0] = 0xBA;
    p.data[1] = pointCount;
    for (uint8_t i = 0; i < pointCount; i++) {
        p.data[2 + i] = results[i];
    }
    Checksum CK = jaevan.calculateChecksumPacket(p);
    p.checksumA = CK.A;
    p.checksumB = CK.B;
    sendPacket(p);
}

void runMandelbrot(const complexFloat* complexPoints, const complexFloat c, const uint8_t pointCount) {
    uint8_t results[pointCount];
    Mandelbrot mandelbrot;
    for (uint8_t i = 0; i < pointCount; i++) {
        results[i] = mandelbrot.iterateMandelbrot(complexPoints[i], c);
    }
    sendResults(results, pointCount);
}

void prepareMandelbrot(const uint8_t* data, uint16_t length) {
    uint8_t pointCount = data[1];
    complexFloat complexPoints[data[1]];
    complexFloat c;
    uint32_t cRealInt;
    uint32_t cImagInt;
    uint32_t realInt;
    uint32_t imagInt;

    cRealInt = ((uint32_t)data[2] << 24) |
               ((uint32_t)data[3] << 16) |
               ((uint32_t)data[4] << 8) |
               (uint32_t)data[5];

    memcpy(&c.real, &cRealInt, 4);

    cImagInt = ((uint32_t)data[6] << 24) |
               ((uint32_t)data[7] << 16) |
               ((uint32_t)data[8] << 8) |
               (uint32_t)data[9];
               
    memcpy(&c.imag, &cImagInt, 4);

    for (uint16_t i = 0; i < pointCount; i++) {
        realInt = ((uint32_t)data[10+8*i] << 24) |
               ((uint32_t)data[11+8*i] << 16) |
               ((uint32_t)data[12+8*i] << 8) |
               (uint32_t)data[13+8*i];

        memcpy(&complexPoints[i].real, &realInt, 4);

        imagInt = ((uint32_t)data[14+8*i] << 24) |
               ((uint32_t)data[15+8*i] << 16) |
               ((uint32_t)data[16+8*i] << 8) |
               (uint32_t)data[17+8*i];

        memcpy(&complexPoints[i].imag, &imagInt, 4);
    }
    runMandelbrot(complexPoints, c, pointCount);
}

void handlePacket(const JaevanPacket& p) {
    if (p.command == MandelbrotCommand) {
        if (p.data[0] == 0xB9) {
            prepareMandelbrot(p.data, p.dataLength);
        }
    } else if (p.command == GRdiagCommand) {
        if (p.data[0] == 0xC7) {
            JaevanProtocol jaevan;
            JaevanPacket response;
            response.sync1 = SYNC1;
            response.sync2 = SYNC2;
            response.destination = JaevanProtocol::Direction::toUSB;
            response.command = GRdiagCommand;
            response.dataLength = 0x0002; // 2
            response.data[0] = 0xC7;
            response.data[1] = 0xC8;
            Checksum CK = jaevan.calculateChecksumPacket(response);
            response.checksumA = CK.A;
            response.checksumB = CK.B;
            sendPacket(response);
        }
    }
    return;
}


int main() {
    if (Serial_IsOpen() != 1) {
        unsigned char mode[6] = {0, 9, 2, 0, 0, 0};    // 115200 bps 8E1
        Serial_Open(mode);
    }
    int running = 1;
    int keyCol = 0;
    int keyRow = 0;
    unsigned short key = 0;
    JaevanProtocol jaevan;
    uint8_t RX;
    jaevan.onPacket(handlePacket);
    Bkey_SetAllFlags(0x80);
    Bdisp_AllClr_VRAM();
    while (running) {
        Bdisp_PutDisp_DD();
        GetKeyWait_OS(&keyCol, &keyRow, 1, 0, 0, &key);
        if (keyCol == 0x04 && keyRow == 0x09) { 
            Serial_Close(1);
            Bkey_SetAllFlags(0x00);
            keyCol = 0;
            keyRow = 0;
            running = 0; 
        }

        if (Serial_PollRX() > 0) {
            Serial_ReadSingle(&RX);
            jaevan.parseByte(RX);
        }
    }

    return 0;
}
