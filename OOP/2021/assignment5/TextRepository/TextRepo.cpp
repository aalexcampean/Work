#include "TextRepo.h"
#include <iostream>
#include <fstream>
#include <sstream>

TextRepo::TextRepo() {
}

TextRepo::TextRepo(const std::string& file) {
    this->file_name = file;
    this->load();
}

TextRepo::TextRepo(const TextRepo &text_repo) {
    this->file_name = text_repo.file_name;
    this->db = text_repo.db;
}

TextRepo::~TextRepo() {
}

TextRepo &TextRepo::operator=(const TextRepo& text_repo) {
    this->file_name = text_repo.file_name;
    this->db = text_repo.db;
    return *this;
}

void TextRepo::load() {
    std::ifstream input(this->file_name, 0);

    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        Movie m;
        if (!(iss >> m)) { break; } // error

        this->addElement(m);
    }
}

void TextRepo::save() {
    std::ofstream output(this->file_name);
    output << *this;
    output.close();
}


