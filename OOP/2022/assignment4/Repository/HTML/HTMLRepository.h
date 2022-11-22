//
// Created by Alex Campean on 13.04.2022.
//

#pragma once
#include "TextFile/TextFileRepository.h"

class HTMLRepository : public TextFileRepository {
public:
    HTMLRepository();
    HTMLRepository(const std::string &inputFileName, const std::string &outputFileName);
    ~HTMLRepository();

private:
    void save() override;
};


