//Anton Wallin
//2020-05-03
//Objektbaserad Programmering
//Labb 3

#include "linked_list.h"

linked_list::node_t::node_t(double value, node_t * next, node_t * prev)
{
    this->value = value;
    this->next = next;
    this->prev = prev;
}

linked_list::linked_list ()
{
    head = nullptr;
    tail = nullptr;
}
linked_list::linked_list ( const linked_list & src)
{
    head = new linked_list::node_t(src.head->value);
    for(auto rhsPtr = src.head; rhsPtr != nullptr; rhsPtr = rhsPtr->next)
    {
        if(rhsPtr->next != nullptr)
        {
            push_back(rhsPtr->next->value);
        }
    }
}
linked_list::~ linked_list ()
{
    // Delete memory
    while(!is_empty())
        pop_front();
}
/*
Assign list to another list
@param values are list to be assigned
@return the new list
*/
linked_list & linked_list::operator=( const linked_list & rhs )
{
    
    // Delete content of list if it's not empty
    while(!is_empty())
        pop_front();

    auto ptr = rhs.head;
    for(; ptr != nullptr; ptr = ptr->next)
    {
        push_back(ptr->value);
    }
    return *this;
}
/*
Add elements to the back
@param values are list to be added
@return the new list
*/
linked_list & linked_list::operator +=( const linked_list & rhs)
{
    auto ptr = rhs.head;
    if(rhs.is_empty())
        return *this;
    for(; ptr != nullptr; ptr = ptr->next)
    {
        push_back(ptr->value);
    }
    return *this;
}
/*
Add element with value at specficied postion
@param values are value to be added and at which position
*/
void linked_list::insert ( double value , size_t pos)
{
    // If position doesn't exist, throw exception
    if(pos >= size() || pos < 0)
    {
        throw std::out_of_range(std::string("error: list isn't that large"));
    }
    auto ptr = head;
    int index = 0;

    // Search the node until either reached the end or found the position
    for(; ptr != 0 && pos != index; ptr = ptr->next)
        index++;
    auto node = new linked_list::node_t(value);
    // If not first position
    if(ptr->prev != nullptr)
    {
        node->next = ptr;
        node->prev = ptr->prev;
        ptr->prev->next = node;
        ptr->prev = node;
    }
    // If first position
    else
    {
        node->next = ptr;
        node->prev = nullptr;
        ptr->prev = node;
        head = node;
    }
}
/*
Add elements to the front
@param values are value to be added to element
*/
void linked_list::push_front ( double value )
{
    // If empty add the first element
    if(is_empty())
    {
        auto node = new linked_list::node_t(value);
        node->prev = nullptr;
        head = node;
        tail = head;
    }
    // If not empty add element at first position.
    else
    {
        auto ptr = head;
        // Go to last element and assign tail pointer to it
        for(; ptr->next != 0; ptr = ptr->next);
        tail = ptr;
        // Add new element at front
        auto *node = new linked_list::node_t(value);
        node->next = head;
        head->prev = node;
        head = node;
    }
}
/*
Add elements to the back
@param values are value to be added to element
*/
void linked_list::push_back ( double value )
{
    // If empty add first element
    if(is_empty())
    {
        auto node = new linked_list::node_t(value);
        head = node;
        tail = head;
    }
    // If not empty add element after the last position.
    else
    {
        auto ptr = head;
        // Go to last element and assign tail pointer to it
        for(; ptr->next != 0; ptr = ptr->next);
        tail = ptr;
        // Add new element at back and and assign tail pointer to it
        auto node = new linked_list::node_t(value);
        node->prev = tail;
        node->next = nullptr;
        tail->next = node;
        tail = node;
    }
}
/*
Access the front element
@return return value of front element
*/
double linked_list::front () const
{
    return head->value;
}
/*
Access the back element
@return return value of back element
*/
double linked_list::back () const
{
    return tail->value;
}
/*
Access the specificed element
@param values are position to find element
@return return value of specificd element
*/
double linked_list::at( size_t pos) const
{
    // If position doesn't exist, throw exception
    if(pos >= size() || pos < 0) {throw std::out_of_range(std::string("error: position doesn't exist"));}
    auto node = head;
    int listPos = 0;
    // Search the node until either reached the end or found the position
    for(; node != 0 && listPos != pos; node = node->next)
        listPos++;
    return node->value;
}
/*
Delete the specificed element
@param values are position to find element
*/
void linked_list::remove ( size_t pos)
{
    auto node = head;
    int listPos = 0;

    // Search until end of list or found position
    for(; node != 0 && listPos != pos; node = node->next)
        listPos++;
    if(listPos != pos)
    {
        std::cout << "Position doesn't exist\n";
        return;
    }
    // If it's not the front element
    if(node->prev != nullptr)
    {
        // If it's not the back element
        if(node->next != nullptr)
        {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        // If it's the back element
        else
        {
            node->prev->next = node->next;
            tail = node->prev;
        }

    }
    // If it's the front element
    else
    {
        head = node->next;
        head->prev = nullptr;
    }
    delete node;
}
/*
Access and delete front element
@return value of front element
*/
double linked_list::pop_front ()
{
    double value;
    if(head != nullptr)
    {
        value = head->value;
        auto ptr = head;
        if(head->next == nullptr)
            head = 0;
        else
        {
            head = head->next;
            head->prev = 0;
        }
        delete ptr;
    }
    else{
        throw (std::string("List is empty, can't return value"));
    }
    return value;
}
/*
Access and delete back element
@return value of back element
*/
double linked_list::pop_back ()
{
    double value;
    if(tail != nullptr)
    {
        value = tail->value;
        auto ptr = tail;
        tail = tail->prev;
        tail->next = 0;
        delete ptr;
    }
    else{
        throw (std::string("List is empty, can't return value"));
    }
    return value;
}
/*
Access size of list (number of elements)
@return value of size of the list
*/
size_t linked_list::size () const
{
    size_t size = 0;
    if(head != nullptr)
    {
        // Increment size for every element
        for(auto ptr = head; ptr != 0; ptr = ptr->next)
        {
            size++;
        }
    }
    return size;
}
/*
Find out if list is empty or not
@return true of false
*/
bool linked_list::is_empty () const
{
    if(head != nullptr)
        return false;
    return true;
}
/*
Output content of list
*/
void linked_list::print () const
{
    for(auto ptr = head; ptr != 0; ptr = ptr->next)
    {
        std::cout << ptr->value << " ";
    }
}
/*
Output content of list in reverse
*/
void linked_list::print_reverse () const
{   
    for(auto ptr = tail; ptr != 0; ptr = ptr->prev)
    {
        std::cout << ptr->value << " ";
    }
}
/*
Find out if value of the elements are sorted
@return true of false
*/
bool linked_list::is_sorted () const
{
    auto* ptr = head;
    for(; ptr->next != nullptr; ptr = ptr->next)
    {  
        if(ptr->value > ptr->next->value)
            return false;
    }
    return true;
}