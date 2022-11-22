//
// Created by Alex Campean on 06.04.2022.
//

#include "Project.h"

/// Date

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

/// Project

Project::Project() {
}

Project::Project(const std::string &inputName, const std::string &inputCustomer, Date inputDate, double inputCost, bool inputIsDone) {
    this->name = inputName;
    this->customer = inputCustomer;
    this->date = inputDate;
    this->cost = inputCost;
    this->isDone = inputIsDone;
}

Project::~Project() {
}

std::string Project::getName() const {
    return this->name;
}

std::string Project::getCustomer() const {
    return this->customer;
}

Date Project::getDate() const {
    return this->date;
}

double Project::getCost() const {
    return this->cost;
}

bool Project::getIsDone() const {
    return this->isDone;
}

bool Project::operator<(const Project &project) const {
    return this->date < project.date;
}

bool Project::operator==(const Project &project) const {
    return this->name == project.name && this->customer == project.customer;
}
