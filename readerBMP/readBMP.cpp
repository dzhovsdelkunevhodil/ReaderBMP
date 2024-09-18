
#include "readBMP.h"

ReaderBMP::ReaderBMP() : file(), fileHeader{}, infoHeader{}, data(nullptr) {}

ReaderBMP::~ReaderBMP() {
    closeBMP();
}

void ReaderBMP::openBMP(const std::string& filePath) {
    if (file.is_open()) {
        file.close();
    }
    file.open(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error(" Error opening file: " + filePath);
    }

    readFileHeader();
    readInfoHeader();
    readImageData();
}

void ReaderBMP::closeBMP() {
    if (file.is_open()) {
        file.close();
    }
    data.reset();
}

void ReaderBMP::displayBMP() {
    if (!file.is_open()) {
        throw std::runtime_error(" File is not open");
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int bytesPerPixel = infoHeader.biBitCount / 8;
    // � ������� BMP ������ ������ �������� ������ ���� ��������� �� 4 �����
    // ���� ����� ������ �������� � ������ �� ������ 4, �� � ����� ������ 
    // ����������� ����� �������� (padding), ����� ����� ����� ������ ����� ������� 4.
    int padding = (4 - (width * bytesPerPixel) % 4) % 4;
    // width * bytesPerPixel ----  ���� ��� �������� ����� ������ ��������
    // (4 - (width * bytesPerPixel) % 4) ---- ���� ��� ������������ ������ �� 4 �����
    // (4 - (width * bytesPerPixel) % 4) % 4 ---- �������� ������, ����� ������� ����� 0

    for (int y = height - 1; y >= 0; --y) { //����������������� ����� �������� 
        //BMP ������ ������ ������ �������� � �������� ������� (����� �����)
        for (int x = 0; x < width; ++x) {
            int index = (y * (width * bytesPerPixel + padding) + x * bytesPerPixel);
            // width * bytesPerPixel + padding ---- ���� ��� �������� ����� ������ �������� � ������ ��������
            // y * (width * bytesPerPixel + padding) ---- ���� ��� �������� ���� ����� �������� �� ������� ������
            // x * bytesPerPixel ---- ���� ��� �������� �������� � ������� ������ �� �������� �������

            unsigned char blue = data[index];
            unsigned char green = data[index + 1];
            unsigned char red = data[index + 2];

            if (red == 0 && green == 0 && blue == 0) {
                std::cout << '#';
            }
            else if (red == 255 && green == 255 && blue == 255) {
                std::cout << '.';
            }
            else {
                std::cout << '?';
                //throw std::runtime_error(" Unsupported color at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
            }
        }
        std::cout << std::endl;
    }

}

void ReaderBMP::readFileHeader() {
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42) { //BitMap
        throw std::runtime_error(" Unsupported format");
    }
}//����������������������

void ReaderBMP::readInfoHeader() {
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    std::cout << " BMP format " + std::to_string(infoHeader.biBitCount) + '\n';
    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) { // 24 � 32 ���
        throw std::runtime_error(" Unsupported BMP format " + std::to_string(infoHeader.biBitCount));
    }
}

void ReaderBMP::readImageData() {
    data = std::make_unique<unsigned char[]>(infoHeader.biSizeImage);
    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    file.read(reinterpret_cast<char*>(data.get()), infoHeader.biSizeImage);
    if (file.fail()) {
        throw std::runtime_error(" Error reading BMP data");
    }
}
