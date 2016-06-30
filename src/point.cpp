#include "point.h"

Point::Point()
    : _x(0), _y(0) {
}

Point::Point(int x, int y)
    : _x(x), _y(y) {
}

int Point::x() const {
    return _x;
}

int Point::y() const {
    return _y;
}

int &Point::rx() {
    return _x;
}

int &Point::ry() {
    return _y;
}

void Point::setX(int x) {
    _x = x;
}

void Point::setY(int y) {
    _y = y;
}
