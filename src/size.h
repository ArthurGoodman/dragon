#pragma once

class Size {
    int w, h;

public:
    Size();
    Size(int width, int height);

    int width() const;
    int height() const;
};
