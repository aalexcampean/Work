//
// Created by Alex Campean on 27.05.2022.
//

#include <string>
#include <vector>
#include <ostream>

class Equation {
private:
    double a;
    double b;
    double c;
public:
    Equation(){};
    Equation(double a, double b, double c) : a(a), b(b), c(c) {}
    ~Equation(){}

    double getA() const;
    void setA(double inputA);

    double getB() const;
    void setB(double inputB);

    double getC() const;
    void setC(double inputC);

    std::string toString() const;

    bool operator==(const Equation &rhs) const;
    bool operator!=(const Equation &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Equation &equation);
    friend std::istream& operator>>(std::istream& in, Equation &equation);
};

inline std::ostream &operator<<(std::ostream &os, const Equation &equation) {
    os << equation.a << "," << equation.b << "," << equation.c;
    return os;
}

inline std::istream& operator>>(std::istream& in, Equation &equation) {
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < 3; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    equation.a = std::stod(fields[0]);
    equation.b = std::stod(fields[1]);
    equation.c = std::stod(fields[2]);
    return in;
}