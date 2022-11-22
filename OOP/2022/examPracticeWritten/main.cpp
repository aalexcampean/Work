//
// Created by Alex Campean on 11.06.2022.
//

#include <string>
#include <vector>
#include <numeric>

template<typename T>
T fct(std::vector<T> vector) {
    if (vector.empty()) {
        throw std::exception();
    }
    T sum = vector[0];
    std::for_each(vector.begin() + 1, vector.end(), [&sum](auto &item) {
        sum += item;
    });
    return sum;
}

template<typename T>
T fct2(std::vector<T> vector) {
    if (vector.empty()) {
        throw std::exception();
    }
    T greatest = vector[0];
    std::for_each(vector.begin() + 1, vector.end(), [&greatest](auto &item) {
        if (item > greatest) greatest = item;
    });
    return greatest;
}

void testFct() {
    std::vector<int> v1{4, 2, 1, -4};
    assert(fct<int>(v1) == 3);
    std::vector<int> v2;

    try {
        fct<int>(v2);
        assert(false);
    }
    catch (std::exception &) {
        assert(true);
    }

    std::vector<double> v3{2, 10.5, 5, -10};
    assert(fct<double>(v3) == 7.5);

    std::vector<std::string> v4{"y", "q", "a", "m"};
    assert(fct<std::string>(v4) == "yqam");
}

void testFct2() {
    std::vector<int> v1{4, 2, 1, 6, 3, -4};
    assert(fct2<int>(v1) == 6);
    std::vector<int> v2;

    try {
        fct2<int>(v2);
        assert(false);
    }
    catch (std::exception &) {
        assert(true);
    }

    std::vector<double> v3{2, 10.5, 6.33, -100, 9, 1.212};
    assert(fct2<double>(v3) == 10.5);

    std::vector<std::string> v4{"y", "q", "a", "m"};
    assert(fct2<std::string>(v4) == "y");
}

int main(int argc, char *argv[]) {
    testFct();
    testFct2();
    return 0;
}