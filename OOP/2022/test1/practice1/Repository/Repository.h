//
// Created by Alex Campean on 04.04.2022.
//

#include "../Domain/Gene.h"
#include <vector>

class Repository {
private:
    std::vector<Gene> genes;
public:
    /// Constructors Destructor
    Repository();
    Repository(const Repository &repository);
    ~Repository();

    /// Getter
    int getRepositoryLength();
    std::vector<Gene> getAllRepository();

    /// Add Gene
    /// <summary>Adds a gene to the repository</summary>
    /// <param name="&gene">Gene, the new gene to be added</param>
    /// <returns></returns
    void addGeneRepository(const Gene &gene);

    /// Operator Overload
    Gene& operator[](int index);
};


