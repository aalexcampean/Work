//
// Created by Alex Campean on 11.06.2022.
//
#pragma once


#include "../Sale/Sale.h"

class Discount {
public:
    virtual double calc (Sale s) = 0;
};

class ItemDiscount : public Discount {
private:
    int code;
    int percentage;
public:
    ItemDiscount(int code, int percentage);
    double calc(Sale s) override;
};

class SumDiscount : public Discount {
private:
    std::vector<Discount*> discounts;
public:
    SumDiscount(std::vector<Discount*> discounts);
    void add(Discount d);
    double calc(Sale s) override;
};

