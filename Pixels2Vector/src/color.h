#ifndef COLOR_H
#define COLOR_H

#include <inttypes.h>
#include <iostream>
//enum ColorType
//{
//	WITH_ALPHA,
//	NO_ALPHA,
//
//};

class Color
{
private:
	uint8_t red_;
	uint8_t green_;
	uint8_t blue_;
	uint8_t alpha_;

public:

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	Color(Color& color);

	friend std::ostream& operator<< (std::ostream& os, const Color& color);
	friend class Pixel;
};

#endif // !COLOR_H
