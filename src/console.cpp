#include "../include/console.hpp"
#include "font.hpp"
#include <cstring>

/* class: Colsole */
Console::Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color):
  writer_{writer}, fg_color_{fg_color}, bg_color_{bg_color},
  buffer_{}, cursor_{0, 0}
{

}

void Console::putString(const char *s) {
  while (*s) {
    if (*s == '\n') {
      newLine();
    }
    else if (cursor_.col < kcols - 1) {
      write_ascii(writer_, 
        FONT_HORIZONTAL_PIXEL * cursor_.col, 
        FONT_VERTICAL_PIXEL * cursor_.row, 
        *s, fg_color_);
      buffer_[cursor_.row][cursor_.col] = *s;
      cursor_.col++;
    }
    s++;
  }
}

void Console::newLine() {
  cursor_.col = 0;
  if (cursor_.row < krows - 1) {
    cursor_.row++;
  }
  else {
    for (int y = 0; y < FONT_VERTICAL_PIXEL * krows; y++) {
      for (int x = 0; x < FONT_HORIZONTAL_PIXEL * kcols; x++) {
        writer_.write(x, y, bg_color_);
      }
    }
    for (int row = 0; row < krows - 1; row++) {
      memcpy(buffer_[row], buffer_[row + 1], kcols + 1);
      write_string(writer_, 0, FONT_VERTICAL_PIXEL * row, buffer_[row], fg_color_);
    }
    memset(buffer_[krows - 1], 0, kcols + 1);
  }
}