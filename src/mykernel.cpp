#include "../include/kernel.hpp"
#include <cstddef>
#include <cstdio>

char pixel_writer_buf[sizeof(RGB8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;


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

  // 画面を白色で塗りつぶす
  for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
    for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
      pixel_writer->write(x, y, WHITE);
    }
  }
  // for (int x = 0; x < 200; ++x) {
  //   for (int y = 0; y < 100; ++y) {
  //     pixel_writer->write(x, y, RGB_GREEN);
  //   }
  // }

  // // #@@range_begin(write_fonts)
  // int i = 0;
  // for (char c = '!'; c <= '~'; ++c, ++i) {
  //   write_ascii(*pixel_writer, FONT_HORIZONTAL_PIXEL * i, 50, c, BLACK);
  // }
  // // #@@range_end(write_fonts)
  // write_string(*pixel_writer, 0, 66, "Hello world!", RGB_BLUE);

  console = new(console_buf) Console(*pixel_writer, BLACK, WHITE);

  for (int i = 0; i < 27; i++) {
    printk("printk: %d\n", i);
  }

  while (1) __asm__("hlt");
}

extern "C" void __cxa_pure_virtual() {
  while (1) __asm__("hlt");
}
