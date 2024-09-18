
#include "readBMP.h"

int main(int argc, char* argv[])
{

    try {
        if (argc != 2) {
            throw std::invalid_argument(" Incorrect usage. Usage (example): " + std::string(argv[0]) + " C:\\dev\\1.bmp");
        }
        //    ./read_display_BMP.exe C:\img\1.bmp

        ReaderBMP readerBMP;
        readerBMP.openBMP(argv[1]);
        readerBMP.displayBMP();
        readerBMP.closeBMP();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << " Invalid argument: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::runtime_error& e) {
        std::cerr << " Runtime error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << " Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << " Unknown error " << std::endl;
        return 1;
    }

    return 0;
}

