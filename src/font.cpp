#include "../include/font.hpp"


extern const uint8_t _binary_hankaku_bin_start;
extern const uint8_t _binary_hankaku_bin_end;
extern const uint8_t _binary_hankaku_bin_size;

const uint8_t* get_font(char c) {
  auto index = FONT_BIN_SIZE * static_cast<unsigned int>(c);
  if (index >= reinterpret_cast<uintptr_t>(&_binary_hankaku_bin_size)) {
    return nullptr;
  }

  return &_binary_hankaku_bin_start + index;
}

void write_ascii(PixelWriter& writer, int x, int y, char c, const PixelColor& color) {
  const uint8_t* font_p = get_font(c);
  if (font_p == nullptr) return;

  for (int dy = 0; dy < FONT_VERTICAL_PIXEL; dy++) {
    for (int dx = 0; dx < FONT_HORIZONTAL_PIXEL; dx++) {
      if ((font_p[dy] << dx) & 0x80u) {
        writer.write(x + dx, y + dy, color);
      }
    }
  }
}

void write_string(PixelWriter& writer, int x, int y, const char* str, const PixelColor& color) {
  for (int i = 0; str[i] != '\0'; i++) {
    write_ascii(writer, x + FONT_HORIZONTAL_PIXEL * i, y, str[i], color);
  }
}
