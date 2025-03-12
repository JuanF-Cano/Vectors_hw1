#include <iostream>
#include "vector.h"

using namespace std;

int main() {
    Vector<int> vec;
    
    vec.insert(0, 10); // Insert at the beginning
    vec.insert(1, 20); // Insert at the end
    vec.insert(1, 15); // Insert in the middle
    cout << "After insertions: ";
    vec.print(); // Expected {10, 15, 20}
    
    vec.erase(0); // Erase from the beginning
    cout << "After erasing first element: ";
    vec.print(); // Expected {15, 20}
    
    vec.erase(vec.size() - 1); // Erase from the end
    cout << "After erasing last element: ";
    vec.print(); // Expected {15}
    
    vec.insert(0, 5);
    vec.insert(1, 7);
    vec.insert(2, 9);
    cout << "After inserting more elements: ";
    vec.print(); // Expected {5, 7, 15, 9}
    
    vec.erase(1); // Erase from the middle
    cout << "After erasing middle element: ";
    vec.print(); // Expected {5, 15, 9}
    
    return 0;
}