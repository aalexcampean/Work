#pragma once
#include "Gene.h"
#include "../DynamicArray/Da.h"

class Repository {
private:
        DynamicArray<Gene> da;

public:
    Repository();
    Repository(const Repository &r);
    ~Repository();

    // Operators Overload
    Gene& operator[](int index);

    int getLength() const;

    /// <summary>Adds an element to the repository layer</summary>
    /// <param name="&g">Gene, a reference to the gene element that needs to be added to the repository</param>
    /// <returns></returns
    void addElementRepo(Gene &g);


};

