//
// Created by Alex Campean on 15.03.2022.
//
#pragma once

typedef struct {
    char* name;
    char* continent;
    double population;
} Country;

// Constructor, Destructor

/// <summary>Creates a Country struct with its specific fields</summary>
/// <param name="name">Char*, the name of the country
/// <param name="continent">Char*, the continent which the country belongs to
/// <param name="population">Double, the population of the country
/// <returns>A struct of type Country</returns
Country* createCountry(char* name, char* continent, double population);

/// <summary>Destroys a Country struct along with its specific fields</summary>
/// <param name="country">Country*, the struct to be destroyed
void destroyCountry(Country* country);

// Getters

/// <summary>Returns the "name" field of the country</summary>
/// <param name="country">Country*, the given country</param>
/// <returns>The string associated to the field "name" of the given country</returns
char* getName(Country* country);

/// <summary>Returns the "continent" field of the country</summary>
/// <param name="country">Country*, the given country</param>
/// <returns>The string associated to the field "continent" of the given country</returns
char* getContinent(Country* country);

/// <summary>Returns the "population" field of the country</summary>
/// <param name="country">Country*, the given country</param>
/// <returns>The string associated to the field "population" of the given country</returns
double getPopulation(Country* country);

// Setter

/// <summary>Sets the population field of a Country struct to a given param</summary>
/// <param name="country">Country*, the given Country element</param>
/// <param name="new_population">double, the given population</param>
/// <returns></returns
void setPopulation(Country* country, double new_population);

// Deep Copy

/// <summary>Makes a deep copy of the second struct and puts it into the first one</summary>
/// <param name="country1">Country*, the destination country</param>
/// <param name="country2">Country*, the source country</param>
/// <returns></returns
void makeCountryDeepCopy(Country* country1, Country* country2);

// Copy Country

/// <summary>Returns a copy of a given Country struct</summary>
/// <param name="country">Country*, the given Country struct</param>
/// <returns>A pointer to the copy of the given Country struct</returns
Country* copyCountry(Country* country);

// String Representation

/// <summary>Returns the string representation of a given Country struct</summary>
/// <param name="country">Country*, the given Country struct</param>
/// <param name="string">Char*, the string which the representation of the Country struct will be stored in</param>
/// <returns>A pointer to the string representation of a given Country struct</returns
void toString(Country* country, char* string);
