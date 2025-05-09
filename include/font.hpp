#ifndef FONT_H
#define FONT_H

#include <cstdint>
#include "graphics.hpp"

#define FONT_BIN_SIZE 16
#define FONT_VERTICAL_PIXEL 16
#define FONT_HORIZONTAL_PIXEL 8

void write_ascii(PixelWriter& writer, int x, int y, char c, const PixelColor& color);
void write_string(PixelWriter& writer, int x, int y, const char* str, const PixelColor& color);

#endif // FONT_H