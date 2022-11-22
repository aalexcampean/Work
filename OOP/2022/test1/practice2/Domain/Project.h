//
// Created by Alex Campean on 06.04.2022.
//


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

    out << date.year << ".";
    out << monthString << ".";
    out << dayString;
    return out;
}

class Project {
private:
    std::string name;
    std::string customer;
    Date date;
    double cost;
    bool isDone;
public:
    Project();
    Project(const std::string &inputName, const std::string &inputCustomer, Date inputDate, double inputCost, bool inputIsDone);
    ~Project();

    /// Getters
    std::string getName() const;
    std::string getCustomer() const;
    Date getDate() const;
    double getCost() const;
    bool getIsDone() const;

    /// Operator Overload
    bool operator<(const Project &project) const;
    bool operator==(const Project &project) const;
    friend std::ostream& operator<<(std::ostream& out, const Project& project);
};
inline std::ostream& operator<<(std::ostream& out, const Project& project) {
    out << project.name << "; ";
    out << project.customer << "; ";
    out << project.date << "; ";
    out << std::fixed << std::setprecision(2) << project.cost << "; ";
    out << (project.isDone? "true" : "false");
    return out;
}


