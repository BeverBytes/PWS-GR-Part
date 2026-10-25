#include "mandelbrot.h"

int Mandelbrot::iterateMandelbrot(complexFloat z, complexFloat c) {
    int iterations = 0;
    float magnetude = 0;
    while (magnetude <= 2 && iterations < 150) {
        z = Mandelbrot::floatAdd(Mandelbrot::floatMult(z, z), c);
        magnetude = Mandelbrot::floatMagnitude(z);
        iterations++;
    }
    return iterations;
}


float sqrt(float domestic_number) {
    if (domestic_number < 0) {
        return -1.0; // Return an error value for negative inputs
    }
    if (domestic_number == 0 || domestic_number == 1) {
        return domestic_number;
    }

    // Initial guess can be the number itself
    float guess = domestic_number;
    float epsilon = 0.0000001; // Controls the precision of the result
    float previous_guess = 0;

    // Iterate until the difference between iterations is negligible
    while (guess - previous_guess > epsilon || previous_guess - guess > epsilon) {
        previous_guess = guess;
        guess = (guess + domestic_number / guess) / 2.0;
    }

    return guess;
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

float Mandelbrot::floatMagnitude(complexFloat value) {
    return sqrt(value.real * value.real + value.imag * value.imag);
}

double Mandelbrot::doubleMagnitude(complexDouble value) {
    return sqrt(value.real * value.real + value.imag * value.imag);
}

long double Mandelbrot::longDoubleMagnitude(complexLongDouble value) {
    return sqrt(value.real * value.real + value.imag * value.imag);
}