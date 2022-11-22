#include "Estate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constructor, Destructor

Estate* createEstate(char* type, char* address, double surface, double price){
    Estate* e = (Estate*)malloc(sizeof(Estate));

    e->type = (char*)malloc(sizeof(char) * 20);
    strcpy(e->type, type);

    e->address = (char*)malloc(sizeof(char) * 50);
    strcpy(e->address, address);

    e->surface = surface;
    e->price = price;

    return e;
}

void destroyEstate(Estate* e){
    if (e == NULL){
        return;
    }
    free(e->type);
    free(e->address);

    free(e);
    e = NULL;
}


// Getters

char* getType(Estate* e){
    return e->type;
}

char* getAddress(Estate* e){
    return e->address;
}

double getSurface(Estate* e){
    return e->surface;
}

double getPrice(Estate* e){
    return e->price;
}

// Setter

void setNonUniqueAttributes(Estate* e, char* given_type, double given_surface, double given_price){
    strcpy(e->type, given_type);
    e->surface = given_surface;
    e->price = given_price;
}

// Make Estate Deep Copy

void makeEstateDeepCopy(Estate* e_1, Estate* e_2){
    if (e_1->type == NULL || e_2->type == NULL){
        e_1->type = e_2->type;
    }
    else{
        strcpy(e_1->type, getType(e_2));
    }
    if (e_1->address == NULL || e_2->address == NULL){
        e_1->address = e_2->address;
    }
    else{
        strcpy(e_1->address, getAddress(e_2));
    }
    e_1->surface = getSurface(e_2);
    e_1->price = getPrice(e_2);
}

// Copy Estate

Estate* copyEstate(Estate* e){
    return createEstate(e->type, e->address, e->surface, e->price);
}

// String Representation

void toString(Estate* e, char* string){
    sprintf(string, "Type: %s  |  Address: %s  |  Surface: %lf square meters  |  Price: %lf lei", e->type, e->address, e->surface, e->price);
}