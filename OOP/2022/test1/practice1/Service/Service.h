//
// Created by Alex Campean on 04.04.2022.
//

#include "../Repository/Repository.h"

class Service {
private:
    Repository* repository;
public:
    /// Constructors, Destructor
    Service();
    Service(Repository* inputRepository);
    Service(const Service &service);
    ~Service();

    /// Getter
    int getServiceLength();
    std::vector<Gene> getAllService();
    std::vector<Gene> getAllSortedAscendingByOrganism();
    /// <summary>Filters all genes based on a provided gene sequence</summary>
    /// <param name="&inputSequence">string, the gene sequence which the list is filtered by</param>
    /// <returns>The filtered list(containing just matching genes)</returns
    std::vector<Gene> getAllGenesContainingSequence(const std::string &inputSequence);

    /// Add Gene
    /// <summary>Adds a gene to the service</summary>
    /// <param name="&inputOrganism">string, the organism name of the new gene to be added</param>
    /// <param name="&inputName">string, the gene name of the new gene to be added</param>
    /// <param name="&inputSequence">string, the gene sequence of the new gene to be added</param>
    /// <returns></returns
    void addGeneService(const std::string &inputOrganism, const std::string &inputName, const std::string &inputSequence);

    /// Operator Overload
    Gene& operator[](int index);

    /// Input 5 entries
    void addFirstEntries();
};
