//
// Created by lblaga on 19.03.2020.
//

#include "List.h"
#include <stdexcept>

List::List ()
{

}

List::List (std::vector<int> const &args)
{
    for (int arg : args)
        this -> push_back (arg);
}

List::~List ()
{
    node *to_be_deleted;
    while (head)
    {
        to_be_deleted = head;
        head = head -> next;
        delete to_be_deleted;
    }
}

int &List::operator[] (size_t my_index) const
{
    if (my_index < 0 || my_index > this -> count - 1)
        throw std::out_of_range ("Index out of range.");
    return (this -> find_by_index (my_index)) -> value;
}

List &List::operator>> (int new_value)
{
    this -> push_back (new_value);
    return (*this);
}

List &List::operator+ (List const &second_list)
{
    auto *return_list = new List;
    for (int i = 0; i < this -> size (); i++)
        return_list -> push_back (this -> index (i));
    for (int i = 0; i < second_list . size (); i++)
        return_list -> push_back (second_list . index (i));
    return *return_list;
}

std::ostream &operator<< (std::ostream &os, const List &myList)
{
    std::cout << "From head to tail: ";
    for (int i = 0; i < myList . size (); i++)
        os << myList . index (i) << " ";
    std::cout << std::endl;

    std::cout << "From tail to head: ";
    for (int i = myList.size () - 1; i >= 0; i--)
        os << myList . index (i) << " ";
    std::cout << std::endl;

    return os;
}

void List::insert (int new_value, size_t my_index)
{
    if (count == 0 || my_index <= 0)
        return this -> push_front (new_value);
    if (my_index >= count)
        return this -> push_back (new_value);
    (this -> count)++;
    node *new_node = this -> find_by_index (my_index - 1);
    new_node -> next -> prev = new node;
    new_node -> next -> prev -> next = new_node -> next;
    new_node -> next -> prev -> prev = new_node;
    new_node -> next -> prev -> value = new_value;
    new_node -> next = new_node -> next -> prev;
}

void List::push_front (int new_value)
{
    (this -> count)++;
    if (head)
    {
        node *new_node = new node;
        new_node -> prev = nullptr;
        new_node -> next = head;
        new_node -> value = new_value;
        head -> prev = new_node;
        head = new_node;
    }
    else
    {
        tail = head = new node;
        head -> next = head -> prev = nullptr;
        head -> value = new_value;
    }
}

void List::push_back (int new_value)
{
    (this -> count)++;
    if (tail)
    {
        node *new_node = new node;
        new_node -> next = nullptr;
        new_node -> prev = tail;
        new_node -> value = new_value;
        tail -> next = new_node;
        tail = new_node;
    }
    else
    {
        tail = head = new node;
        head -> next = head -> prev = nullptr;
        head -> value = new_value;
    }
}

size_t List::size () const
{
    return this -> count;
}

int List::index (size_t my_index) const
{
    return (*this)[my_index];
}

int List::front ()
{
    if (head)
        return head -> value;
    throw std::out_of_range ("Index out of range.");
}

int List::back ()
{
    if (tail)
        return tail -> value;
    throw std::out_of_range ("Index out of range.");
}

void List::pop (size_t my_index)
{
    if (my_index < 0 || my_index > this -> count - 1)
        throw std::out_of_range ("Index out of range.");
    if (my_index == 0)
        return pop_front ();
    if (my_index == this -> count - 1)
        return pop_back ();
    node *to_be_deleted = find_by_index (my_index);
    to_be_deleted -> prev -> next = to_be_deleted -> next;
    to_be_deleted -> next -> prev = to_be_deleted -> prev;
    (this -> count)--;
    delete to_be_deleted;
}

void List::pop_back ()
{
    if (count)
    {
        (this -> count)--;
        node *to_be_deleted = tail;
        tail = tail -> prev;
        delete to_be_deleted;
        if (!count)
            head = nullptr;
    }
}

void List::pop_front ()
{
    if (count)
    {
        (this -> count)--;
        node *to_be_deleted = head;
        head = head -> next;
        delete to_be_deleted;
        if (!count)
            tail = nullptr;
    }
}

List::node *List::find_by_index (size_t my_index) const
{
    bool start_node = my_index <= (this -> count) / 2;
    node *curr_node = start_node ? this -> head : this -> tail;
    my_index = start_node ? my_index : count - my_index - 1;
    while (my_index--)
        curr_node = start_node ? curr_node -> next : curr_node -> prev;
    return curr_node;
}

size_t List::find (int needle)
{
    node *curr_node = head;
    size_t curr_index = 0;
    while (curr_node)
        if (curr_node -> value == needle)
            return curr_index;
        else
        {
            curr_node = curr_node -> next;
            curr_index++;
        }
    return -1;
}
