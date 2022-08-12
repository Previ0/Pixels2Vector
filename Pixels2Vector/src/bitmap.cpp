#include <iostream>
#include <array>
#include <vector>
#include <bitset>

#include "bitmap.h"

Bitmap::Bitmap(std::string& filename) :
	bmp_file_{ new std::ifstream(filename, std::ios::binary) },
	width{0},
	height{0},
	arr{nullptr}
{

	this->ReadFile();


	delete bmp_file_;
}

Bitmap::Bitmap(std::string filename) :
	bmp_file_{ new std::ifstream(filename, std::ios::binary) },
	width{ 0 },
	height{ 0 },
	arr{ nullptr }
{

	this->ReadFile();


	delete bmp_file_;
}

void Bitmap::ReadFile() {
	if (bmp_file_->is_open()) {
		constexpr size_t kHeaderSize = 54; //good

		std::array<char, kHeaderSize> header; //good
		bmp_file_->read(header.data(), header.size()); //good

	///*	for (int i = 0; i < header.size(); ++i) {
	//		std::cout << header[i] << " ";
	//	}*/

	//	auto file_size = *reinterpret_cast<uint32_t*> (&header[2]); // good 2 - byte from begginig
	//	auto data_offset = *reinterpret_cast<uint32_t*> (&header[10]); //good
	//	width = *reinterpret_cast<uint32_t*> (&header[18]); //good
	//	height = *reinterpret_cast<uint32_t*> (&header[22]); //good
	//	auto depth = *reinterpret_cast<uint16_t*> (&header[26]); //good

	//	std::cout << "file size: " << file_size << std::endl;
	//	std::cout << "data offset: " << data_offset << std::endl;
	//	std::cout << "width: " << width << std::endl;
	//	std::cout << "height: " << height << std::endl;
	//	std::cout << "depth: " << depth << "-bit" << std::endl;

	//	std::vector<char> img(data_offset - kHeaderSize); //good
	//	bmp_file_->read(img.data(), img.size()); //

	//	//std::bitset<sizeof(width) * 4 > x1(width);
	//	//std::cout << "width: " << x1 << std::endl;
	//	//std::bitset<sizeof(width) * 4 > x2(width * 3);
	//	//std::cout << "width * 3: " << x2 << std::endl;
	//	//std::bitset<sizeof(width) * 4 > x3(width * 3 + 3);
	//	//std::cout << "width * 3 + 3: " << x3 << std::endl;
	//	//std::bitset<sizeof(width) * 4 > x4(3);
	//	//std::cout << "3: " << x4 << std::endl;
	//	//std::bitset<sizeof(width) * 4 > x5(~3);
	//	//std::cout << "~3: " << x5 << std::endl;
	//	//std::bitset<sizeof(width) * 4 > x6((width * 3 + 3) & (~3));
	//	//std::cout << "(width * 3 + 3) & (~3): " << x6 << std::endl;
	//	//std::cout << ((width * 3 + 3)) << std::endl;
	//	//std::cout << ((width * 3 + 3) & (~3)) << std::endl;

	//	auto data_size = (width * 4) * height;
	//	
	//	std::cout << "data_size: " << data_size << std::endl;

	//	img.resize(data_size);
	//	bmp_file_->read(img.data(), img.size());

	//	char temp = 0;
	//	int counter = 0;

	//	for (auto i = data_size - 4; i >= 0; i -= 4) {
	//		counter++;
	//		temp = img[i];
	//		img[i] = img[i + 2];
	//		img[i + 2] = temp;

	//		if ((counter + 1)%(16*16)) std::cout << "=============" << std::endl;

	//		std::cout <<
	//			"R: " << int(img[i] & 0xff) <<
	//			" G: " << int(img[i + 1] & 0xff) <<
	//			" B: " << int(img[i + 2] & 0xff) << 
	//			" A: " << int(img[i + 3] & 0xff) << std::endl;
	//	}

	//	std::cout << "Number of pixels: " << counter << std::endl;
	}
	else {
		std::cout << "File not found\n";
		
	}
	bmp_file_->close();
}