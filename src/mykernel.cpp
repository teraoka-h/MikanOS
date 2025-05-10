#include "../include/kernel.hpp"
#include <cstddef>
#include <cstdio>

char pixel_writer_buf[sizeof(RGB8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;


const PixelColor kDesktopBGColor{45, 118, 237};
const PixelColor kDesktopFGColor{255, 255, 255};

// #@@range_begin(mosue_cursor_shape)
const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
  "@              ",
  "@@             ",
  "@.@            ",
  "@..@           ",
  "@...@          ",
  "@....@         ",
  "@.....@        ",
  "@......@       ",
  "@.......@      ",
  "@........@     ",
  "@.........@    ",
  "@..........@   ",
  "@...........@  ",
  "@............@ ",
  "@......@@@@@@@@",
  "@......@       ",
  "@....@@.@      ",
  "@...@ @.@      ",
  "@..@   @.@     ",
  "@.@    @.@     ",
  "@@      @.@    ",
  "@       @.@    ",
  "         @.@   ",
  "         @@@   ",
};
// #@@range_end(mosue_cursor_shape)


void* operator new(size_t size, void *buf) {
  return buf;
}

void operator delete(void *obj) noexcept {}

int printk(const char* format, ...) {
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  console->putString(s);
  return result;
} 


extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
  // ピクセル描画機能
  switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor: {
      pixel_writer = new(pixel_writer_buf) RGB8BitPerColorPixelWriter(frame_buffer_config);
      break;
    }
    case kPixelBGRResv8BitPerColor: {
      pixel_writer = new(pixel_writer_buf) BGR8BitPerColorPixelWriter(frame_buffer_config);
      break;
    }
  }

  // コンソール生成
  console = new(console_buf) Console(*pixel_writer, BLACK, WHITE);

  // デスクトップの描画
  const int kFrameWidth = frame_buffer_config.horizontal_resolution;
  const int kFrameHeight = frame_buffer_config.vertical_resolution;

  fill_rectangle(*pixel_writer, {0, 0}, {kFrameWidth, kFrameHeight - 50}, kDesktopBGColor);
  fill_rectangle(*pixel_writer, {0, kFrameHeight - 50}, {kFrameWidth, 50}, {1, 8, 17});
  fill_rectangle(*pixel_writer, {0, kFrameHeight - 50}, {kFrameWidth / 5, 50}, {80, 80, 80});
  draw_rectangle(*pixel_writer, {10, kFrameHeight - 40}, {30, 30}, {160, 160, 160});


  printk("Welcome to MikanOS!\n");

  // マウスの描画
  // for (int dy = 0; dy < kMouseCursorHeight; dy++) {
  //   for (int dx = 0; dx < kMouseCursorWidth; dx++) {
  //     if (mouse_cursor_shape[dy][dx] == '@') {
  //       pixel_writer->write(200 + dx, 100 + dy, WHITE);
  //     }
  //     else if (mouse_cursor_shape[dy][dx] == '.') {
  //       pixel_writer->write(200 + dx, 100 + dy, BLACK);
  //     }
  //   }
  // }

  while (1) __asm__("hlt");
}

extern "C" void __cxa_pure_virtual() {
  while (1) __asm__("hlt");
}
