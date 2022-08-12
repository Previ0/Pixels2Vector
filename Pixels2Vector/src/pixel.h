#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"

class Pixel
{
private:
	Color color_;
	int pos_x_;
	int pos_y_;
public:
	Pixel();
	Pixel(int x, int y, Color& color);
	Pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	void setPosition(int x, int y);
	void setColor(Color& color);
	void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;
	uint8_t getAlpha() const;


	void PrintColor();
};

#endif // !PIXEL_H