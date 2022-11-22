//
// Created by Alex Campean on 06.04.2022.
//

#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Date {
        private:
        int day;
        int month;
        int year;
        public:
        Date();
        Date(int inputDay, int inputMonth, int inputYear);
        ~Date();

        /// Getters
        int getDay() const;
        int getMonth() const;
        int getYear() const;

        /// Operator Overload
        bool operator<(const Date &date) const;
        bool operator==(const Date &date) const;
        Date& operator=(const Date &date);
        friend std::ostream& operator<<(std::ostream& out, const Date& date);
};
inline std::ostream& operator<<(std::ostream& out, const Date& date) {
    std::string monthString = (date.month < 10)? "0" + std::to_string(date.month) : std::to_string(date.month);
    std::string dayString = (date.day < 10)? "0" + std::to_string(date.day) : std::to_string(date.day);

    out << dayString << ".";
    out << monthString << ".";
    out << date.year;
    return out;
}

class Bill {
private:
    std::string serialNumber;
    std::string company;
    Date dueDate;
    double sum;
    bool isPaid;
public:
    Bill();
    Bill(const std::string &inputSerialNumber, const std::string inputCompany, const Date &inputDueDate, double inputSum, bool inputIsPaid);
    ~Bill();

    /// Getter
    std::string getSerialNumber() const;
    std::string getCompany() const;
    Date getDueDate() const;
    double getSum() const;
    bool getIsPaid() const;

    /// Operator Overload
    bool operator<(const Bill &bill) const;
    bool operator==(const Bill &bill) const;
    bool operator==(const std::string &inputSerialNumber) const;
    friend std::ostream& operator<<(std::ostream& out, const Bill& bill);
};
inline std::ostream& operator<<(std::ostream& out, const Bill& bill) {
    out << bill.serialNumber << "; ";
    out << bill.company << "; ";
    out << bill.dueDate << "; ";
    out << std::fixed << std::setprecision(2) << bill.sum << "; ";
    out << (bill.isPaid? "true" : "false");
    return out;
}