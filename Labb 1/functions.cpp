#include "structs.h"
#include "functions.h"

//The operators purpose is how to extract to objects of the type person.
//The parameters are the istream object and the object type person.
std::istream& operator >> (std::istream &in, person &persons) {
    
        std::string address, zip, zip2, city;
        std::getline(in, persons.name);
        std::getline(in, persons.id);
        std::getline(in, persons.address.street, ',');
        std::getline(in, address);

        //If file has reached the end
        if(in.eof())
        {
            return in;
        }
        std::istringstream instream;
        instream.str(address);
        instream >> zip >> zip2;
        zip = zip + zip2;
        std::string word;
        while(instream >> word)
        {
            city += word + " ";
            
        }
        int last_char = city.size() - 1;
        //Remove the space on the last word of city
        city.erase(last_char, 1);

        persons.address.zip = stoi(zip);
        persons.address.city = city;

        return in;
}

//The functions purpose is to read from file and insert into object with type person, using the istream operator.
//The parameters is a string, the filename to be opened.
//The return value is the vector with type person.
std::vector <person> read_file(std::string filename) {

    std::ifstream inFile(filename);
    person P;
    std::vector <person> persons;
    if(inFile.fail())
    {
        std::cout << "Couldn't open file. Closing program.\n";
        return persons;
    }
    while(inFile >> P)
    {   
        persons.push_back(P);
    }
    inFile.close();
    return persons;
}

//The functions purpose is to return all the people with the same city as the input from user.
//The parameters are a vector of type person and string.
//The return value is a vector of type person.
std::vector<person> find_person_from_city(std::vector<person> &haystack, std::string city)
{
    to_lower(city);
    std::vector<person> found_in_city;

    for(int i = 0; i < haystack.size(); i++)
    {
        std::string tmp = haystack[i].address.city;

        to_lower(tmp);

        if(city == tmp)
        {
            found_in_city.push_back(haystack[i]);
        }
    }
    return found_in_city;
}

//The functions purpose is to return the number of matches of people that has the input from the user in their name
//The parameters are a vector with type person and a string.
//The return value is a size_t with the number of matches.
size_t find_in_names(std::vector<person> &persons, std::string name_part) {

    to_lower(name_part);
    size_t name_count = 0;

    for(int i = 0; i < persons.size(); i++)
    {
        std::string tmp = persons[i].name;
        to_lower(tmp);
        if(tmp.find(name_part) != std::string::npos)
        {
            name_count++;
        }
    }
    return name_count;
}

//The functions purpose is to transform the string to lower case letters, including swedish letters.
//The parameters is a string. It's pass-by-reference.
void to_lower(std::string &s)
{

    transform(s.begin(), s.end(), s.begin(), ::tolower);
    for(int i = 0; i < s.size(); i++)
    {   
        size_t found = s.find("Å");
        if(found != std::string::npos)
        {
            s.replace(found, 2, "å");
        }
        found = s.find("Ä");
        if(found != std::string::npos)
        {
            s.replace(found, 2, "ä");
        }
        found = s.find("Ö");
        if(found != std::string::npos)
        {
            s.replace(found, 2, "ö");
        }

    }   

}

//The functions purpose is to print the menu text and ask for input from user.
//It returns the user's input as a interger, if it's valid.
int menu () {

    std::cout << "\n1 - Search part of a personsname.\n"
              << "2 - Search cities.\n"
              << "3 - Exit.\n"
              << "Enter number: ";
    std::string str;
    std::getline(std::cin, str);

    //The string input can't be more then one character and the first character can't be a non-digit.
    while(str.size() > 1 || !isdigit(str[0]))
    {
        std::cout << "Invalid.\n\n";
        std::cout << "Enter number: ";
        std::getline(std::cin, str);
    }
    int input = stoi(str);
    return input;
    
}