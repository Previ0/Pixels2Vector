#include <iostream>

#include "pixel.h"

Pixel::Pixel() :
	pos_x_{ 0 },
	pos_y_{ 0 },
	color_(0,0,0,0)
{

}

Pixel::Pixel(int x, int y, Color& color) :
	color_(color),
	pos_x_{ x },
	pos_y_{ y }
{

}

Pixel::Pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
	color_(red, green, blue, alpha), pos_x_{x}, pos_y_{y}
{

}

void Pixel::setPosition(int x, int y) {
	pos_x_ = x;
	pos_y_ = y;
}
void Pixel::setColor(Color &color) {
	color_ = Color(color);
}

void Pixel::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	color_ = Color(red,green,blue,alpha);
}

uint8_t Pixel::getRed() const { return color_.red_; }
uint8_t Pixel::getGreen() const { return color_.green_; }
uint8_t Pixel::getBlue() const { return color_.blue_; }
uint8_t Pixel::getAlpha() const { return color_.alpha_; }

void Pixel::PrintColor() {
	std::cout << color_ << " ";
}


