#pragma once
#include "../Domain/Weather.h"
#include <string>
#include <vector>

class Repository {
private:
    std::string file_name;
    std::vector<Weather> db;

    void load();
    void save();

public:
    Repository(){};
    Repository(const std::string&);
    Repository(const Repository&);
    ~Repository(){};

    std::vector<Weather> getDataBase() const;
    std::vector<std::string> getDescriptions() const;

    Weather& operator[](int);
    Repository& operator=(const Repository&);

    friend std::ostream& operator<<(std::ostream&, const Repository &);

    void addWeather(Weather&);
};

inline std::ostream& operator<<(std::ostream& stream, const Repository &repo) {
    for (auto& it : repo.db) {
        stream << it << "\n";
    }
    return stream;
}