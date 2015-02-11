
#ifdef __AVR_ATtiny85__
 #include <TinyWireM.h>
#else
 #include <Wire.h>
#endif

#include "Display.h"

/*
****
Font
****
*/

Font::Font()
{
}


// set Font Data
// -------------
void Font::setData(const uint8_t *_data)
{
	// stores data address
	data = _data;

	// read character size
	width = pgm_read_byte(data);
	height = pgm_read_byte(data + 1);

	// gets number of byte per char
	byte_per_char = (width * height + 7) / 8;
}


// returns a pixel from a char
// ---------------------------
bool Font::getPixel(uint16_t char_index, uint16_t x, uint16_t y)
{
	if(x > width){return 0;}
	if(y > height){return 0;}

	// char offset
	uint16_t char_offset = char_index * byte_per_char;

	// pixel offset
	uint16_t pixel_offset = x + y * width;

	// # byte index : char offset + partie entière de offset / 8
	uint16_t byte_index = char_offset + (pixel_offset >> 3);

	// # digit index : reste de la division de o / 8
	uint8_t digit_index = pixel_offset & 0x07;

	// the byte to read
	uint8_t byte = pgm_read_byte(data + 2 + byte_index);

	// this pixel value
	return (byte << digit_index) & 0x80;
}


/* 
******
BITMAP
******
*/

Bitmap::Bitmap()
{
}


// Set the bitmap size
// -------------------
void Bitmap::setSize(uint16_t w,uint16_t h)
{
	// bitmap dimensions
	width = w;
	height = h;

	// number of bytes needed
	byte_count = (width * height + 7) / 8;

	// allocating memory
	pixels = (byte *) malloc(byte_count);
}


// clears all pixels
// -----------------
void Bitmap::clear(void)
{
	for(uint16_t i = 0; i< byte_count; i++)
	{
		pixels[i] = 0x00;
	}
}


// get a pixel value
// -----------------
bool Bitmap::getPixel(uint16_t x,uint16_t y)
{
	if(x > width){return 0;}
	if(y > height){return 0;}

	// pixel offset
	uint16_t pixel_offset = x + y * width;

	// # byte index : partie entière de offset / 8
	uint16_t byte_index = pixel_offset >> 3;

	// # digit : reste de la division de o / 8
	uint16_t digit_index = pixel_offset & 0x07;

	// this pixel value
	return (pixels[byte_index] >> digit_index) & 0x01;
}


// set a pixel value
// -----------------
void Bitmap::setPixel(uint16_t x,uint16_t y, bool c)
{
	if(x > width){return;}
	if(y > height){return;}

	// pixel offset
	uint16_t pixel_offset = x + y * width;

	// # byte index : partie entière de offset / 8
	uint16_t byte_index = pixel_offset >> 3;

	// # digit : reste de la division de o / 8
	uint16_t digit_index = pixel_offset & 0x07;

	if(c)
	{
		pixels[byte_index] |= 1 << digit_index;
	}
	else
	{
		pixels[byte_index] &= ~(1 << digit_index);
	}
}


// inverts a pixel
// ---------------
void Bitmap::invertPixel(uint16_t x,uint16_t y)
{
	if(x > width){return;}
	if(y > height){return;}

	// pixel offset
	uint16_t pixel_offset = x + y * width;

	// # byte index : partie entière de offset / 8
	uint16_t byte_index = pixel_offset >> 3;

	// # digit : reste de la division de o / 8
	uint16_t digit_index = pixel_offset & 0x07;
		
	// invert this single bit
	pixels[byte_index] ^= (1 << digit_index);
}


// draws a bitmap on this bitmap
// -----------------------------
void Bitmap::drawBitmap(Bitmap src, uint16_t x, uint16_t y)
{
	
}


// draws the char char_index with the font font, at position x,y
void Bitmap::drawChar(Font font, uint16_t char_index, uint16_t x, uint16_t y)
{
	for(uint16_t char_x = 0; char_x < font.width; char_x++)
	{
		for(uint16_t char_y = 0; char_y < font.height; char_y++)
		{
			uint16_t dest_x = x + char_x;
			uint16_t dest_y = y + char_y;

			// le pixel est bien dans le bitmap
			if(dest_x >= 0 && dest_x < width && dest_y >= 0 && dest_y < height)
			{
				bool color = font.getPixel(char_index, char_x, char_y);
				setPixel(dest_x, dest_y, color);
			}
		}
	}	
}


/*
******
MATRIX
******
*/

Matrix16x8::Matrix16x8()
{
}


// init the matrix
// ---------------
void Matrix16x8::init(uint8_t _i2c_addr)
{
	i2c_addr = _i2c_addr;

	// starts i2c
	Wire.begin();

	// init oscillator
  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21);
  Wire.endTransmission();

	// init blinkrate
	setBlinkRate(HT16K33_BLINK_OFF);

	// init brightness
	setBrightness(15);

	// init local bitmap size
	setSize(16,8);

	// clear local bitmap
	clear();
}


// sets the brightness
// -------------------
void Matrix16x8::setBrightness(uint8_t b)
{
	if (b > 15) b = 15;
  
	Wire.beginTransmission(i2c_addr);
  Wire.write(HT16K33_BRIGHTNESS_CMD | b);
  Wire.endTransmission();  
}


// sets the blink rate
// -------------------
void Matrix16x8::setBlinkRate(uint8_t b)
{
  if (b > 3) b = 0;
  
	Wire.beginTransmission(i2c_addr);
  Wire.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
  Wire.endTransmission();
}


// writes the pixels
// -----------------
void Matrix16x8::writeDisplay(void)
{
	Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)0x00);
  for(uint16_t i=0; i < byte_count; i++)
	{
    Wire.write(pixels[i] & 0xFF);    
  }
  Wire.endTransmission();  
}


