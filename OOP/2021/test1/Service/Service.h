#pragma once
#include "../Repository/Repository.h"

class Service {
private:
    Repository repo;

public:
    // Constructor, Destructor

    Service();
    Service(const Service &s);
    ~Service();

    // Operators Overload
    Gene& operator[](int index);

    // Getters
    int getLength() const;

    // Add

    void addElementService(const std::string& organism, const std::string& name, const std::string& sequence);

    // First Genes

    void firstGenes();
};