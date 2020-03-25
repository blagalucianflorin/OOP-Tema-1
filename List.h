//
// Created by lblaga on 19.03.2020.
//

#ifndef TEMA_1_LIST_H
#define TEMA_1_LIST_H

#include <iostream>
#include <vector>
#include <stdexcept>

class List
{

private:
    typedef struct node
    {
        int value;
        node *next;
        node *prev;
    } node;
    node *head = nullptr;
    node *tail = nullptr;
    size_t count = 0;

    node *find_by_index (size_t my_index) const;

public:
    List ();

    explicit List (std::vector<int> const &args);

    ~List ();

    int &operator[] (size_t i) const;

    List &operator>> (int new_value);

    List &operator+ (List const &second_list);

    friend std::ostream &operator<< (std::ostream &os, const List &myList);

    void insert (int new_value, size_t my_index);

    void push_back (int new_value);

    void push_front (int new_value);

    void pop (size_t my_index);

    void pop_back ();

    void pop_front ();

    int index (size_t my_index) const;

    int back ();

    int front ();

    size_t size () const;

    size_t find (int needle);
};

#endif //TEMA_1_LIST_H
