#include "Service.h"

Service::Service() {
    Repository designated_repo;
    this->repo = designated_repo;
}

Service::Service(const Service &s) {
    this->repo = s.repo;
}

Service::~Service() {

}

Gene &Service::operator[](int index) {
    return this->repo[index];
}

// Getters

int Service::getLength() const {
    return this->repo.getLength();
}

// Add, Delete, Update

void Service::addElementService(const std::string& organism, const std::string& name, const std::string& sequence) {
    Gene designated_gene(organism, name, sequence);
    this->repo.addElementRepo(designated_gene);
}

// First Genes

void Service::firstGenes() {
    this->addElementService("E_Coli_K12", "yqgE", "ATGACATCATCATTG");
    this->addElementService("M_tuberculosis", "ppiA", "TCTTCATCATCATCGG");
    this->addElementService("Mouse", "Col2a1", "TTAAAGCATGGCTCTGTG");
    this->addElementService("E_Coli_ETEC", "yqgE", "GTGACAGCGCCCTTCTTTCCACG");
    this->addElementService("E_Coli_K12", "hokC", "TTAATGAAGCATAAGCTTGATTTC");
}


