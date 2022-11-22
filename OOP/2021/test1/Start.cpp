#include <iostream>
#include "User_Interface/Ui.h"

void testAdd() {
    Repository my_repo;
    Gene new_gene("E_Coli_K12", "yqgE", "ATGACATCATCATTG");
    assert(my_repo.getLength() == 0);
    my_repo.addElementRepo(new_gene);

    assert(my_repo.getLength() == 1);

    assert(my_repo[0].getOrganism() == "E_Coli_K12");
}

int main() {
    testAdd();
    Ui my_ui;
    my_ui.start();
    return 0;
}
