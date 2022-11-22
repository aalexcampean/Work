#include <fstream>
#include "HtmlRepo.h"

HtmlRepo::HtmlRepo() {
}

HtmlRepo::~HtmlRepo() {
}

void HtmlRepo::save() {
    std::ofstream output("Wishlist.html");
    output << "<!DOCTYPE html>" << std::endl;
    output << "<html>" << std::endl;

    output << "<head>" << std::endl;
    output << "<title>Wishlist</title>" << std::endl;
    output << "</head>" << std::endl;

    output << "<body>" << std::endl;
    output << "<table border=\"1\">" << std::endl;

    output << "<tr>" << std::endl;
    output << "<td>Title</td>" << std::endl;
    output << "<td>Genre</td>" << std::endl;
    output << "<td>Year of release</td>" << std::endl;
    output << "<td>Number of likes</td>" << std::endl;
    output << "<td>Trailer link</td>" << std::endl;
    output << "</tr>" << std::endl;

    for (auto& it : this->getDataBase()) {
        output << "<tr>" << std::endl;

        output << "<td>" << it.getTitle() << "</td>" << std::endl;
        output << "<td>" << it.getGenre() << "</td>" << std::endl;
        output << "<td>" << it.getYearOfRelease() << "</td>" << std::endl;
        output << "<td>" << it.getNrOfLikes() << "</td>" << std::endl;
        output << "<td><a href =" << it.getTrailer() << ">Link</a></td>" << std::endl;

        output << "</tr>" << std::endl;
    }
    output << "</table>" << std::endl;
    output << "</body>" << std::endl;
    output << "</html>" << std::endl;
    output.close();
}

void HtmlRepo::openFile() {
    std::string command = std::string("open ").append("Wishlist.html");
    system(command.c_str());
}
