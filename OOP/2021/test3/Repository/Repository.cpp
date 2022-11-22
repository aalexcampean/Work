#include <sstream>
#include <fstream>
#include "Repository.h"
#include "../Exception/CustomException.h"

void Repository::load() {
    std::ifstream input(this->file_name, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Weather w;
        iss >> w;
        this->addWeather(w);
    }
}

void Repository::save() {
    std::ofstream output(this->file_name);
    output << *this;
    output.close();
}

Repository::Repository(const std::string& file) {
    this->file_name = file;
    this->load();
}

Repository::Repository(const Repository &repo) {
    this->file_name = repo.file_name;
    this->db = repo.db;
}

std::vector<Weather> Repository::getDataBase() const{
    return this->db;
}

std::vector<std::string> Repository::getDescriptions() const{
    std::vector<std::string> descriptions;
    std::for_each(this->db.begin(), this->db.end(),[&descriptions](auto &it){
        auto secondIt = find(descriptions.begin(), descriptions.end(), it.getDescription());
        if (secondIt == descriptions.end()) {
            descriptions.push_back(it.getDescription());
        }
    });
    return descriptions;
}

Weather &Repository::operator[](int index) {
    return this->db[index];
}

Repository& Repository::operator=(const Repository& repo) {
    this->file_name = repo.file_name;
    this->db = repo.db;
    return *this;
}

void Repository::addWeather(Weather &w) {
    auto it = find(this->db.begin(), this->db.end(), w);
    if (it != this->db.end()) {
        throw CustomException(0002, "Weather already exists");
    }

    this->db.push_back(w);
    this->save();
}







