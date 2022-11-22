#include "Service.h"

Service::Service() {
    this->repo = new Repository{"Database.txt"};
}

std::vector<Weather> Service::getDataBase() const {
    return this->repo->getDataBase();
}

std::vector<std::string> Service::getDescriptions() const{
    return this->repo->getDescriptions();
}

Service &Service::operator=(const Service& service) {
    this->repo = service.repo;
    return *this;
}

void Service::addToDataBase(const std::string& givenStartHour, const std::string& givenEndHour, const std::string& givenPrecipitation, const std::string& givenDescription) {
    // TODO: VALIDATION
    Weather w(std::stoi(givenStartHour), std::stoi(givenEndHour), std::stoi(givenPrecipitation), givenDescription);
    this->repo->addWeather(w);
}

std::vector<Weather> Service::filterDataBasePrecipitation(int providedPrecipitation) const {
    std::vector<Weather> dataBase = this->getDataBase();
    std::vector<Weather> filteredWeathers;
    std::for_each(dataBase.begin(), dataBase.end(),[&filteredWeathers, &providedPrecipitation](auto &it){ if (it.getPrecipitation() < providedPrecipitation)  filteredWeathers.push_back(it);});

    return filteredWeathers;
}

std::vector<Weather> Service::filterDataBaseDescription(const std::vector<std::string>& providedDescription) const {
    std::vector<Weather> dataBase = this->getDataBase();
    std::vector<Weather> filteredWeathers;
    for (auto &it : dataBase) {
        for (auto &descriptionsIt : providedDescription) {
            if (it.getDescription() == descriptionsIt)
                filteredWeathers.push_back(it);
        }
    }

    return filteredWeathers;
}


