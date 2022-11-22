#include <fstream>
#include "CsvRepo.h"

CsvRepo::CsvRepo() {
}

CsvRepo::~CsvRepo() {
}

void CsvRepo::save() {
    std::ofstream output("Wishlist.csv");
    output << *this;
    output.close();
}

void CsvRepo::openFile() {
    std::string command = std::string("open ").append("Wishlist.csv");
    system(command.c_str());
}
