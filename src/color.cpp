#include "color.h"

int Color::rgba(byte r, byte g, byte b, byte a) {
    return a << 24 | b << 16 | g << 8 | r;
}

int Color::rgb(byte r, byte g, byte b) {
    return rgba(r, g, b, 255);
}

byte Color::red(int rgba) {
    return rgba & 0xff;
}

byte Color::green(int rgba) {
    return (rgba >> 8) & 0xff;
}

byte Color::blue(int rgba) {
    return (rgba >> 16) & 0xff;
}

byte Color::alpha(int rgba) {
    return (rgba >> 24) & 0xff;
}

Color::Color()
    : r(0), g(0), b(0), a(255) {
}

Color::Color(byte r, byte g, byte b, byte a)
    : r(r), g(g), b(b), a(a) {
}

byte Color::red() const {
    return r;
}

byte Color::green() const {
    return g;
}

byte Color::blue() const {
    return b;
}

byte Color::alpha() const {
    return a;
}

int Color::rgba() const {
    return rgba(r, g, b, a);
}
