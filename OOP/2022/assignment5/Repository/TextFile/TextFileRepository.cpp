//
// Created by Alex Campean on 13.04.2022.
//

#include "TextFileRepository.h"

#include <iostream>
#include <fstream>
#include <sstream>

/// Constructors, Destructor
TextFileRepository::TextFileRepository(const std::string &inputFileName, const std::string &outputFileName) {
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
    this->load();
}

TextFileRepository::TextFileRepository(const TextFileRepository &inputRepository): InMemoryRepository(inputRepository) {
    this->inputFileName = inputRepository.inputFileName;
    this->outputFileName = inputRepository.outputFileName;
}

TextFileRepository::~TextFileRepository() {
}

/// Getters
std::string TextFileRepository::getInputFileName() const {
    return this->inputFileName;
}

std::string TextFileRepository::getOutputFileName() const {
    return this->outputFileName;
}

/// Load, Save to file
void TextFileRepository::load() {
    std::ifstream input(this->inputFileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Dog dog;
        if (!(iss >> dog)) { break; } // error

        this->addElementRepo(dog);
    }
}

void TextFileRepository::save() {
    std::ofstream output(this->outputFileName);
    output << *this;
    output.close();
}

void TextFileRepository::openFile() {
    std::string command = std::string("open ").append(this->outputFileName);
    system(command.c_str());
}