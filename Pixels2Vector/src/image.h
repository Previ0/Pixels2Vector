#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include "pixel.h"

enum HeaderTypeBMPDIB {

	BITMAPV3INFOHEADER = 56,
	BITMAPV4HEADER = 108,
	BITMAPV5HEADER = 124,


};

class Image {
private:
	int width_;
	int height_;
	Pixel** pixel_array_;

public:
	Image();
	Image(int width, int height);
	Image(std::ifstream& file);

	void Reset(int width, int height);

	void SetPixelsColor(const int x, const int y, Color& color);

	void SetPixelsColor(const int x, const int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	void ReadFromFile(std::ifstream& file);
	void WriteToSVG(std::string filename);

	void Print();

	~Image();
};

#endif // !IMAGE_H

