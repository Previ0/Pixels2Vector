#include "color.h"

Color::Color() :
	red_{ 0 }, green_{ 0 }, blue_{ 0 }, alpha_{ 0 }
{
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
	red_{red}, green_{green}, blue_{blue}, alpha_{alpha}
{
}

Color::Color(Color& color) :
	red_{ color.red_ },
	green_{ color.green_ },
	blue_{ color.blue_ },
	alpha_{ color.alpha_ }
{

}

std::ostream& operator<< (std::ostream& os, const Color& color) {
	os << std::hex << (int) color.red_ << (int) color.green_ << (int)color.blue_ << (int) color.alpha_;
	return os;
}