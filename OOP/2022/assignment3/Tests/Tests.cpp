//
// Created by Alex Campean on 03.04.2022.
//

#include "Tests.h"
#include "../Repository/AdminRepository.h"
#include "../Repository/UserRepository.h"
#include "../Service/AdminService.h"
#include "../Service/UserService.h"

void testAll() {
    testDomain();
    testDynamicArray();
    testAdminRepository();
    testUserRepository();
    testServices();
}

/// General Tests
void testDomain() {
    Dog dog1{};
    Dog dog2{"Golden Retriever", "Max", 3, ""};

    assert(dog1.getBreed().empty());
    assert(dog1.getName().empty());
    assert(dog1.getAge() == 0);
    assert(dog1.getImage().empty());

    assert(dog1.toString() == "Breed:   |  Name:   |  Age: 0.0 months  |  Image: ");

    assert(dog2.getBreed() == "Golden Retriever");
    assert(dog2.getName() == "Max");
    assert(dog2.getAge() == 3);
    assert(dog2.getImage().empty());

    Dog dog3{dog2};

    assert((dog2 == dog3) == true);

    assert(dog2.toString() == "Breed: Golden Retriever  |  Name: Max  |  Age: 3.0 years  |  Image: ");
    assert(dog3.toString() == "Breed: Golden Retriever  |  Name: Max  |  Age: 3.0 years  |  Image: ");

    assert(dog3.getBreed() == "Golden Retriever");
    assert(dog3.getName() == "Max");
    assert(dog3.getAge() == 3);
    assert(dog3.getImage().empty());

    dog2.setNonUniqueAttributes("Golden Retriever", "Max", 4);
    assert(dog2.getBreed() == "Golden Retriever");
    assert(dog2.getName() == "Max");
    assert(dog2.getAge() == 4);
    assert(dog2.getImage().empty());

    assert(dog2.toString() == "Breed: Golden Retriever  |  Name: Max  |  Age: 4.0 years  |  Image: ");
    assert(dog3.toString() == "Breed: Golden Retriever  |  Name: Max  |  Age: 3.0 years  |  Image: ");

    Dog dog4;
    dog4 = dog3;
    assert(dog4.getBreed() == "Golden Retriever");
    assert(dog4.getName() == "Max");
    assert(dog4.getAge() == 3);
    assert(dog4.getImage().empty());

    assert(dog4.toString() == "Breed: Golden Retriever  |  Name: Max  |  Age: 3.0 years  |  Image: ");
}
void testDynamicArray() {
    DynamicArray<Dog> da1;

    assert(da1.getLength() == 0);
    assert(da1.getCapacity() == 10);

    /// Test Add
    Dog dog1{"Golden Retriever", "Max", 3, "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg"};
    da1.addElement(dog1);

    assert(da1.getLength() == 1);
    assert(da1.getCapacity() == 10);

    assert(da1.getIndex(dog1.getImage()) == 0);
    assert(da1[0] == dog1);

    assert(da1[da1.getIndex(dog1)].getBreed() == "Golden Retriever");
    assert(da1[da1.getIndex(dog1)].getName() == "Max");
    assert(da1[da1.getIndex(dog1)].getAge() == 3);
    assert(da1[da1.getIndex(dog1)].getImage() == "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");

    Dog dog2{"French Bulldog", "Elysees", 1, "https://pbs.twimg.com/media/FKGTAuAUcAEBXGZ.jpg"};
    da1.addElement(dog2);

    assert(da1.getLength() == 2);
    assert(da1.getCapacity() == 10);

    assert(da1.getIndex(dog2) == 1);
    assert(da1[1] == dog2);

    assert(da1[da1.getIndex(dog2)].getBreed() == "French Bulldog");
    assert(da1[da1.getIndex(dog2)].getName() == "Elysees");
    assert(da1[da1.getIndex(dog2)].getAge() == 1);
    assert(da1[da1.getIndex(dog2)].getImage() == "https://pbs.twimg.com/media/FKGTAuAUcAEBXGZ.jpg");

    /// Test Update
    Dog dog2_1{"French Bulldog", "Milo", 2, "https://pbs.twimg.com/media/FKGTAuAUcAEBXGZ.jpg"};
    da1.updateElement(dog2_1);

    assert(da1.getIndex(dog2_1) == 1);
    assert(da1[1] == dog2_1);

    assert(da1[da1.getIndex(dog2_1)].getName() == "Milo");
    assert(da1[da1.getIndex(dog2_1)].getAge() == 2);

    /// Test Delete
    da1.deleteElement(1);

    assert(da1.getLength() == 1);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog2) == -1);

    /// Test Operators
    assert(da1[0] == dog1);

    try {
        assert(da1[-1] == dog1);
    }
    catch (std::string exp){
//        std::cout << exp << std::endl;
    }

    try {
        assert(da1[100] == dog1);
    }
    catch (std::string exp){
//        std::cout << exp << std::endl;
    }

    DynamicArray<Dog> da2;
    da2 = da1;

    assert(da2.getLength() == 1);
    assert(da2.getCapacity() == 10);
    assert(da2[0] == dog1);

    /// Test Index
    Dog testDog{"Chiwawa", "Cabron", 2, ""};
    assert(da1.getIndex(testDog) == -1);

    /// Test Resize
    Dog dog3{"French Bulldog", "Bobby", 0.5, "https://www.hepper.com/wp-content/uploads/2021/11/French-Bulldog-sitting-on-the-pavement.jpg"};
    da1.addElement(dog3);
    assert(da1.getLength() == 2);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog3) == 1);

    Dog dog4{"Doberman", "Abel", 2.6, "https://www.petplace.com/static/d4eb1d31d9e22d830a0097e3e8dcdf3d/98569/AdobeStock_142438416.jpg"};
    da1.addElement(dog4);
    assert(da1.getLength() == 3);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog4) == 2);

    Dog dog5{"Chow Chow", "Michael", 1, "https://familist.ro/wp-content/uploads/2011/10/Chow-Chow-c%C3%A2inele-cu-liba-albastr%C4%83.jpg"};
    da1.addElement(dog5);
    assert(da1.getLength() == 4);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog5) == 3);

    Dog dog6{"Akita Inu", "Norra", 2, "https://i.pinimg.com/550x/6f/ce/bd/6fcebd437c9a93d111174c4a29819d2c.jpg"};
    da1.addElement(dog6);
    assert(da1.getLength() == 5);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog6) == 4);

    Dog dog7{"Corgi", "Sir", 1.3, "https://cdn.buttercms.com/ZF8K2t8hT8OoNR3W42bX"};
    da1.addElement(dog7);
    assert(da1.getLength() == 6);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog7) == 5);

    Dog dog8{"Dalmatian", "George", 2.6, "https://img.a1.ro/0/2011/7/7/47440/138355386687ac9383.jpg"};
    da1.addElement(dog8);
    assert(da1.getLength() == 7);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog8) == 6);

    Dog dog9{"Hound", "Alfred", 4, "https://imagesvc.meredithcorp.io/v3/mm/image?url=https%3A%2F%2Fstatic.onecms.io%2Fwp-content%2Fuploads%2Fsites%2F47%2F2020%2F10%2F26%2Fbloodhound-WL002292-2000.jpg"};
    da1.addElement(dog9);
    assert(da1.getLength() == 8);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog9) == 7);

    Dog dog10{"Shitzu", "Tobby", 3, "https://i.pinimg.com/474x/99/a6/b6/99a6b6b52a81dfa3f9ccb396fe51da54.jpg"};
    da1.addElement(dog10);
    assert(da1.getLength() == 9);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog10) == 8);

    Dog dog11{"German Shepherd", "Lola", 5, "https://www.akc.org/wp-content/uploads/2016/06/German-Shepherd-Dog-laying-down-in-the-backyard.jpeg"};
    da1.addElement(dog11);
    assert(da1.getLength() == 10);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(dog11) == 9);

    Dog dog12{"Chiwawa", "Pedro", 1.7, "https://cdn.pixabay.com/photo/2016/04/27/14/05/chihuahua-1356693_1280.jpg"};
    da1.addElement(dog12);
    assert(da1.getLength() == 11);
    assert(da1.getCapacity() == 20);
    assert(da1.getIndex(dog12) == 10);
}

/// Admin Tests
void testAdminRepository() {
    AdminRepository rep1;
    assert(rep1.getRepoLength() == 0);
    assert(rep1.getRepoCapacity() == 10);

    /// Test Add
    Dog dog1{"French Bulldog", "Bobby", 0.5, "https://www.hepper.com/wp-content/uploads/2021/11/French-Bulldog-sitting-on-the-pavement.jpg"};
    rep1.addElementRepo(dog1);
    assert(rep1.getRepoLength() == 1);
    assert(rep1.getRepoCapacity() == 10);
    assert(rep1[0] == dog1);

    Dog dog2{"Doberman", "Abel", 2.6, "https://www.petplace.com/static/d4eb1d31d9e22d830a0097e3e8dcdf3d/98569/AdobeStock_142438416.jpg"};
    rep1.addElementRepo(dog2);
    assert(rep1.getRepoLength() == 2);
    assert(rep1.getRepoCapacity() == 10);
    assert(rep1[1] == dog2);

    try {
        rep1.addElementRepo(dog1);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test Update
    Dog dog2_1{"Doberman", "Abel", 3, "https://www.petplace.com/static/d4eb1d31d9e22d830a0097e3e8dcdf3d/98569/AdobeStock_142438416.jpg"};
    rep1.updateElementAdminRepo(dog2_1);
    assert(rep1[1] == dog2_1);

    Dog dog3{"Chow Chow", "Michael", 1, "https://familist.ro/wp-content/uploads/2011/10/Chow-Chow-c%C3%A2inele-cu-liba-albastr%C4%83.jpg"};
    try {
        rep1.updateElementAdminRepo(dog3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test Delete
    rep1.deleteElementRepo(dog2_1.getImage());
    assert(rep1.getRepoLength() == 1);
    assert(rep1.getRepoCapacity() == 10);
    assert(rep1[0] == dog1);

    try {
        rep1.deleteElementRepo(dog3.getImage());
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test Copy Constructor
    AdminRepository rep2(rep1);
    assert(rep2.getRepoLength() == 1);
    assert(rep2[0] == dog1);

    rep2.addElementRepo(dog3);
    assert(rep2.getRepoLength() == 2);
    assert(rep2[1] == dog3);

    assert(rep1.getRepoLength() == 1);
    try {
        assert(rep1[1] == dog3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test = Overload
    AdminRepository rep3;
    rep3 = rep2;
    assert(rep3.getRepoLength() == 2);
    assert(rep3[1] == dog3);

    rep3.deleteElementRepo(dog3.getImage());
    assert(rep3.getRepoLength() == 1);
    try {
        assert(rep3[1] == dog3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    assert(rep2.getRepoLength() == 2);
    assert(rep2[1] == dog3);

    /// Test Copy Database
    Dog new_list[rep2.getRepoLength()];
    int length = 0;

    length = rep2.copyDatabase(new_list, "Chow Chow", 3);
    assert(length == 1);

    length = rep2.copyDatabase(new_list, "", 10);
    assert(length == 2);
}

void testUserRepository() {
    UserRepository rep1;
    assert(rep1.getRepoLength() == 0);
    assert(rep1.getRepoCapacity() == 10);

    /// Test Add
    Dog dog1{"French Bulldog", "Bobby", 0.5, "https://www.hepper.com/wp-content/uploads/2021/11/French-Bulldog-sitting-on-the-pavement.jpg"};
    rep1.addElementRepo(dog1);
    assert(rep1.getRepoLength() == 1);
    assert(rep1.getRepoCapacity() == 10);
    assert(rep1[0] == dog1);

    Dog dog2{"Doberman", "Abel", 2.6, "https://www.petplace.com/static/d4eb1d31d9e22d830a0097e3e8dcdf3d/98569/AdobeStock_142438416.jpg"};
    rep1.addElementRepo(dog2);
    assert(rep1.getRepoLength() == 2);
    assert(rep1.getRepoCapacity() == 10);
    assert(rep1[1] == dog2);

    try {
        rep1.addElementRepo(dog1);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test Update
    Dog dog2_1{"Doberman", "Abel", 3, "https://www.petplace.com/static/d4eb1d31d9e22d830a0097e3e8dcdf3d/98569/AdobeStock_142438416.jpg"};
    rep1.updateElementAdminRepo(dog2_1);
    assert(rep1[1] == dog2);

    /// Test Delete
    rep1.deleteElementRepo(dog2_1.getImage());
    assert(rep1.getRepoLength() == 1);
    assert(rep1.getRepoCapacity() == 10);
    assert(rep1[0] == dog1);

    Dog dog3{"Chow Chow", "Michael", 1, "https://familist.ro/wp-content/uploads/2011/10/Chow-Chow-c%C3%A2inele-cu-liba-albastr%C4%83.jpg"};
    try {
        rep1.deleteElementRepo(dog3.getImage());
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test Copy Constructor
    UserRepository rep2(rep1);
    assert(rep2.getRepoLength() == 1);
    assert(rep2.getRepoCapacity() == 10);
    assert(rep2[0] == dog1);

    /// Test Copy Database
    Dog new_list[rep1.getRepoLength()];
    assert(rep1.copyDatabase(new_list, "Chow Chow", 3) == 0);
}

void testServices() {
    /// Test User Service
    UserRepository userRepository;
    UserService serv1(&userRepository);
    assert(serv1.getServiceLength() == 0);
    assert(serv1.getServiceCapacity() == 10);

    /// Test Add
    serv1.addElementService("Golden Retriever", "Max", 3, "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    assert(serv1.getServiceLength() == 1);
    assert(serv1.getServiceCapacity() == 10);

    assert(serv1[0].getBreed() == "Golden Retriever");
    assert(serv1[0].getName() == "Max");
    assert(serv1[0].getAge() == 3);
    assert(serv1[0].getImage() == "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");

    try{
        serv1.addElementService("Golden Retriever", "Robert", 2, "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }
    assert(serv1.getServiceLength() == 1);
    assert(serv1.getServiceCapacity() == 10);

    /// Test Update
    serv1.updateElementService("Golden Retriever", "Robert", 2,
                               "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    assert(serv1[0].getBreed() == "Golden Retriever");
    assert(serv1[0].getName() == "Max");
    assert(serv1[0].getAge() == 3);
    assert(serv1[0].getImage() == "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");

    /// Test Delete
    serv1.deleteElementService("https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    assert(serv1.getServiceLength() == 0);
    assert(serv1.getServiceCapacity() == 10);

    try{
        serv1.deleteElementService("https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }
    assert(serv1.getServiceLength() == 0);
    assert(serv1.getServiceCapacity() == 10);

    /// Test First Movies
    serv1.firstDogs();
    assert(serv1.getServiceLength() == 0);
    assert(serv1.getServiceCapacity() == 10);

    /// Test Copy Database
    Dog new_list[serv1.getServiceLength()];
    int length = 0;
    assert(serv1.copyDatabase(new_list, "Golden Retriever", 9) == 0);

    /// Test Copy Constructor
    UserService serv1Copy(serv1);
    assert(serv1Copy.getServiceLength() == 0);
    assert(serv1Copy.getServiceCapacity() == 10);

    /// Test Admin Service
    AdminRepository adminRepository;
    AdminService serv2(&adminRepository);

    /// Test Add
    serv2.addElementService("Golden Retriever", "Max", 3, "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    assert(serv2.getServiceLength() == 1);
    assert(serv2.getServiceCapacity() == 10);

    assert(serv2[0].getBreed() == "Golden Retriever");
    assert(serv2[0].getName() == "Max");
    assert(serv2[0].getAge() == 3);
    assert(serv2[0].getImage() == "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");

    try{
        serv2.addElementService("Golden Retriever", "Robert", 2, "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }
    assert(serv2.getServiceLength() == 1);
    assert(serv2.getServiceCapacity() == 10);

    /// Test Update
    serv2.updateElementService("Golden Retriever", "Robert", 2,
                               "https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    assert(serv2[0].getName() == "Robert");
    assert(serv2[0].getAge() == 2);

    try{
        serv1.updateElementService("French Bulldog", "Elysees", 1, "https://pbs.twimg.com/media/FKGTAuAUcAEBXGZ.jpg");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    /// Test Delete
    serv2.deleteElementService("https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    assert(serv2.getServiceLength() == 0);
    assert(serv2.getServiceCapacity() == 10);

    try{
        serv2.deleteElementService("https://www.megapet.ro/continut/upload//Golden-Retriever.jpg");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }
    assert(serv2.getServiceLength() == 0);
    assert(serv2.getServiceCapacity() == 10);

    /// Test First Movies
    serv2.firstDogs();
    assert(serv2.getServiceLength() == 11);
    assert(serv2.getServiceCapacity() == 20);

    /// Test Copy Database
    Dog new_list2[serv2.getServiceLength()];
    int length2 = 0;
    length = serv2.copyDatabase(new_list2, "Golden Retriever", 5);
    assert(length == 1);

    /// Test Copy Constructor
    AdminService serv2Copy(serv2);
    assert(serv2Copy.getServiceLength() == 11);
    assert(serv2Copy.getServiceCapacity() == 20);

    /// Test = Overload
    AdminRepository repository3;
    AdminService serv3(&repository3);
    serv3 = serv2Copy;
    assert(serv3.getServiceLength() == 11);
    assert(serv3.getServiceCapacity() == 20);
}
