#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cstdint>
#include "frame_buffer_config.hpp"

#define PIXEL_MEM_SIZE 4 // [R, G, B](3B) + reserved(1B)

struct PixelColor {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};


class PixelWriter {
 private:
  const FrameBufferConfig& config_;

 public:
  PixelWriter(const FrameBufferConfig& config);
  virtual ~PixelWriter() = default;
  virtual void write(int x, int y, const PixelColor& color) = 0;

 protected:
  uint8_t* pixel_at(int x, int y);
};


class RGB8BitPerColorPixelWriter: public PixelWriter {
 public:
  using PixelWriter::PixelWriter;

  void write(int x, int y, const PixelColor& color) override;
};


class BGR8BitPerColorPixelWriter: public PixelWriter {
 public:
  using PixelWriter::PixelWriter;

  void write(int x, int y, const PixelColor& color) override;
};

/* common color (PixelColor)  */
#define WHITE  {255, 255, 255}
#define BLACK  {  0,   0,   0}

// RGB colors
#define RGB_RED    {255,   0,   0}
#define RGB_GREEN  {  0, 255,   0}
#define RGB_BLUE   {  0,   0, 255}
#define RGB_YELLOW {255, 255,   0}

#endif