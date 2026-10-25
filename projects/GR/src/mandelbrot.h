#ifndef MANDELBROT_H
#define MANDELBROT_H_H
// #pragma pack(push, 1)

struct complexFloat {
    float real;
    float imag;
};

struct complexDouble {
    double real;
    double imag;
};

struct complexLongDouble {
    long double real;
    long double imag;
};

// #pragma pop

class Mandelbrot {
    public:
        int iterateMandelbrot(complexFloat z, complexFloat c);

        complexFloat floatMult(complexFloat a, complexFloat b);
        complexDouble doubleMult(complexDouble a, complexDouble b);
        complexLongDouble longDoubleMult(complexLongDouble a, complexLongDouble b);

        complexFloat floatAdd(complexFloat a, complexFloat b);
        complexDouble doubleAdd(complexDouble a, complexDouble b);
        complexLongDouble longDoubleAdd(complexLongDouble a, complexLongDouble b);

        complexFloat floatSub(complexFloat a, complexFloat b);
        complexDouble doubleSub(complexDouble a, complexDouble b);
        complexLongDouble longDoubleSub(complexLongDouble a, complexLongDouble b);

        complexFloat floatDiv(complexFloat a, complexFloat b);
        complexDouble doubleDiv(complexDouble a, complexDouble b);
        complexLongDouble longDoubleDiv(complexLongDouble a, complexLongDouble b);

        float floatMagnitude(complexFloat value);
        double doubleMagnitude(complexDouble value);
        long double longDoubleMagnitude(complexLongDouble value);
};

#endif