#include "size.h"

Size::Size()
    : w(0), h(0) {
}

Size::Size(int width, int height)
    : w(width), h(height) {
}

int Size::width() const {
    return w;
}

int Size::height() const {
    return h;
}
