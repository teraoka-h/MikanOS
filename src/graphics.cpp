#include "../include/graphics.hpp"


void fill_rectangle(PixelWriter& writer, 
                    const Vector2D<int>& pos, 
                    const Vector2D<int>& size,
                    const PixelColor& color) {
  for (int dy = 0; dy < size.y; dy++) {
    for (int dx = 0; dx < size.x; dx++) {
      writer.write(pos.x + dx, pos.y + dy, color);
    }
  }
}

// 長方形(枠のみ)の描画s
void draw_rectangle(PixelWriter& writer, 
                    const Vector2D<int>& pos, 
                    const Vector2D<int>& size,
                    const PixelColor& color) {
  for (int dx = 0; dx < size.x; dx++) {
    writer.write(pos.x + dx, pos.y, color);
    writer.write(pos.x + dx, pos.y + size.y - 1, color);
  }
  for (int dy = 1; dy < size.y - 1; dy++) {
    writer.write(pos.x, pos.y + dy, color);
    writer.write(pos.x + size.x - 1, pos.y + dy, color);
  }
}

/**
 * class: PixelWriter
 */
PixelWriter::PixelWriter(const FrameBufferConfig& config): config_{config} {};

uint8_t* PixelWriter::pixel_at(int x, int y) {
  return config_.frame_buffer + PIXEL_MEM_SIZE * (config_.pixels_per_scan_line * y + x);
}


/**
 * class: RGB8BitPerColorPixelWriter
 */
void RGB8BitPerColorPixelWriter::write(int x, int y, const PixelColor& color) {
  auto p = pixel_at(x, y);
  p[0] = color.r;
  p[1] = color.g;
  p[2] = color.b;
};


/**
 * class: BGR8BitPerColorPixelWriter
 */
void BGR8BitPerColorPixelWriter::write(int x, int y, const PixelColor& color) {
    auto p = pixel_at(x, y);
    p[0] = color.b;
    p[1] = color.g;
    p[2] = color.r;
};
