#include <iostream>

#include "List.h"

int main() {
    List myList1({1, 2, 3, 4});
    List myList2({5, 6, 7});
    List myList3({8, 9, 10});
    List myList4;

    myList4 = myList1 + myList2 + myList3;
    myList4 >> 11 >> 12;

    myList4[9] = 10;

    std::cout << myList4 << std::endl;
    std::cout << myList4[myList4.find(2)] << std::endl;

//    Throws std::out_of_range
//    std::cout << myList4[20] << std::endl;
    return 0;
}
