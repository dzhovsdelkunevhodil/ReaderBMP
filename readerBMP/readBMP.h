#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

//описание BMP
//https://jenyay.net/Programming/Bmp?ysclid=m187ni1h3q420129536



class ReaderBMP {

public:
	ReaderBMP();
	~ReaderBMP();

	void displayBMP();
	void closeBMP();
	void openBMP(const std::string& filePath);

private:

	void readFileHeader();
	void readInfoHeader();
	void readImageData();

	std::ifstream file;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	std::unique_ptr<unsigned char[]> data;
};