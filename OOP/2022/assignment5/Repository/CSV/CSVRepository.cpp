//
// Created by Alex Campean on 13.04.2022.
//

#include <fstream>
#include "CSVRepository.h"

CSVRepository::CSVRepository() : TextFileRepository("AdoptionList.txt", "AdoptionList.csv") {
}

CSVRepository::CSVRepository(const std::string &inputFileName, const std::string &outputFileName) : TextFileRepository(inputFileName, outputFileName) {
}

CSVRepository::~CSVRepository() {
}

void CSVRepository::save() {
    std::ofstream output(this->getOutputFileName());
    output << "Breed" << ",";
    output << "Name" << ",";
    output << "Age" << ",";
    output << "Image Link" << "\n";
    output << *this;
    output.close();
}