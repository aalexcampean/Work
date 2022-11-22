//
// Created by Alex Campean on 06.04.2022.
//

#include "Tests.h"
#include "../Service/Service.h"

void testAll() {
    testComputeTotalSum();
    testDeleteRepository();
    testDeleteService();
}

void testDeleteRepository() {
    Repository repository;
    assert(repository.getRepositorySize() == 0);

    Date date1(15, 4, 2016);
    Bill bill1("0A33455X", "Digi Sport", date1, 75, false);
    repository.addBill(bill1);
    assert(repository.getRepositorySize() == 1);

    Date date2(16, 3, 2016);
    Bill bill2("EED36677", "E-On", date2, 122, true);
    repository.addBill(bill2);
    assert(repository.getRepositorySize() == 2);

    repository.deleteBill("EED36677");
    assert(repository.getRepositorySize() == 1);
}

void testDeleteService() {
    Service service;
    assert(service.getServiceSize() == 0);

    service.addInitialEntries();
    assert(service.getServiceSize() == 5);

    service.deleteBillService("EED36677");
    assert(service.getServiceSize() == 4);
}

void testComputeTotalSum() {
    Service service;
    assert(service.getServiceSize() == 0);

    service.addInitialEntries();
    assert(service.getServiceSize() == 5);

    double finalSum = service.computeTotalSumForUnpaidBills();
    assert(finalSum == 144);
}
