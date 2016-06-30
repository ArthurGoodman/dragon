#include "image.h"

Image::Image()
    : data(0), w(0), h(0) {
}

Image::Image(int width, int height)
    : w(width), h(height) {
    data = new byte[rawSize()];
    std::fill(data, data + rawSize(), 0);
}

Image::Image(const Image &image)
    : w(image.w), h(image.h) {
    data = new byte[image.rawSize()];
    std::copy(image.data, image.data + image.rawSize(), data);
}

Image::Image(Image &&image)
    : data(image.data), w(image.w), h(image.h) {
    image.data = 0;
    image.w = 0;
    image.h = 0;
}

Image::~Image() {
    delete[] data;
}

Image &Image::operator=(const Image &image) {
    delete[] data;

    data = new byte[image.rawSize()];
    std::copy(image.data, image.data + image.rawSize(), data);

    w = image.w;
    h = image.h;

    return *this;
}

Image &Image::operator=(Image &&image) {
    delete[] data;

    data = image.data;

    w = image.w;
    h = image.h;

    image.data = 0;
    image.w = 0;
    image.h = 0;

    return *this;
}

byte *Image::bits() const {
    return data;
}

byte *Image::at(int x, int y) const {
    return &data[x * h * channels + y * channels];
}

void Image::save(const std::string &fileName) const {
    BmpHeader bmpHeader;
    DibHeader dibHeader;

    setupHeaders(bmpHeader, dibHeader);

    std::ofstream stream(fileName, std::ios::binary);
    stream.write((char *)&bmpHeader, sizeof(bmpHeader));
    stream.write((char *)&dibHeader, sizeof(dibHeader));

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            stream.write((char *)&at(x, y)[2], 1);
            stream.write((char *)&at(x, y)[1], 1);
            stream.write((char *)&at(x, y)[0], 1);
            stream.write((char *)&at(x, y)[3], 1);
        }

    stream.close();
}

void Image::fill(int rgba) {
    std::fill((int *)data, (int *)(data + rawSize()), rgba);
}

void Image::fill(const Color &color) {
    fill(color.rgba());
}

int Image::getPixel(int x, int y) const {
    if (x >= 0 && x < w && y >= 0 && y < h)
        return *(int *)at(x, y);

    return 0;
}

void Image::setPixel(int x, int y, int rgba) {
    if (x >= 0 && x < w && y >= 0 && y < h)
        *(int *)at(x, y) = rgba;
}

void Image::setPixel(int x, int y, const Color &color) {
    Canvas::setPixel(x, y, color);
}

int Image::width() const {
    return w;
}

int Image::height() const {
    return h;
}

int Image::rawSize() const {
    return channels * w * h;
}

void Image::setupHeaders(BmpHeader &bmpHeader, DibHeader &dibHeader) const {
    dibHeader.width = w;
    dibHeader.height = -h;
    dibHeader.rawSize = rawSize();
    bmpHeader.size = bmpHeader.offset + dibHeader.rawSize;

    std::fill(dibHeader.colorSpaceEndpoints, dibHeader.colorSpaceEndpoints + 9, 0);
}
