#include "mandelbrot.h"

int Mandelbrot::iterateMandelbrot(complexFloat z, complexFloat c) {
    int iterations = 0;
    float magnetude = 0;
    while (magnetude <= 4.0f && iterations < 150) {
        z = Mandelbrot::floatAdd(Mandelbrot::floatMult(z, z), c);
        magnetude = z.real * z.real + z.imag * z.imag;
        iterations++;
    }
    return iterations;
}

complexFloat Mandelbrot::floatMult(complexFloat a, complexFloat b) {
    return {a.real * b.real - a.imag * b.imag,
            a.real * b.imag + a.imag * b.real};
}

complexDouble Mandelbrot::doubleMult(complexDouble a, complexDouble b) {
    return {a.real * b.real - a.imag * b.imag,
            a.real * b.imag + a.imag * b.real};
}

complexLongDouble Mandelbrot::longDoubleMult(complexLongDouble a, complexLongDouble b) {
    return {a.real * b.real - a.imag * b.imag,
            a.real * b.imag + a.imag * b.real};
}

complexFloat Mandelbrot::floatAdd(complexFloat a, complexFloat b) {
    return {a.real + b.real, a.imag + b.imag};
}

complexDouble Mandelbrot::doubleAdd(complexDouble a, complexDouble b) {
    return {a.real + b.real, a.imag + b.imag};
}

complexLongDouble Mandelbrot::longDoubleAdd(complexLongDouble a, complexLongDouble b) {
    return {a.real + b.real, a.imag + b.imag};
}

complexFloat Mandelbrot::floatSub(complexFloat a, complexFloat b) {
    return {a.real - b.real, a.imag - b.imag};
}

complexDouble Mandelbrot::doubleSub(complexDouble a, complexDouble b) {
    return {a.real - b.real, a.imag - b.imag};
}

complexLongDouble Mandelbrot::longDoubleSub(complexLongDouble a, complexLongDouble b) {
    return {a.real - b.real, a.imag - b.imag};
}

complexFloat Mandelbrot::floatDiv(complexFloat a, complexFloat b) {
    const float denominator = b.real * b.real + b.imag * b.imag;
    return {(a.real * b.real + a.imag * b.imag) / denominator,
            (a.imag * b.real - a.real * b.imag) / denominator};
}

complexDouble Mandelbrot::doubleDiv(complexDouble a, complexDouble b) {
    const double denominator = b.real * b.real + b.imag * b.imag;
    return {(a.real * b.real + a.imag * b.imag) / denominator,
            (a.imag * b.real - a.real * b.imag) / denominator};
}

complexLongDouble Mandelbrot::longDoubleDiv(complexLongDouble a, complexLongDouble b) {
    const long double denominator = b.real * b.real + b.imag * b.imag;
    return {(a.real * b.real + a.imag * b.imag) / denominator,
            (a.imag * b.real - a.real * b.imag) / denominator};
}