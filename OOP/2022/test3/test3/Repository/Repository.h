//
// Created by Alex Campean on 27.05.2022.
//

#pragma once
#include <vector>
#include <ostream>
#include "Equation.h"


class Repository {
protected:
    std::vector<Equation> equations;
public:
    Repository(){};
    Repository(const Repository &repository): equations(repository.equations){};
    ~Repository(){};

    virtual int getRepoLength() const = 0;
    virtual std::vector<Equation> getEquations() const = 0;

    /// Add, Delete
    virtual void addElementRepo(const Equation& item) = 0;

    /// Operators Overload
    virtual Equation& operator[](int index) = 0;
    friend std::ostream &operator<<(std::ostream &os, const Repository &repository);
};

inline std::ostream &operator<<(std::ostream &os, const Repository &repository) {
    for (const auto& it: repository.equations) {
        os << it << "\n";
    }
    return os;
}
