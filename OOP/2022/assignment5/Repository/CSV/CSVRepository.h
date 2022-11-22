//
// Created by Alex Campean on 13.04.2022.
//

#pragma once
#include "../TextFile/TextFileRepository.h"

class CSVRepository : public TextFileRepository {
public:
    CSVRepository();
    CSVRepository(const std::string &inputFileName, const std::string &outputFileName);
    ~CSVRepository();

private:
    void save() override;
};
