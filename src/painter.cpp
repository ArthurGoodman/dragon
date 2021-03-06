#include "painter.h"

#include <algorithm>

#include "canvas.h"
#include "color.h"

Painter::Painter(Canvas *canvas)
    : canvas(canvas), color(Color::rgb(0, 0, 0)) {
}

void Painter::setColor(int rgba) {
    color = rgba;
}

void Painter::setColor(byte r, byte g, byte b, byte a) {
    color = Color::rgba(r, g, b, a);
}

void Painter::setColor(const Color &color) {
    this->color = color.rgba();
}

void Painter::drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x1 >= x0 ? 1 : -1;
    int sy = y1 >= y0 ? 1 : -1;

    if (dy <= dx) {
        int d = (dy << 1) - dx;

        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;

        canvas->setPixel(x0, y0, color);

        for (int x = x0 + sx, y = y0, i = 1; i <= dx; i++, x += sx) {
            if (d > 0) {
                d += d2;
                y += sy;
            } else
                d += d1;

            canvas->setPixel(x, y, color);
        }
    } else {
        int d = (dx << 1) - dy;

        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;

        canvas->setPixel(x0, y0, color);

        for (int y = y0 + sy, x = x0, i = 1; i <= dy; i++, y += sy) {
            if (d > 0) {
                d += d2;
                x += sx;
            } else
                d += d1;

            canvas->setPixel(x, y, color);
        }
    }
}

void Painter::drawLine(const Point &p0, const Point &p1) {
    drawLine(p0.x(), p0.y(), p1.x(), p1.y());
}
