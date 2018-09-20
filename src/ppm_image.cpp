#include <iostream>
#include <fstream>
#include <cstring>
#include "ppm_image.h"

PPMImage::PPMImage(std::string filename) {
    std::ifstream file;
    file.open(filename.c_str(), std::ios::binary);

    std::string tag;

    int depth;
    file >> tag;
    if(tag == "P6") {
    } else {
        std::cerr << "Invalid file type: " << filename << std::endl;
    }

    file.close();
}

bool PPMImage::write_to_file(std::string filename) const {
    std::ofstream file;
    file.open(filename.c_str(), std::ios::binary);

    file << "P6\n" << image.get_width() << " " << image.get_height() << "\n255\n";
    file.write(reinterpret_cast<const char*>(image.get_data().get()), image.get_width() * image.get_height() * 3);
    file.close();

    return true;
}
