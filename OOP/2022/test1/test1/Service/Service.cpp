//
// Created by Alex Campean on 06.04.2022.
//

#include "Service.h"

Service::Service() {
    this->repository = new Repository;
}

Service::Service(Repository *inputRepository) {
    this->repository = inputRepository;
}

Service::~Service() {
}

int Service::getServiceSize() const {
    return this->repository->getRepositorySize();
}

std::vector<Bill> Service::getAllService() const {
    return this->repository->getAllBills();
}

std::vector<Bill> Service::getAllPaidBillsSortedByDueDate() const {
    std::vector<Bill> allBills = this->repository->getAllBills();
    std::vector<Bill> paidBills;
    std::copy_if(allBills.begin(), allBills.end(), std::back_inserter(paidBills), [](auto &it){
        return it.getIsPaid();
    });
    std::sort(paidBills.begin(), paidBills.end());
    return paidBills;
}

std::vector<Bill> Service::getAllUnpaidBills() const {
    std::vector<Bill> allBills = this->repository->getAllBills();
    std::vector<Bill> unpaidBills;
    std::copy_if(allBills.begin(), allBills.end(), std::back_inserter(unpaidBills), [](auto &it){
        return !it.getIsPaid();
    });
    return unpaidBills;
}

void Service::addBillService(const std::string &inputSerialNumber, const std::string &inputCompany, int inputDay, int inputMonth,
                             int inputYear, double inputSum, bool inputIsPaid) {
    Date inputDate(inputDay, inputMonth, inputYear);
    Bill inputBill(inputSerialNumber, inputCompany, inputDate, inputSum, inputIsPaid);
    this->repository->addBill(inputBill);
}

void Service::deleteBillService(const std::string &inputSerialNumber) {
    if (inputSerialNumber.empty()) {
        throw std::string("Invalid empty serial number");
    }
    this->repository->deleteBill(inputSerialNumber);
}

double Service::computeTotalSumForUnpaidBills() {
    std::vector<Bill> unpaidBills = this->getAllUnpaidBills();
    double finalSum;
    std::for_each(unpaidBills.begin(), unpaidBills.end(), [&finalSum](auto &it){
        finalSum += it.getSum();
    });
    return finalSum;
}

void Service::addInitialEntries() {
    this->addBillService("0A33455X", "Digi Sport", 15, 4, 2016, 75, false);
    this->addBillService("EED36677", "E-On", 16, 3, 2016, 122, true);
    this->addBillService("X990TTRR", "Orange", 18, 4, 2016, 46, false);
    this->addBillService("1234RR5", "Vodafone", 20, 4, 2016, 23, false);
    this->addBillService("TRE3EERR", "Tcomm", 21, 4, 2016, 10, true);
}


