#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include <TinyWireM.h>
#else
 #include <Wire.h>
#endif

#define HT16K33_BRIGHTNESS_CMD 0xE0
#define HT16K33_BLINK_CMD 0x80

#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3




class Font
{
	public:
		Font();
		void setData(const uint8_t *_data);
		bool getPixel(uint16_t char_index, uint16_t x, uint16_t y);
		uint16_t width;
		uint16_t height;
		uint16_t byte_per_char;
		const uint8_t *data;
};




class Bitmap
{
	public:
		Bitmap();
		void setSize(uint16_t w,uint16_t h);
		void clear(void);
		bool getPixel(uint16_t x,uint16_t y);
		void setPixel(uint16_t x,uint16_t y, bool c);
		void invertPixel(uint16_t x,uint16_t y);
		void drawBitmap(Bitmap src, uint16_t x, uint16_t y);
		void drawChar(Font font, uint16_t char_index, uint16_t x, uint16_t y);
		uint16_t width;
		uint16_t height;
		uint16_t byte_count;
		byte *pixels;
};




class Matrix16x8 : public Bitmap 
{
	public:
		Matrix16x8();
		void init(uint8_t _i2c_addr);
		void setBrightness(uint8_t b);
		void setBlinkRate(uint8_t b);
		void writeDisplay(void);
		
	protected:
		uint8_t i2c_addr;
};

