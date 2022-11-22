#include <string.h>

// The Structure

typedef struct{

    char* type;
    char* address;
    double surface;
    double price;

} Estate;

// Constructor, Destructor

/// <summary>Creates an Estate element with specific fields</summary>
/// <param name="type">Char*, the type of estate
/// <param name="address">Char*, the address of estate
/// <param name="surface">Double, the surface of estate
/// <param name="price">Double, the price of estate</param>
/// <returns>An element of type Estate</returns
Estate* createEstate(char* type, char* address, double surface, double price);

/// <summary>Destroys an Estate element with specific fields</summary>
/// <param name="type">Char*, the type of estate
/// <param name="address">Char*, the address of estate
/// <param name="surface">Double, the surface of estate
/// <param name="price">Double, the price of estate</param>
/// <returns>An element of type Estate</returns
void destroyEstate(Estate* e);

// Getters

/// <summary>Returns the "type" field of the Estate element</summary>
/// <param name="e">Estate*, the given Estate element</param>
/// <returns>The string associated to the field "type" of the given Estate element</returns
char* getType(Estate* e);

/// <summary>Returns the "address" field of the Estate element</summary>
/// <param name="e">Estate*, the given Estate element</param>
/// <returns>The string associated to the field "address" of the given Estate element</returns
char* getAddress(Estate* e);

/// <summary>Returns the "surface" field of the Estate element</summary>
/// <param name="e">Estate*, the given Estate element</param>
/// <returns>The double associated to the field "surface" of the given Estate element</returns
double getSurface(Estate* e);

/// <summary>Returns the "price" field of the Estate element</summary>
/// <param name="e">Estate*, the given Estate element</param>
/// <returns>The double associated to the field "price" of the given Estate element</returns
double getPrice(Estate* e);

// Setter

/// <summary>Sets the non unique fields of an estate element to the given params</summary>
/// <param name="e">Estate*, the given Estate element</param>
/// <param name="given_type">char*, the given type</param>
/// <param name="given_surface">double, the given surface</param>
/// <param name="given_price">double, the given price</param>
/// <returns></returns
void setNonUniqueAttributes(Estate* e, char* given_type, double given_surface, double given_price);

// Make Estate Deep Copy

/// <summary>Makes a deep copy of the second element and puts it into the first one</summary>
/// <param name="e_1">Estate*, the destination estate</param>
/// <param name="e_2">Estate*, the source estate</param>
/// <returns></returns
void makeEstateDeepCopy(Estate* e_1, Estate* e_2);

// Copy Estate

/// <summary>Returns a copy of a given Estate element</summary>
/// <param name="e">Estate*, the given Estate element</param>
/// <returns>A pointer to the copy of the given Estate element</returns
Estate* copyEstate(Estate* e);

// String Representation

/// <summary>Returns the string representation of a given Estate element</summary>
/// <param name="e">Estate, the given Estate element
/// <param name="string">Char*, the string which the representation of the Estate element will stored in</param>
/// <returns>A pointer to the string representation of a given Estate element</returns
void toString(Estate* e, char* string);