//Anton Wallin
//2020-05-03
//Objektbaserad Programmering
//Labb 3

#include "linked_list.h"
#include "time.h"

void print_list(const linked_list &list);
linked_list merge (linked_list list1, linked_list list2);

int main() {

    linked_list list1;
    linked_list list2;

    srand (time(NULL));

    // Insert 100 random numbers in both lists
    list1.push_back(rand()% 20);
    list2.push_back(rand()% 20);
    for(int i = 0; i < 99; i++)
    {
        list1.push_back(list1.back() + rand()% 20);
        list2.push_back(list2.back() + rand()% 20);
    }   

    // Return value of element at position 50
    double elem1 = list1.at(50);
    double elem2 = list2.at(50);
    std::cout << "List 1 50:th element: " << elem1 << "\nList 2 50:th element: " << elem2 << "\n";

    // Remove the largest element at position 50
    if(elem1 > elem2)
    {
        std::cout << "Removing " << elem1 << " from list 1\n";
        list1.remove(50);
    }
    else if(elem1 < elem2)
    {
        std::cout << "Removing " << elem2 << " from list 2\n";
        list2.remove(50);
    }
    else
        std::cout << "They're equal.\n";

    linked_list list3;
    // Call the "=" operator to assign list1 to list3
    list3 = list1;

    // Remove half of list 3 elements
    for(int i = 0; i < 50; i++)
    {
        list3.pop_back();
        list3.push_front(list3.pop_back());
    }

    std::cout << "\nPrinting list3 with global function\n";
    print_list(list3);

    std::cout << "\n\nList 1: \n";
    list1.print();
    std::cout << "\n\nList 2: \n";
    list2.print();

    auto mergeList = merge(list1, list2);
    std::cout << "\n\nList merge: \n";
    print_list(mergeList);
    
    if(mergeList.is_sorted())
        std::cout << "\n\nmerge is sorted\n";
    else
        std::cout << "\n\nmerge is NOT sorted\n";
    std::cout << "\n";
}

/*
Output content of list
@param values are the list to be printed
*/
void print_list(const linked_list &list)
{
    auto ptr = list.head;
    for(; ptr != nullptr; ptr = ptr->next)
    {
        std::cout << ptr->value << " ";
    }
}
/*
Merge two lists into one list
@param values the two lists to be merged together
@return the new merged list
*/
linked_list merge (linked_list list1, linked_list list2)
{
    linked_list temp;

    while(!list1.is_empty() && !list2.is_empty())
    {
        if(list1.front() < list2.front())
        {
            temp.push_back(list1.pop_front());
        }
        else
        {
            temp.push_back(list2.pop_front());
        }
    }

    while(!list1.is_empty())
        temp.push_back(list1.pop_front());
    while(!list2.is_empty())
        temp.push_back(list2.pop_front());

    return temp;
}
