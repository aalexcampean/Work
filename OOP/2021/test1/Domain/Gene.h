#pragma once
#include <string>

class Gene {
private:

    std::string organism;
    std::string name;
    std::string sequence;

public:

    // Constructor, Destructor

    Gene();
    Gene(const std::string& organism, const std::string& name, const std::string& sequence);
    Gene(Gene& g);
    ~Gene();

    // Operators Overload

    Gene& operator=(const Gene&);
    bool operator==(const Gene& g1) const;
    bool checkIfEqual(const std::string& organism, const std::string& name) const;

    // Getters

    std::string getOrganism() const;
    std::string getName() const;
    std::string getSequence() const;

    // Setters

    void setSequence(const std::string& new_sequence);

    // String Representation

    /// <summary>Returns the string representation of a given element</summary>
    /// <param name=""></param>
    /// <returns>A string containing the string representation of a given element</returns
    std::string toString() const;

};