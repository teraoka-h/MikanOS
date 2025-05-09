#include "../include/graphics.hpp"

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
