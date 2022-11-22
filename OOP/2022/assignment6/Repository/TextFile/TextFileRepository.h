//
// Created by Alex Campean on 13.04.2022.
//

#pragma once
#include "../InMemory/InMemoryRepository.h"

class TextFileRepository : public InMemoryRepository {
private:
    std::string inputFileName;
    std::string outputFileName;

    /// Load, Save to file
    void load();
    void save() override;

public:
    /// Constructors, Destructor
    TextFileRepository(const std::string &inputFileName, const std::string &outputFileName);
    TextFileRepository(const TextFileRepository &inputRepository);
    ~TextFileRepository();

    /// Getters
    std::string getInputFileName() const;
    std::string getOutputFileName() const;

    void openFile();
};

