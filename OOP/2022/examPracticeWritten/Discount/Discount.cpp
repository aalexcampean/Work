//
// Created by Alex Campean on 11.06.2022.
//

#include "Discount.h"

ItemDiscount::ItemDiscount(int code, int percentage) : code(code), percentage(percentage) {

}

double ItemDiscount::calc(Sale s) {
    std::vector<SaleItem> allSaleItems = s.getAll();
    double discount = 0;
    std::for_each(allSaleItems.begin(), allSaleItems.end(), [&discount, this](const SaleItem &saleItem) {
        if (saleItem.getCode() == this->code) {
            discount += (saleItem.getPrice() * this->percentage) / 100;
        }

    });
    return discount;
}

SumDiscount::SumDiscount(std::vector<Discount *> discounts) : discounts(discounts){

}

void SumDiscount::add(Discount d) {
    discounts.push_back(&d);
}

double SumDiscount::calc(Sale s) {
    double discount = 0;
    std::for_each(discounts.begin(), discounts.end(), [&s, &discount](auto &d) {
        discount += d.calc(s);
    });
    return discount;
}
