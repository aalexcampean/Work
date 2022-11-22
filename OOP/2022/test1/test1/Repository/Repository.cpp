//
// Created by Alex Campean on 06.04.2022.
//

#include "Repository.h"

Repository::Repository() {
}

Repository::~Repository() {
}

int Repository::getRepositorySize() const {
    return this->bills.size();
}

std::vector<Bill> Repository::getAllBills() const {
    return this->bills;
}

void Repository::addBill(const Bill &bill) {
    auto it = std::find(this->bills.begin(), this->bills.end(), bill);
    if (it != this->bills.end()) {
        throw std::string("Bill already exists");
    }
    this->bills.push_back(bill);
}

void Repository::deleteBill(const std::string &inputSerialNumber) {
    auto it = std::find(this->bills.begin(), this->bills.end(), inputSerialNumber);
    if (it == this->bills.end()) {
        throw std::string("Bill does not exist");
    }
    this->bills.erase(it);
}

Bill &Repository::operator[](int index) {
    return this->bills[index];
}