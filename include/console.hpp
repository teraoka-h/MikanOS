#ifndef CONSOLE_H
#define CONSOLE_H

#include "graphics.hpp"

struct Cursor {
  int row;
  int col;
};

class Console {
 public:
  static const int krows = 25; // コンソールの表示領域
  static const int kcols = 80; // 

 private:
  PixelWriter& writer_;
  const PixelColor fg_color_; 
  const PixelColor bg_color_;
  char buffer_[krows][kcols + 1];
  Cursor cursor_;

 public:
  Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color);
  void putString(const char *s);

 private:
  void newLine();
};

#endif // CONSOLE_H