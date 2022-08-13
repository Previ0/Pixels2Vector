#include <iostream>
#include <array>
#include <vector>

#include "image.h"

Image::Image() :
	width_{ 0 }, height_{ 0 }, pixel_array_{ nullptr }
{

}

Image::Image(int width, int height) : 
	width_{ width }, height_{ height }, pixel_array_{ nullptr }
{
	pixel_array_ = new Pixel*[width];
	for (int i = 0; i < width_; ++i) {
		pixel_array_[i] = new Pixel[height_];
	}

}

Image::Image(std::ifstream& file) :
	width_{ 0 }, height_{ 0 }, pixel_array_{ nullptr }
{
	ReadFromFile(file);
}


void Image::Reset(int width, int height) {
	// Deletion of old image
	for (int i = 0; i < this->width_; ++i) {
		delete[] pixel_array_[i];
	}

	delete[] pixel_array_;

	// Initializing new pixel array
	width_ = width;
	height_ = height;

	std::cout << "reseted w: " << width_ << std::endl;
	std::cout << "reseted h: " << height_ << std::endl;

	pixel_array_ = new Pixel*[width_];
	for (int i = 0; i < width_; ++i) {
		pixel_array_[i] = new Pixel[height_];
	}
}

void Image::SetPixelsColor(const int x, const int y, Color& color) {
	pixel_array_[x][y].setColor(color);
}

void Image::SetPixelsColor(const int x, const int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	Color temp(red, green, blue, alpha);
	pixel_array_[x][y].setColor(temp);
}

void Image::ReadFromFile(std::ifstream& file) {
	bool is_alpha_available = false;

	if (file.is_open()) {
		//reading in BMP file header
		constexpr size_t kHeaderBMP = 14; 
		std::array<char, kHeaderBMP> header; 

		file.read(header.data(),header.size());
		for (int i = 0; i < kHeaderBMP; ++i) {
			if (i % 16 == 0) std::cout << i << ": ";
			std::cout << std::hex << ((char)header[i] & 0xff) << " ";
			if ((i + 1) % 16 == 0) std::cout << "\n";
		}
		std::cout << "\n";
		std::cout << "\n";
		// offset of bytes to pixel array
		auto offset = *reinterpret_cast<uint16_t*> (&header[10]);

		//reading in size of DIB header
		char DIB_header[12]; // 12 - smallest DIB header
		file.read(DIB_header, 12);
		auto DIB_header_size = *reinterpret_cast<uint32_t*> (&DIB_header[0]);
		auto width = *reinterpret_cast<uint32_t*> (&DIB_header[4]);
		auto height = *reinterpret_cast<uint32_t*> (&DIB_header[8]);
		std::cout << "w: " << std::dec << width << std::endl;
		std::cout << "h: " << std::dec << height << std::endl;

		//rest of DIB header
		char* vital_DIB_header_data = new char[DIB_header_size - 12];
		file.read(vital_DIB_header_data, DIB_header_size - 12);
		auto depth = *reinterpret_cast<uint16_t*> (&vital_DIB_header_data[0]);
		auto bits_per_pixel = *reinterpret_cast<uint16_t*> (&vital_DIB_header_data[2]);

		if (bits_per_pixel == 32) is_alpha_available = true;


		std::vector<char> pixel_array((width * height) * bits_per_pixel / 8);
		int unmanaged_file_data_size = offset - kHeaderBMP - DIB_header_size;

		std::cout << "pixel array size: " << std::dec << pixel_array.size() << std::endl;

		std::cout << std::dec << unmanaged_file_data_size << "\n";

		for (int i = 0; i < unmanaged_file_data_size; ++i) {
			char dump;
			file.read(&dump, 1);
		}

		file.read(pixel_array.data(), pixel_array.size());

		this->Reset(width, height);

		for (int i = 0; i < pixel_array.size(); i += 4) {
			int pos_x = (i / 4) % width_; //good
			int pos_y = height_ - 1 - ((i / 4) / width_);
			pixel_array_[pos_x][pos_y].setColor(
				pixel_array[i + 2], //red
				pixel_array[i + 1],	//green
				pixel_array[i],		//blue
				pixel_array[i + 3]	//alpha
			);
		}

		std::cout << width_ << std::endl;
		std::cout << height_ << std::endl;
	}
	else {
		std::cout << "File not found\n";
	}
	file.close();
}

void Image::Print() {
	for (int i = 0; i < width_; ++i) {
		for (int j = 0; j < height_; ++j) {
			pixel_array_[i][j].PrintColor();
		}
	}
}

void Image::WriteToSVG(std::string filename) {
	if (width_ == 0 || height_ == 0) return;

	filename = filename.append(".svg");
	std::ofstream file(filename, std::ios_base::out);
	if (file.is_open()) {
		file << "<svg version=\"1.1\" width = \"" << width_ << "\" height = \"" << height_ << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

		for (int i = 0; i < width_; ++i) {
			for (int j = 0; j < height_; ++j) {
 				if (pixel_array_[i][j].getAlpha() == 0) continue;
				file << "  " <<
					"<rect x=\"" << i << "\" y=\"" << j << "\" " <<
					"width=\"1\" height=\"1\" style=\"fill:rgb(" <<
					static_cast<unsigned int>(pixel_array_[i][j].getRed()) << ", " <<
					static_cast<unsigned int>(pixel_array_[i][j].getGreen()) << ", " <<
					static_cast<unsigned int>(pixel_array_[i][j].getBlue()) <<
					");opacity:\"" << (static_cast<unsigned int>(pixel_array_[i][j].getAlpha()) / 255.0) << "\" />\n";
			}
		}
		file << "</svg>";
	}
	else {
		std::cout << "Problem with saving a file." << std::endl;
	}
	file.close();
}

Image::~Image() {
	for (int i = 0; i < this->width_; ++i) {
		delete[] pixel_array_[i];
	}

	delete[] pixel_array_;
}

