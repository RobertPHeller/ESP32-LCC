#ifndef _ADAFRUIT_ST7789H_
#define _ADAFRUIT_ST7789H_

#include "Adafruit_ST77xx.h"
#include <Esp32SPI.hxx>
#include "freertos_drivers/esp32/Esp32Gpio.hxx"
#include "os/Gpio.hxx"

/// Subclass of ST77XX type display for ST7789 TFT Driver
class Adafruit_ST7789 : public Adafruit_ST77xx {
public:
  Adafruit_ST7789(int8_t cs, Gpio *dc, Gpio *rst);

  void setRotation(uint8_t m);
  void init(openmrn_arduino::Esp32SPI*spi,uint16_t width, uint16_t height);

protected:
  uint8_t _colstart2 = 0, ///< Offset from the right
      _rowstart2 = 0;     ///< Offset from the bottom

private:
  uint16_t windowWidth;
  uint16_t windowHeight;
};

#endif // _ADAFRUIT_ST7789H_
