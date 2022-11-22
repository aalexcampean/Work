//
// Created by Alex Campean on 04.04.2022.
//

#include <string>

class Gene {
private:
    std::string organism;
    std::string name;
    std::string sequence;
public:
    /// Constructors, Destructor
    Gene();
    Gene(const std::string &inputOrganism, const std::string &inputName, const std::string &inputSequence);
    Gene(const Gene &gene);
    ~Gene();

    /// Getters
    std::string getOrganism();
    std::string getName();
    std::string getSequence();

    /// Setters
    void setOrganism(const std::string &inputOrganism);
    void setName(const std::string &inputName);
    void setSequence(const std::string &inputSequence);

    /// Operator Overload
    bool operator ==(const Gene &gene) const;
    bool operator <(const Gene &gene) const;
    Gene& operator =(const Gene &gene);

    /// String Representation
    std::string toString();
};

