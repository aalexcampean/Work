#pragma once
#include "../Repository/Repository.h"

class Service {
private:
    Repository* repo;

public:
    Service();
    ~Service(){};

    std::vector<Weather> getDataBase() const;
    std::vector<std::string> getDescriptions() const;
    Service& operator=(const Service&);

    void addToDataBase(const std::string&, const std::string &, const std::string &, const std::string &);
    std::vector<Weather> filterDataBasePrecipitation(int) const;
    std::vector<Weather> filterDataBaseDescription(const std::vector<std::string>&) const;
};

