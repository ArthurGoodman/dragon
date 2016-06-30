#pragma once

class Point {
    int _x, _y;

public:
    Point();
    Point(int x, int y);

    int x() const;
    int y() const;

    int &rx();
    int &ry();

    void setX(int x);
    void setY(int y);
};
