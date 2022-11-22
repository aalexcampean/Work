//
// Created by Alex Campean on 16.03.2022.
//

#include "Country.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Country* createCountry(char* name, char* continent, double population){
    Country* country = (Country*)malloc(sizeof(Country));

    country->name = (char*)malloc(sizeof(char) * 20);
    strcpy(country->name, name);

    country->continent = (char*)malloc(sizeof(char) * 50);
    strcpy(country->continent, continent);

    country->population = population;

    return country;
}

void destroyCountry(Country* country){
    if (country == NULL){
        return;
    }
    free(country->name);
    free(country->continent);

    free(country);
    country = NULL;
}

//Getters

char* getName(Country* country) {
    return country->name;
}

char* getContinent(Country* country) {
    return country->continent;
}

double getPopulation(Country* country) {
    return country->population;
}

// Setter

void setPopulation(Country* country, double new_population) {
    country->population = new_population;
}

// Deep Copy

void makeCountryDeepCopy(Country* country1, Country* country2) {
    if (country1->name == NULL || country2->name == NULL){
        country1->name = country2->name;
    }
    else{
        strcpy(country1->name, getName(country2));
    }
    if (country1->continent == NULL || country2->continent == NULL){
        country1->continent = country2->continent;
    }
    else{
        strcpy(country1->continent, getContinent(country2));
    }
    country1->population = getPopulation(country2);
}

// Copy Country

Country* copyCountry(Country* country) {
    return createCountry(getName(country), getContinent(country), getPopulation(country));
}

// String Representation

void toString(Country* country, char* string) {
    sprintf(string,
            "Name: %s  |  Continent: %s  |  Population: %lf millions",
            country->name,
            country->continent,
            country->population);
}