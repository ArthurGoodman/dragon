#include "canvas.h"

Canvas::~Canvas() {
}

void Canvas::setPixel(int x, int y, const Color &color) {
    setPixel(x, y, color.rgba());
}

Size Canvas::size() {
    return Size(width(), height());
}
