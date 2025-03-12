#include <iostream>
#include "vector.h"

using namespace std;

int main() {
    Stack<int> s;

    // Check that the stack is initially empty
    cout << "Stack initially empty: " << (s.empty() ? "Yes" : "No") << endl; // Expected: Yes

    // Test push
    s.push(10);
    s.push(20);
    s.push(30);
    cout << "After pushing 10, 20, 30, stack empty? " << (s.empty() ? "Yes" : "No") << endl; // Expected: No

    // Test top
    cout << "Top element (before pop): " << s.top() << endl; // Expected: 30

    // Test pop
    s.pop();
    cout << "After one pop, top element: " << s.top() << endl; // Expected: 20
    s.pop();
    cout << "After another pop, top element: " << s.top() << endl; // Expected: 10

    // Check size
    cout << "Stack size: " << s.size() << endl; // Expected: 1

    // Empty the stack
    s.pop();
    cout << "Stack empty after popping all elements? " << (s.empty() ? "Yes" : "No") << endl; // Expected: Yes

    // Test push after emptying the stack
    s.push(50);
    cout << "After pushing 50, top element: " << s.top() << endl; // Expected: 50

    return 0;
}
