//
// Created by Alex Campean on 11.06.2022.
//
#pragma once

#include <vector>
#include "../SaleItem/SaleItem.h"

class Sale {
private:
    std::vector<SaleItem> saleItems;
public:
    Sale(){};
    ~Sale(){};

    std::vector<SaleItem> getAll();
};
