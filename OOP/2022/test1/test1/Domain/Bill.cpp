//
// Created by Alex Campean on 06.04.2022.
//

#include "Bill.h"

Date::Date() {
}

Date::Date(int inputDay, int inputMonth, int inputYear) {
    this->day = inputDay;
    this->month = inputMonth;
    this->year = inputYear;
}

Date::~Date() {
}

int Date::getDay() const {
    return this->day;
}

int Date::getMonth() const {
    return this->month;
}

int Date::getYear() const {
    return this->year;
}

bool Date::operator<(const Date &date) const {
    if (this->year < date.year) {
        return true;
    } else if (this->year > date.year) {
        return false;
    } else {
        if (this->month < date.month) {
            return true;
        } else if (this->month > date.month) {
            return false;
        } else {
            if (this->day < date.day) {
                return true;
            } else {
                return false;
            }
        }
    }
}

bool Date::operator==(const Date &date) const {
    return this->year == date.year && this->month == date.month && this->day == date.day;
}

Date &Date::operator=(const Date &date) {
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
    return *this;
}

/// Bill

Bill::Bill() {
}

Bill::Bill(const std::string &inputSerialNumber, const std::string inputCompany, const Date &inputDueDate, double inputSum,
           bool inputIsPaid) {
    this->serialNumber = inputSerialNumber;
    this->company = inputCompany;
    this->dueDate = inputDueDate;
    this->sum = inputSum;
    this->isPaid = inputIsPaid;
}

Bill::~Bill() {
}

std::string Bill::getSerialNumber() const {
    return this->serialNumber;
}

std::string Bill::getCompany() const {
    return this->company;
}

Date Bill::getDueDate() const {
    return this->dueDate;
}

double Bill::getSum() const {
    return this->sum;
}

bool Bill::getIsPaid() const {
    return this->isPaid;
}

bool Bill::operator<(const Bill &bill) const {
    return this->dueDate < bill.dueDate;
}

bool Bill::operator==(const Bill &bill) const {
    return this->serialNumber == bill.serialNumber;
}

bool Bill::operator==(const std::string &inputSerialNumber) const {
    return this->serialNumber == inputSerialNumber;
}

