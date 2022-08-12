#ifndef BITMAP_H
#define BITMAP_H

#include <fstream>

class Bitmap {
public:
	Bitmap(std::string& filename);
	Bitmap(std::string filename);
private:
	void ReadFile();

private:
	unsigned char** arr;
	std::ifstream* bmp_file_;
	int width;
	int height;
};

#endif // !BITMAP_H




