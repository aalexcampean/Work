#include "Ui/Ui.h"
#include "Tests/Tests.h"
#include <stdlib.h>

int main(){
    testAll();
    system("leaks a23_912_Campean_Catalin");
    UserInterface* ui = createUserInterface();
    startUi(ui);
    system("leaks a23_912_Campean_Catalin");

}