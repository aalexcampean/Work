#include "Tests.h"
#include <iostream>

void testAll() {
    testEntity();
    testDynamicArray();
    testAdminRepository();
    testAdminService();
    testUserRepository();
    testUserService();
}

void testEntity() {
    Movie m1{};
    Movie m2{"Arsène Lupin", "Adventure/Love", 2004, 0, "https://youtu.be/5owbso3KJf4"};

    assert(m1.getTitle() == "");
    assert(m1.getGenre() == "");
    assert(m1.getYearOfRelease() == 0);
    assert(m1.getNrOfLikes() == 0);
    assert(m1.getTrailer() == "");

    assert(m1.toString() == "Title:   |  Genre:   |  Year of Release: 0  |  Number of likes: 0  |  Trailer: ");

    assert(m2.getTitle() == "Arsène Lupin");
    assert(m2.getGenre() == "Adventure/Love");
    assert(m2.getYearOfRelease() == 2004);
    assert(m2.getNrOfLikes() == 0);
    assert(m2.getTrailer() == "https://youtu.be/5owbso3KJf4");

    Movie m3{m2};

    assert((m2 == m3) == true);

    assert(m2.toString() == "Title: Arsène Lupin  |  Genre: Adventure/Love  |  Year of Release: 2004  |  Number of likes: 0  |  Trailer: https://youtu.be/5owbso3KJf4");
    assert(m3.toString() == "Title: Arsène Lupin  |  Genre: Adventure/Love  |  Year of Release: 2004  |  Number of likes: 0  |  Trailer: https://youtu.be/5owbso3KJf4");

    assert(m3.getTitle() == "Arsène Lupin");
    assert(m3.getGenre() == "Adventure/Love");
    assert(m3.getYearOfRelease() == 2004);
    assert(m3.getNrOfLikes() == 0);
    assert(m3.getTrailer() == "https://youtu.be/5owbso3KJf4");

    m2.setNonUniqueAttributes("Drama", 2017, 10, "https://youtu.be/2fhO2A4SL24");
    assert(m2.getGenre() == "Drama");
    assert(m2.getYearOfRelease() == 2017);
    assert(m2.getNrOfLikes() == 10);
    assert(m2.getTrailer() == "https://youtu.be/2fhO2A4SL24");

    assert(m2.toString() == "Title: Arsène Lupin  |  Genre: Drama  |  Year of Release: 2017  |  Number of likes: 10  |  Trailer: https://youtu.be/2fhO2A4SL24");
    assert(m3.toString() == "Title: Arsène Lupin  |  Genre: Adventure/Love  |  Year of Release: 2004  |  Number of likes: 0  |  Trailer: https://youtu.be/5owbso3KJf4");

    Movie m4;
    m4 = m3;
    assert(m4.getTitle() == "Arsène Lupin");
    assert(m4.getGenre() == "Adventure/Love");
    assert(m4.getYearOfRelease() == 2004);
    assert(m4.getNrOfLikes() == 0);
    assert(m4.getTrailer() == "https://youtu.be/5owbso3KJf4");

    assert(m4.toString() == "Title: Arsène Lupin  |  Genre: Adventure/Love  |  Year of Release: 2004  |  Number of likes: 0  |  Trailer: https://youtu.be/5owbso3KJf4");


}

void testDynamicArray() {
    DynamicArray<Movie> da1;

    assert(da1.getLength() == 0);
    assert(da1.getCapacity() == 10);

    // test add

    Movie m1{"Arsène Lupin", "Adventure/Love", 2004, 0, "https://youtu.be/5owbso3KJf4"};
    da1.addElement(m1);

    assert(da1.getLength() == 1);
    assert(da1.getCapacity() == 10);

    assert(da1.getIndex(m1.getTitle()) == 0);
    assert(da1[0] == m1);

    assert(da1[da1.getIndex(m1.getTitle())].getTitle() == "Arsène Lupin");
    assert(da1[da1.getIndex(m1.getTitle())].getGenre() == "Adventure/Love");
    assert(da1[da1.getIndex(m1.getTitle())].getYearOfRelease() == 2004);
    assert(da1[da1.getIndex(m1.getTitle())].getNrOfLikes() == 0);
    assert(da1[da1.getIndex(m1.getTitle())].getTrailer() == "https://youtu.be/5owbso3KJf4");


    Movie m2{"Amélie", "Comedy Romance/Love", 2001, 0, "https://youtu.be/HUECWi5pX7o"};
    da1.addElement(m2);

    assert(da1.getLength() == 2);
    assert(da1.getCapacity() == 10);

    assert(da1.getIndex(m2.getTitle()) == 1);
    assert(da1[1] == m2);

    assert(da1[da1.getIndex(m2.getTitle())].getTitle() == "Amélie");
    assert(da1[da1.getIndex(m2.getTitle())].getGenre() == "Comedy Romance/Love");
    assert(da1[da1.getIndex(m2.getTitle())].getYearOfRelease() == 2001);
    assert(da1[da1.getIndex(m2.getTitle())].getNrOfLikes() == 0);
    assert(da1[da1.getIndex(m2.getTitle())].getTrailer() == "https://youtu.be/HUECWi5pX7o");

    // test update

    Movie m2_1{"Amélie", "Comedy Romance/Love", 2003, 10, "https://youtu.be/HUECWi5pX7o"};
    da1.updateElement(m2_1, da1.getIndex(m2.getTitle()));

    assert(da1.getIndex(m2_1.getTitle()) == 1);
    assert(da1[1] == m2_1);
    assert(da1[da1.getIndex(m2.getTitle())].getYearOfRelease() == 2003);
    assert(da1[da1.getIndex(m2.getTitle())].getNrOfLikes() == 10);

    // test delete

    da1.deleteElement(1);

    assert(da1.getLength() == 1);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m2.getTitle()) == -1);

    // test operators

    assert(da1[0] == m1);

    try {
        assert(da1[-1] == m1);
    }
    catch (std::string exp){
//        std::cout << exp << std::endl;
    }

    try {
        assert(da1[100] == m1);
    }
    catch (std::string exp){
//        std::cout << exp << std::endl;
    }

    DynamicArray<Movie> da2;
    da2 = da1;

    assert(da2.getLength() == 1);
    assert(da2.getCapacity() == 10);
    assert(da2[0] == m1);

    // test get element by unique field

    assert(da2.getElementByUniqueField(m1.getTitle()) == m1);


    // test resize

    Movie m3{"Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM"};
    da1.addElement(m3);
    assert(da1.getLength() == 2);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m3.getTitle()) == 1);

    Movie m4{"Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ"};
    da1.addElement(m4);
    assert(da1.getLength() == 3);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m4.getTitle()) == 2);

    Movie m5{"La science des rêves", "Surrealistic Science Fantasy/Comedy", 2006, 0, "https://youtu.be/dHtE0szIip0"};
    da1.addElement(m5);
    assert(da1.getLength() == 4);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m5.getTitle()) == 3);

    Movie m6{"Irréversible", "Psychological Thriller/Drama", 2002, 0, "https://youtu.be/ZoDtJjqkfxU"};
    da1.addElement(m6);
    assert(da1.getLength() == 5);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m6.getTitle()) == 4);

    Movie m7{"Fallen Angels", "Crime/Drama", 1995, 0, "https://youtu.be/dtum6XVH3HI"};
    da1.addElement(m7);
    assert(da1.getLength() == 6);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m7.getTitle()) == 5);

    Movie m8{"Instinct", "Drama/Thriller", 2019, 0, "https://www.youtube.com/watch?v=0OIetiMoseA"};
    da1.addElement(m8);
    assert(da1.getLength() == 7);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m8.getTitle()) == 6);

    Movie m9{"Love", "Erotic Drama", 2015, 0, "https://youtu.be/62yCdFzP9Mc"};
    da1.addElement(m9);
    assert(da1.getLength() == 8);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m9.getTitle()) == 7);

    Movie m10{"Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA"};
    da1.addElement(m10);
    assert(da1.getLength() == 9);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m10.getTitle()) == 8);

    Movie m11{"Queen of Heart", "Drama", 2019, 0, "https://youtu.be/MaxIbXW23NA"};
    da1.addElement(m11);
    assert(da1.getLength() == 10);
    assert(da1.getCapacity() == 10);
    assert(da1.getIndex(m11.getTitle()) == 9);

    Movie m12{"Parasite", "Thriller", 2019, 0, "https://youtu.be/5xH0HfJHsaY"};
    da1.addElement(m12);
    assert(da1.getLength() == 11);
    assert(da1.getCapacity() == 20);
    assert(da1.getIndex(m12.getTitle()) == 10);

}

void testAdminRepository() {

    AdminRepository rep1;
    assert(rep1.getAdminRepoLength() == 0);
    assert(rep1.getAdminRepoCapacity() == 10);

    // test add

    Movie m1{"Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM"};
    rep1.addElementAdminRepo(m1);
    assert(rep1.getAdminRepoLength() == 1);
    assert(rep1.getAdminRepoCapacity() == 10);
    assert(rep1[0] == m1);

    Movie m2{"Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ"};
    rep1.addElementAdminRepo(m2);
    assert(rep1.getAdminRepoLength() == 2);
    assert(rep1.getAdminRepoCapacity() == 10);
    assert(rep1[1] == m2);

    try {
        rep1.addElementAdminRepo(m1);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    // test update

    Movie m2_1{"Little Joe", "SF/Drama", 2018, 10, "https://youtu.be/eYfKlNBLLeQ"};
    rep1.updateElementAdminRepo(m2_1);
    assert(rep1[1] == m2_1);

    Movie m3{"Irréversible", "Psychological Thriller/Drama", 2002, 0, "https://youtu.be/ZoDtJjqkfxU"};
    try {
        rep1.updateElementAdminRepo(m3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    // test delete

    rep1.deleteElementAdminRepo(m2_1.getTitle());
    assert(rep1.getAdminRepoLength() == 1);
    assert(rep1.getAdminRepoCapacity() == 10);
    assert(rep1[0] == m1);

    try {
        rep1.deleteElementAdminRepo(m3.getTitle());
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    AdminRepository rep2(rep1);
    assert(rep2.getAdminRepoLength() == 1);
    assert(rep2[0] == m1);

    rep2.addElementAdminRepo(m3);
    assert(rep2.getAdminRepoLength() == 2);
    assert(rep2[1] == m3);

    assert(rep1.getAdminRepoLength() == 1);
    try {
        assert(rep1[1] == m3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    AdminRepository rep3;
    rep3 = rep2;
    assert(rep3.getAdminRepoLength() == 2);
    assert(rep3[1] == m3);

    rep3.deleteElementAdminRepo(m3.getTitle());
    assert(rep3.getAdminRepoLength() == 1);
    try {
        assert(rep3[1] == m3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    assert(rep2.getAdminRepoLength() == 2);
    assert(rep2[1] == m3);

    // test get element by unique field

    assert(rep2.getElementByUniqueField(m3.getTitle()) == m3);

    // test copy database

    Movie new_list[rep2.getAdminRepoLength()];
    int length = 0;

    length = rep2.copyDatabase(new_list, "Psychological Thriller/Drama");
    assert(length == 1);

    length = rep2.copyDatabase(new_list, "");
    assert(length == 2);
}

void testAdminService() {

    AdminService serv1;

    assert(serv1.getAdminServiceLength() == 0);
    assert(serv1.getAdminServiceCapacity() == 10);

    serv1.addElementAdminService("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
    assert(serv1.getAdminServiceLength() == 1);
    assert(serv1.getAdminServiceCapacity() == 10);

    try{
        serv1.addElementAdminService("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    assert(serv1[0].getTitle() == "Garçon Chiffon");
    assert(serv1[0].getGenre() == "Comedy/Drama");
    assert(serv1[0].getYearOfRelease() == 2020);
    assert(serv1[0].getNrOfLikes() == 0);
    assert(serv1[0].getTrailer() == "https://youtu.be/Ghdso2T9qwA");

    serv1.updateElementAdminService("Garçon Chiffon", "Comedy/Drama", 2020, 30, "https://youtu.be/Ghdso2T9qwA");
    assert(serv1[0].getNrOfLikes() == 30);

    try{
        serv1.updateElementAdminService("Chiffon", "Comedy/Drama", 2020, 30, "https://youtu.be/Ghdso2T9qwA");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    serv1.deleteElementAdminService("Garçon Chiffon");
    assert(serv1.getAdminServiceLength() == 0);
    assert(serv1.getAdminServiceCapacity() == 10);

    try{
        serv1.deleteElementAdminService("Chiffon");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    serv1.firstMovies();
    assert(serv1.getAdminServiceLength() == 10);
    assert(serv1.getAdminServiceCapacity() == 10);

    AdminService serv2(serv1);
    assert(serv2.getAdminServiceLength() == 10);
    assert(serv2.getAdminServiceCapacity() == 10);
    assert(serv2[0].getTitle() == "Climax");
    assert(serv2[9].getTitle() == "Queen of Hearts");

    serv2.deleteElementAdminService("Climax");
    assert(serv2.getAdminServiceLength() == 9);
    assert(serv1.getAdminServiceLength() == 10);

    AdminService serv3;
    serv3 = serv2;
    assert(serv3.getAdminServiceLength() == 9);
    assert(serv3.getAdminServiceCapacity() == 10);
    assert(serv2[0].getTitle() == "Queen of Hearts");

    serv3.updateElementAdminService("Amélie", "Comedy Romance/Love", 2001, 10, "https://youtu.be/HUECWi5pX7o");
    assert(serv3[1].getTitle() == "Amélie");
    assert(serv3[1].getNrOfLikes() == 10);
    assert(serv2[1].getTitle() == "Amélie");
    assert(serv2[1].getNrOfLikes() == 0);

    Movie m1("Amélie", "Comedy Romance/Love", 2001, 10, "https://youtu.be/HUECWi5pX7o");

    // test get element by unique field

    assert(serv2.getElementByUniqueField("Amélie") == m1);

    // test copy database

    Movie new_list[serv2.getAdminServiceLength()];
    int length = 0;

    length = serv2.copyDatabase(new_list, "Comedy Romance/Love");
    assert(length == 1);
}

void testUserRepository(){
    UserRepository rep1;
    assert(rep1.getUserRepoLength() == 0);
    assert(rep1.getUserRepoCapacity() == 10);

    // test add

    Movie m1{"Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM"};
    rep1.addElementUserRepo(m1);
    assert(rep1.getUserRepoLength() == 1);
    assert(rep1.getUserRepoCapacity() == 10);
    assert(rep1[0] == m1);

    Movie m2{"Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ"};
    rep1.addElementUserRepo(m2);
    assert(rep1.getUserRepoLength() == 2);
    assert(rep1.getUserRepoCapacity() == 10);
    assert(rep1[1] == m2);

    try {
        rep1.addElementUserRepo(m1);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    // test delete

    Movie m2_1{"Little Joe", "SF/Drama", 2018, 10, "https://youtu.be/eYfKlNBLLeQ"};
    Movie m3{"Irréversible", "Psychological Thriller/Drama", 2002, 0, "https://youtu.be/ZoDtJjqkfxU"};

    rep1.deleteElementUserRepo(m2_1.getTitle());
    assert(rep1.getUserRepoLength() == 1);
    assert(rep1.getUserRepoCapacity() == 10);
    assert(rep1[0] == m1);

    try {
        rep1.deleteElementUserRepo(m3.getTitle());
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    UserRepository rep2(rep1);
    assert(rep2.getUserRepoLength() == 1);
    assert(rep2[0] == m1);

    rep2.addElementUserRepo(m3);
    assert(rep2.getUserRepoLength() == 2);
    assert(rep2[1] == m3);

    assert(rep1.getUserRepoLength() == 1);
    try {
        assert(rep1[1] == m3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    UserRepository rep3;
    rep3 = rep2;
    assert(rep3.getUserRepoLength() == 2);
    assert(rep3[1] == m3);

    rep3.deleteElementUserRepo(m3.getTitle());
    assert(rep3.getUserRepoLength() == 1);
    try {
        assert(rep3[1] == m3);
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    assert(rep2.getUserRepoLength() == 2);
    assert(rep2[1] == m3);
}

void testUserService(){
    UserService serv1;

    assert(serv1.getUserServiceLength() == 0);
    assert(serv1.getUserServiceCapacity() == 10);

    serv1.addElementUserService("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
    assert(serv1.getUserServiceLength() == 1);
    assert(serv1.getUserServiceCapacity() == 10);

    try{
        serv1.addElementUserService("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    assert(serv1[0].getTitle() == "Garçon Chiffon");
    assert(serv1[0].getGenre() == "Comedy/Drama");
    assert(serv1[0].getYearOfRelease() == 2020);
    assert(serv1[0].getNrOfLikes() == 0);
    assert(serv1[0].getTrailer() == "https://youtu.be/Ghdso2T9qwA");

    serv1.deleteElementUserService("Garçon Chiffon");
    assert(serv1.getUserServiceLength() == 0);
    assert(serv1.getUserServiceCapacity() == 10);

    try{
        serv1.deleteElementUserService("Chiffon");
    }
    catch (std::string exp) {
//        std::cout << exp << std::endl;
    }

    serv1.addElementUserService("Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM");
    serv1.addElementUserService("Amélie", "Comedy Romance/Love", 2001, 0, "https://youtu.be/HUECWi5pX7o");
    serv1.addElementUserService("Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ");
    serv1.addElementUserService("La science des rêves", "Surrealistic Science Fantasy/Comedy", 2006, 0,"https://youtu.be/dHtE0szIip0");
    serv1.addElementUserService("Irréversible", "Psychological Thriller/Drama", 2002, 0,"https://youtu.be/ZoDtJjqkfxU");
    serv1.addElementUserService("Fallen Angels", "Crime/Drama", 1995, 0, "https://youtu.be/dtum6XVH3HI");
    serv1.addElementUserService("Instinct", "Drama/Thriller", 2019, 0, "https://www.youtube.com/watch?v=0OIetiMoseA");
    serv1.addElementUserService("Love", "Erotic Drama", 2015, 0, "https://youtu.be/62yCdFzP9Mc");
    serv1.addElementUserService("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
    serv1.addElementUserService("Queen of Hearts", "Drama", 2019, 0, "https://youtu.be/MaxIbXW23NA");

    UserService serv2(serv1);
    assert(serv2.getUserServiceLength() == 10);
    assert(serv2.getUserServiceCapacity() == 10);
    assert(serv2[0].getTitle() == "Climax");
    assert(serv2[9].getTitle() == "Queen of Hearts");

    serv2.deleteElementUserService("Climax");
    assert(serv2.getUserServiceLength() == 9);
    assert(serv1.getUserServiceLength() == 10);

    UserService serv3;
    serv3 = serv2;
    assert(serv3.getUserServiceLength() == 9);
    assert(serv3.getUserServiceCapacity() == 10);
    assert(serv2[0].getTitle() == "Queen of Hearts");
}