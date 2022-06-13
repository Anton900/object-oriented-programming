#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct location {

    std::string street;
    std::string city;
    int zip;

};

struct person {

    std::string name;
    std::string id;
    location address;

};

#endif