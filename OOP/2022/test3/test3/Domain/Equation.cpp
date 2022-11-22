//
// Created by Alex Campean on 27.05.2022.
//

#include "Equation.h"

double Equation::getA() const {
    return a;
}

void Equation::setA(double inputA) {
    Equation::a = inputA;
}

double Equation::getB() const {
    return b;
}

void Equation::setB(double inputB) {
    Equation::b = inputB;
}

double Equation::getC() const {
    return c;
}

void Equation::setC(double inputC) {
    Equation::c = inputC;
}

bool Equation::operator==(const Equation &rhs) const {
    return a == rhs.a &&
           b == rhs.b &&
           c == rhs.c;
}

bool Equation::operator!=(const Equation &rhs) const {
    return !(rhs == *this);
}

std::string Equation::toString() const {
    const std::string signB = b >= 0? "+" : "";
    const std::string signC = c >= 0? "+" : "";
    return std::to_string(a) + "*x^2 " + signB + std::to_string(b) + "*x " + signC + std::to_string(c);
}
