//#include "Tests.h"
//#include "../Service/AdminService.h"
//#include "../Service/UserService.h"
//#include "../Exception/CustomException.h"
//
//void testAll() {
//    testEntity();
//    testRepository();
//    testAdminService();
//    testUserService();
//}
//
//void testEntity() {
//    Movie m1{};
//    Movie m2{"Arsène Lupin", "Adventure/Love", 2004, 0, "https://youtu.be/5owbso3KJf4"};
//
//    assert(m1.getTitle().empty());
//    assert(m1.getGenre().empty());
//    assert(m1.getYearOfRelease() == 0);
//    assert(m1.getNrOfLikes() == 0);
//    assert(m1.getTrailer().empty());
//
//    assert(m2.getTitle() == "Arsène Lupin");
//    assert(m2.getGenre() == "Adventure/Love");
//    assert(m2.getYearOfRelease() == 2004);
//    assert(m2.getNrOfLikes() == 0);
//    assert(m2.getTrailer() == "https://youtu.be/5owbso3KJf4");
//
//    Movie m3{m2};
//
//    assert((m2 == m3) == true);
//
//    assert(m3.getTitle() == "Arsène Lupin");
//    assert(m3.getGenre() == "Adventure/Love");
//    assert(m3.getYearOfRelease() == 2004);
//    assert(m3.getNrOfLikes() == 0);
//    assert(m3.getTrailer() == "https://youtu.be/5owbso3KJf4");
//
//    m2.setNonUniqueAttributes("Drama", 2017, 10, "https://youtu.be/2fhO2A4SL24");
//    assert(m2.getGenre() == "Drama");
//    assert(m2.getYearOfRelease() == 2017);
//    assert(m2.getNrOfLikes() == 10);
//    assert(m2.getTrailer() == "https://youtu.be/2fhO2A4SL24");
//
//
//    Movie m4;
//    m4 = m3;
//    assert(m4.getTitle() == "Arsène Lupin");
//    assert(m4.getGenre() == "Adventure/Love");
//    assert(m4.getYearOfRelease() == 2004);
//    assert(m4.getNrOfLikes() == 0);
//    assert(m4.getTrailer() == "https://youtu.be/5owbso3KJf4");
//
////    std::cout << m4 << std::endl;
//}
//
//void testRepository() {
//
//    MemoryRepo rep1;
//    assert(rep1.getLength() == 0);
//
//    // test add
//
//    Movie m1{"Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM"};
//    rep1.addElement(m1);
//    assert(rep1.getLength() == 1);
//    assert(rep1[0] == m1);
//
//    Movie m2{"Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ"};
//    rep1.addElement(m2);
//    assert(rep1.getLength() == 2);
//    assert(rep1[1] == m2);
//
//    try {
//        rep1.addElement(m1);
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    // test update
//
//    Movie m2_1{"Little Joe", "SF/Drama", 2018, 10, "https://youtu.be/eYfKlNBLLeQ"};
//    rep1.updateElement(m2_1);
//    assert(rep1[1] == m2_1);
//
//    Movie m3{"Irréversible", "Psychological Thriller/Drama", 2002, 0, "https://youtu.be/ZoDtJjqkfxU"};
//    try {
//        rep1.updateElement(m3);
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    // test delete
//
//    rep1.deleteElement(m2_1.getTitle());
//    assert(rep1.getLength() == 1);
//    assert(rep1[0] == m1);
//
//    try {
//        rep1.deleteElement(m3.getTitle());
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    MemoryRepo rep2(rep1);
//    assert(rep2.getLength() == 1);
//    assert(rep2[0] == m1);
//
//    rep2.addElement(m3);
//    assert(rep2.getLength() == 2);
//    assert(rep2[1] == m3);
//
//    assert(rep1.getLength() == 1);
//
//    MemoryRepo rep3;
//    rep3 = rep2;
//    assert(rep3.getLength() == 2);
//    assert(rep3[1] == m3);
//
//    rep3.deleteElement(m3.getTitle());
//    assert(rep3.getLength() == 1);
//
//
//    assert(rep2.getLength() == 2);
//    assert(rep2[1] == m3);
//
////    std::cout << rep2;
//
//}
//
//void testAdminService() {
//
//    AdminService serv1;
//
//    assert(serv1.getLength() == 0);
//
//    serv1.addElement("Garçon Chiffon", "Comedy/Drama", "2020", "0", "https://youtu.be/Ghdso2T9qwA");
//    assert(serv1.getLength() == 1);
//
//    try{
//        serv1.addElement("Garçon Chiffon", "Comedy/Drama", "2020", "0", "https://youtu.be/Ghdso2T9qwA");
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    assert(serv1[0].getTitle() == "Garçon Chiffon");
//    assert(serv1[0].getGenre() == "Comedy/Drama");
//    assert(serv1[0].getYearOfRelease() == 2020);
//    assert(serv1[0].getNrOfLikes() == 0);
//    assert(serv1[0].getTrailer() == "https://youtu.be/Ghdso2T9qwA");
//
//    serv1.updateElement("Garçon Chiffon", "Comedy/Drama", "2020", "30", "https://youtu.be/Ghdso2T9qwA");
//    assert(serv1[0].getNrOfLikes() == 30);
//
//    try{
//        serv1.updateElement("Chiffon", "Comedy/Drama", "2020", "30", "https://youtu.be/Ghdso2T9qwA");
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    serv1.deleteElement("Garçon Chiffon");
//    assert(serv1.getLength() == 0);
//
//    try{
//        serv1.deleteElement("Chiffon");
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    serv1.firstMovies();
//    assert(serv1.getLength() == 10);
//
//    AdminService serv2(serv1);
//    assert(serv2.getLength() == 10);
//    assert(serv2[0].getTitle() == "Climax");
//    assert(serv2[9].getTitle() == "Queen of Hearts");
//
//    serv2.deleteElement("Climax");
//    assert(serv2.getLength() == 9);
//    assert(serv1.getLength() == 10);
//
//    AdminService serv3;
//    serv3 = serv2;
//    assert(serv3.getLength() == 9);
//    assert(serv3[0].getTitle() == "Amélie");
//
//    serv3.updateElement("Amélie", "Comedy Romance/Love", "2001", "10", "https://youtu.be/HUECWi5pX7o");
//    assert(serv3[0].getTitle() == "Amélie");
//    assert(serv3[0].getNrOfLikes() == 10);
//    assert(serv2[0].getTitle() == "Amélie");
//    assert(serv2[0].getNrOfLikes() == 0);
//
//    Movie m1("Amélie", "Comedy Romance/Love", 2001, 10, "https://youtu.be/HUECWi5pX7o");
//    assert(serv2.getElementByTitle("Amélie") == m1);
//
//
//    // test copy database
//
//    std::vector<Movie> new_list1;
//
//    new_list1 = serv2.copyDatabase("Psychological Thriller/Drama");
//    assert(new_list1.size() == 1);
//
//    std::vector<Movie> new_list2;
//    new_list2 = serv3.copyDatabase("");
//    assert(new_list2.size() == 9);
//
////    std::cout << serv3 << std::endl;
////    std::cout << serv2 << std::endl;
//
//}
//
//void testUserService(){
//    UserService serv1;
//
//    assert(serv1.getLength() == 0);
//
//    serv1.addElement("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
//    assert(serv1.getLength() == 1);
//
//    try{
//        serv1.addElement("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
//    }
//    catch (CustomException& e) {
////        std::cout << exp << std::endl;
//    }
//
//    assert(serv1[0].getTitle() == "Garçon Chiffon");
//    assert(serv1[0].getGenre() == "Comedy/Drama");
//    assert(serv1[0].getYearOfRelease() == 2020);
//    assert(serv1[0].getNrOfLikes() == 0);
//    assert(serv1[0].getTrailer() == "https://youtu.be/Ghdso2T9qwA");
//
//    serv1.deleteElement("Garçon Chiffon");
//    assert(serv1.getLength() == 0);
//
//    try{
//        serv1.deleteElement("Chiffon");
//    }
//    catch (std::string exp) {
////        std::cout << exp << std::endl;
//    }
//
//    serv1.addElement("Climax", "Horror/Musical", 2018, 0, "https://youtu.be/gNp0jlfbgqM");
//    serv1.addElement("Amélie", "Comedy Romance/Love", 2001, 0, "https://youtu.be/HUECWi5pX7o");
//    serv1.addElement("Little Joe", "SF/Drama", 2018, 0, "https://youtu.be/eYfKlNBLLeQ");
//    serv1.addElement("La science des rêves", "Surrealistic Science Fantasy/Comedy", 2006, 0,"https://youtu.be/dHtE0szIip0");
//    serv1.addElement("Irréversible", "Psychological Thriller/Drama", 2002, 0,"https://youtu.be/ZoDtJjqkfxU");
//    serv1.addElement("Fallen Angels", "Crime/Drama", 1995, 0, "https://youtu.be/dtum6XVH3HI");
//    serv1.addElement("Instinct", "Drama/Thriller", 2019, 0, "https://www.youtube.com/watch?v=0OIetiMoseA");
//    serv1.addElement("Love", "Erotic Drama", 2015, 0, "https://youtu.be/62yCdFzP9Mc");
//    serv1.addElement("Garçon Chiffon", "Comedy/Drama", 2020, 0, "https://youtu.be/Ghdso2T9qwA");
//    serv1.addElement("Queen of Hearts", "Drama", 2019, 0, "https://youtu.be/MaxIbXW23NA");
//
//    UserService serv2(serv1);
//    assert(serv2.getLength() == 10);
//    assert(serv2[0].getTitle() == "Climax");
//    assert(serv2[9].getTitle() == "Queen of Hearts");
//
//    serv2.deleteElement("Climax");
//    assert(serv2.getLength() == 9);
//    assert(serv1.getLength() == 10);
//
//    UserService serv3;
//    serv3 = serv2;
//    assert(serv3.getLength() == 9);
//    assert(serv2[0].getTitle() == "Amélie");
//
//    assert(serv2.findElement("Climax") == false);
//    assert(serv3.findElement("Little Joe") == true);
//
////    std::cout << serv3 << std::endl;
////    std::cout << serv2 << std::endl;
//}