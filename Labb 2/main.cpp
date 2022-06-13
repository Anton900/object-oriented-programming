//Anton Wallin
//2020-04-29
//Objektbaserad Programmering
//Labb 2

#include <iostream>

int main() {

    int8_t* pointer = 0;
    unsigned int KiB = 1024;
    size_t GiB = 1024 * 1024 * 1024;
    size_t kib_amount = 0;
    size_t gib_amount = 0;
    try {
        while (true)
        {
            std::cout << "\nMenu\n";
            std::cout << "1. Allocate memory in KiB\n"
                << "2. Allocate memory in GiB\n"
                << ": ";
            int input;
            std::cin >> input;

            // Allocate one KiB at the time until failure
            while (input == 1)
            {
                pointer = new int8_t[KiB];
                kib_amount++;
            }

            // Allocate one GiB at the time until failure
            while (input == 2)
            {
                pointer = new int8_t[GiB];
                gib_amount++;
            }


        }
    }
    catch (const std::bad_alloc& e) {
        std::cerr << e.what() << std::endl;
    }

    size_t kib_allocated = kib_amount * KiB;
    size_t gib_allocated = gib_amount * GiB;

    if (kib_amount != 0)
        std::cout << "KiB Allocated: " << kib_allocated / KiB << " KiB\n";
    else
        std::cout << "GiB Allocated: " << gib_allocated / GiB << " GiB\n";

    system("pause");
    delete[] pointer;

    return 0;

}