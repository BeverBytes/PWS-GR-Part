#include <fxcg/keyboard.h>
#include <fxcg/serial.h>
#include "Jaevan.h"
#include <string.h>
#include "mandelbrot.h"

void initializeMandelbrot() {
    return;
}

void runMandelbrot(const complexFloat* complexPoints, const complexFloat c) {
    int results[sizeof(complexPoints)];
    Mandelbrot mandelbrot;
    for (int i = 0; i <= sizeof(complexPoints); i++) {
        results[i] = mandelbrot.iterateMandelbrot(complexPoints[i], c);
    }
}

void prepareMandelbrot(const uint8_t* data, uint16_t size) {
    float realPoints[((size - 1) / 8)];
    float imagPoints[((size - 1) / 8)];
    

    for (int i = 1; i <= sizeof(realPoints); i+ 2) {
        memcpy(&realPoints[i], &data[i * 4], 4);
    }
    for (int i = 2; i <= sizeof(imagPoints); i++) {
        memcpy(&imagPoints[i], &data[i * 4], 4);
    }

    complexFloat c;
    complexFloat complexPoints[((size - 1) / 8) -1];

    c.real = realPoints[0];
    c.imag = imagPoints[0];
    for (int i = 1; i <= sizeof(realPoints); i++) {
        complexPoints[i].real = realPoints[i];
        complexPoints[i].imag = imagPoints[i];
    }

    runMandelbrot(complexPoints, c);
}

void handlePacket(const JaevanPacket& p, const JaevanProtocol::Direction& d) {
    if (p.command == MandelbrotCommand) {
        if (p.data[0] == 0xB8) {
            initializeMandelbrot();
        } else if (p.data[0] == 0xB9) {
            prepareMandelbrot(p.data, p.dataLength);
        }
    }
    return;
}


int main() {
    if (Serial_IsOpen() != 1) {
        unsigned char mode[6] = {0, 9, 1, 0, 0, 0};    // 115200 bps 8E1
        Serial_Open(mode);
    }
    JaevanProtocol jaevan;
    int RxBufferSize;
    int key;
    uint8_t RX;
    jaevan.onPacket(handlePacket);

    while (1) {
        GetKey(&key);
        RxBufferSize = Serial_PollRX();
        if (RxBufferSize > 0) {
            Serial_ReadSingle(&RX);
            jaevan.parseByte(RX);
        }

        if (key == KEY_CTRL_EXE) {
            break;
        }
    }

    return 0;
}
