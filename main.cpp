#include <cassert>
#include <iostream>
#include <utility>
#include "mydeque.hpp"

int main() {
    // 1. Test podstawowych operacji 
    MyDeque<int> dq(4);
    assert(dq.empty());
    assert(!dq.full());
    assert(dq.size() == 0);
    assert(dq.max_size() == 4);

    dq.push_back(11);
    dq.push_back(22);
    dq.push_front(33);
    dq.push_front(44);

    assert(dq.full());
    assert(dq.size() == 4);
    assert(dq.front() == 44);
    assert(dq.back() == 22);

    std::cout << "Zawartosc (od przodu): ";
    dq.display(); // 44 33 11 22
    std::cout << "Zawartosc (od tylu):   ";
    dq.display_reversed(); // 22 11 33 44

    // 2. Test operacji indeksowanych (operator[], index, insert, erase)
    assert(dq[0] == 44);
    assert(dq[1] == 33);
    assert(dq[2] == 11);
    assert(dq[3] == 22);
    assert(dq.index(11) == 2);
    assert(dq.index(999) == -1);

    dq.erase(1); // usuwa 33 -> [44, 11, 22]
    assert(dq.size() == 3);
    assert(dq[1] == 11);

    dq.insert(1, 55); // wstawia 55 przed indeks 1 -> [44, 55, 11, 22]
    assert(dq.full());
    assert(dq[1] == 55);
    assert(dq[2] == 11);

    // 3. Test pop_front i pop_back
    dq.pop_front(); // [55, 11, 22]
    assert(dq.front() == 55);
    dq.pop_back();  // [55, 11]
    assert(dq.back() == 11);
    assert(dq.size() == 2);

    // 4. Test konstruktora kopiującego i operatora przypisania
    MyDeque<int> copy_dq(dq);
    assert(copy_dq.size() == 2);
    assert(copy_dq.front() == 55);
    assert(copy_dq.back() == 11);

    MyDeque<int> assign_dq(2);
    assign_dq = dq;
    assert(assign_dq.size() == 2);
    assert(assign_dq[0] == 55);

    // 5. Test semantyki przenoszenia
    MyDeque<int> move_dq(std::move(copy_dq));
    assert(move_dq.size() == 2);
    assert(move_dq.front() == 55);
    assert(copy_dq.empty());
    assert(copy_dq.max_size() == 0); // sprawdzenie warunku other.msize == 1

    // 6. Test czyszczenia
    dq.clear();
    assert(dq.empty());
    assert(dq.size() == 0);

    std::cout << "Wszystkie testy przeszly pomyslnie!" << std::endl;
    return 0;
}