//
// Created by Alex Campean on 11.06.2022.
//
#pragma once

class SaleItem {
private:
    int code;
    double price;
public:
    SaleItem(){};
    SaleItem(int code, double price);
    ~SaleItem(){}

    int getCode() const;

    void setCode(int code);

    double getPrice() const;

    void setPrice(double price);;
};

int SaleItem::getCode() const {
    return code;
}

void SaleItem::setCode(int code) {
    SaleItem::code = code;
}

double SaleItem::getPrice() const {
    return price;
}

void SaleItem::setPrice(double price) {
    SaleItem::price = price;
}

