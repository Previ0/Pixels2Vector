#include <iostream>
#include <bitset>
#include <fstream>
#include "image.h"
#include "string"


int main(int argc, char* argv[]) {

	std::cout << "====== Pixel2Vector ======" << std::endl;
	std::cout << "Program to convert bmp file to SVG, where every pixel is represented as a single rectangular SVG object." << std::endl;
	std::cout << std::endl;
	std::cout << "------ How to ------" << std::endl;
	std::cout << "Put your BMP file in the same directory with Pixel2Vector program." << std::endl;
	std::cout << "Input your filename." << std::endl;
	std::cout << "The SVG output file shoud appear in the same directory." << std::endl;
	std::cout << "==========================" << std::endl;

	std::string filename;
	std::cout << "Filename: ";
	std::getline(std::cin, filename);

	std::ifstream file(filename, std::ios::binary);
	Image image(file);

	image.WriteToSVG(filename+"_output");

	std::cin.get();

	return 0;
}