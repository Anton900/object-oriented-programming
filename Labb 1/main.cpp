//Anton Wallin
//2020-04-06
//Objektorienterad Programmering
//Labb 1

#include "structs.h"
#include "functions.h"

int main() {
    
    std::vector<person> vec_person;

    //Return a vector with people
    vec_person = read_file("names.txt");
    if(vec_person.empty())
    {
        return 0;
    }
    while(true)
    {
        int input;
        size_t name_count;
        std::string name_part;
        std::string city;
        std::vector<person> vec_city;
        input = menu();
        switch(input)
        {
            case 1: 
                std::cout << "Enter name: ";
                std::getline(std::cin, name_part);

                //Return number of matches of people with name part in their name
                name_count = find_in_names(vec_person, name_part);
                std::cout << "There're " << name_count << " people with that part in their name." << "\n";
                break;
            case 2:
                std::cout << "Enter city name: ";
                std::getline(std::cin, city);

                //Return a vector with people from same city as user input
                vec_city = find_person_from_city(vec_person, city);
                std::cout << "\n";

                //Print all people from city
                for(int i = 0; i < vec_city.size(); i++)
                {
                    std::cout << vec_city[i].name << " " << vec_city[i].address.city << "\n";
                }
                break;
            case 3:
                std::cout << "\nClosing program\n";
                return 0;
            default:
                std::cout << "Invalid.\n";
                break;
        }
    }
}