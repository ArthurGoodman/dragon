#include <iostream>
#include <string>

#include "image.h"
#include "painter.h"
#include "color.h"

int main(int argc, const char **argv) {
    const int n = 12;

    std::string curve = "fx", buffer;

    for (int i = 0; i < n; i++) {
        for (char c : curve)
            switch (c) {
            case 'x':
                buffer += "x+yf+";
                break;

            case 'y':
                buffer += "-fx-y";
                break;

            default:
                buffer += c;
                break;
            }

        std::swap(curve, buffer);
        buffer.clear();
    }

    Image image(1280, 720);
    image.fill(Color::rgb(255, 255, 255));

    Painter painter(&image);
    painter.setColor(255, 0, 0);

    int x = image.width() / 3 - 40, y = image.height() / 3 * 2 - 20, dx = -10, dy = 0, t;

    for (char c : curve)
        switch (c) {
        case 'f':
            painter.drawLine(x, y, x + dx, y + dy);
            x += dx;
            y += dy;
            break;

        case '+':
            t = dx;
            dx = -dy;
            dy = t;
            break;

        case '-':
            t = dx;
            dx = dy;
            dy = -t;
            break;

        default:
            break;
        }

    image.save("dragon.bmp");

    return 0;
}
