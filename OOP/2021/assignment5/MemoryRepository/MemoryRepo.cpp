#include "MemoryRepo.h"
#include "../Exception/CustomException.h"

// Constructor, Destructor

MemoryRepo::MemoryRepo(){
}

MemoryRepo::MemoryRepo(const MemoryRepo &amr){
    this->db = amr.db;
}

MemoryRepo::~MemoryRepo() {
}

// Operators Overload

MemoryRepo& MemoryRepo::operator=(const MemoryRepo &repo) {
    this->db = repo.db;
    return *this;
}

Movie& MemoryRepo::operator[](int index) {
    return this->db[index];
}

// Getter

int MemoryRepo::getLength() const {
    return this->db.size();
}

std::vector<Movie> MemoryRepo::getDataBase() const {
    return this->db;
}

Movie& MemoryRepo::getElementByTitle(const std::string &title) {
    auto it = find(this->db.begin(), this->db.end(), title);
    return *it;
}

// Add, Delete, Update

void MemoryRepo::addElement(Movie &m) {
    auto it = find(this->db.begin(), this->db.end(), m);
    if (it != this->db.end()) {
        throw CustomException(0002, "Movie already exists");
    }

    this->db.push_back(m);
    this->save();
}

void MemoryRepo::deleteElement(const std::string &title) {
    auto it = find(this->db.begin(), this->db.end(), title);
    if (it == this->db.end()) {
        throw CustomException(0002, "Movie does not exists");
    }

    this->db.erase(it);
    this->save();
}

void MemoryRepo::updateElement(Movie &m) {
    auto it = find(this->db.begin(), this->db.end(), m);
    if (it == this->db.end()) {
        throw CustomException(0002, "Movie does not exists");
    }

    *it = m;
    this->save();
}



