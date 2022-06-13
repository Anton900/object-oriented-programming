#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

std::istream& operator >> (std::istream &in, person &persons);
std::vector <person> read_file(std::string filename);
std::vector<person> find_person_from_city(std::vector<person> &haystack, std::string city);
size_t find_in_names(std::vector<person> &persons, std::string name_part);
void to_lower(std::string &s);
int menu ();

#endif