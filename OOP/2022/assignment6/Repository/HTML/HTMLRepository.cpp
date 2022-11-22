//
// Created by Alex Campean on 13.04.2022.
//

#include <fstream>
#include "HTMLRepository.h"

HTMLRepository::HTMLRepository() : TextFileRepository("AdoptionList.txt", "AdoptionList.html") {
}

HTMLRepository::HTMLRepository(const std::string &inputFileName, const std::string &outputFileName) : TextFileRepository(inputFileName, outputFileName) {
}

HTMLRepository::~HTMLRepository() {
}

void HTMLRepository::save() {
    std::ofstream output(this->getOutputFileName());
    output << "<!DOCTYPE html>" << std::endl;
    output << "<html>" << std::endl;

    output << "<head>" << std::endl;
    output << "<title>Adoption List</title>" << std::endl;
    output << "</head>" << std::endl;

    output << "<body>" << std::endl;
    output << "<table border=\"1\">" << std::endl;

    output << "<tr>" << std::endl;
    output << "<td>Breed</td>" << std::endl;
    output << "<td>Name</td>" << std::endl;
    output << "<td>Age</td>" << std::endl;
    output << "<td>Image link</td>" << std::endl;
    output << "</tr>" << std::endl;

    for (auto &it: this->getDogs()) {
        output << "<tr>" << std::endl;

        output << "<td>" << it.getBreed() << "</td>" << std::endl;
        output << "<td>" << it.getName() << "</td>" << std::endl;
        output << "<td>" << it.getAge() << "</td>" << std::endl;
        output << "<td><a href =" << it.getImage() << ">Link</a></td>" << std::endl;

        output << "</tr>" << std::endl;
    }
    output << "</table>" << std::endl;
    output << "</body>" << std::endl;
    output << "</html>" << std::endl;
    output.close();
}