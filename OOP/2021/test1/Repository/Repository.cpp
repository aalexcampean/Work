#include "Repository.h"

Repository::Repository() {
    DynamicArray<Gene> designated_da;
    this->da = designated_da;
}

Repository::Repository(const Repository &r) {
    this->da = r.da;

}

Repository::~Repository() {
}

int Repository::getLength() const{
    return this->da.getLength();
}

void Repository::addElementRepo(Gene &g) {
    if (this->da.getIndex(g.getOrganism(), g.getName()) != -1){
        throw std::string("Gene already exists");
    }
    this->da.addElement(g);
}

Gene &Repository::operator[](int index) {
    return this->da[index];
}


