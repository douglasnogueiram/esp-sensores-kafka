#define connect_width 64
#define connect_height 64
const unsigned char connect_bits[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 
  0x00, 0xFF, 0x01, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0x00, 0xFE, 0x00, 0x00, 
  0x00, 0xC0, 0x3F, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x00, 
  0x00, 0x07, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0xE0, 0x7F, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x00, 
  0xC0, 0x01, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0xC0, 0x00, 0x00, 0x00, 
  0x00, 0xC0, 0x7F, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7, 0x40, 
  0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF1, 0x3F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 
  0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x01, 0xF0, 0x00, 
  0x00, 0x00, 0x80, 0xFF, 0xFF, 0x03, 0xFC, 0x01, 0x00, 0x00, 0x80, 0xFF, 
  0xFF, 0x07, 0xFC, 0x03, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 
  0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x07, 0xF0, 0xFF, 
  0xFF, 0x01, 0xFE, 0x07, 0x80, 0x3F, 0xFC, 0xFF, 0xFF, 0x01, 0xFE, 0x03, 
  0xC0, 0xFF, 0x1F, 0xFF, 0xFF, 0x00, 0xFC, 0x03, 0xC0, 0xFF, 0x07, 0xFE, 
  0xFF, 0x00, 0xF8, 0x01, 0xE0, 0xFF, 0x00, 0xFC, 0x3F, 0x00, 0x60, 0x00, 
  0xE0, 0x7F, 0x00, 0xF8, 0x1F, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 0xE0, 
  0x07, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 
  0x80, 0x3F, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 
  0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFC, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFE, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
