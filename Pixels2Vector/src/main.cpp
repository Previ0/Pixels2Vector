#include <iostream>
#include <bitset>
#include <algorithm>
#include <fstream>
#include "image.h"
#include "string"

void setExtensionName(std::string& filename, std::string expected);

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
	setExtensionName(filename, ".bmp");

	std::ifstream file(filename, std::ios::binary);
	Image image(file);

	image.WriteToSVG(filename+"_output");

	std::cin.get();

	return 0;
}

void setExtensionName(std::string& filename, std::string expected) {
	std::string temp;

	// expected extension to lowercase
	for (char c : expected) {
		std::tolower(c);
	}

	// checking wheter extension name has starting character '.'
	if (expected[0] != '.')
		expected = "." + expected;

	// if filename is empty, it 'creates example' name
	if (filename.length() == 0) {
		filename = "example" + expected;
		return;
	}

	// checking if filename contains file extension name
	int i = filename.length() - 1;
	while (filename[i] != '.' && i >= 0) {
		temp.push_back(std::tolower(filename[i]));
		--i;
	}
	temp.push_back('.');
	std::reverse(temp.begin(), temp.end());

	// checking if filename's extension is the same as expected
	// if not, it adds file extension name
	if (temp != expected) filename += expected;
	std::cout << "temp: " << temp << std::endl;

}