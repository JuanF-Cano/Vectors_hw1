#include <iostream>
#include "vector.h"

int main() {
  Stack<int> s;

  // Verificar que la pila inicia vacía
  cout << "Stack initially empty: " << (s.empty() ? "Yes" : "No") << endl;

  // Probar push
  s.push(10);
  s.push(20);
  s.push(30);
  cout << "After pushing 10, 20, 30, stack empty? " << (s.empty() ? "Yes" : "No") << endl;

  // Probar top
  cout << "Top element (before pop): " << s.top() << endl;

  // Probar pop
  s.pop();
  cout << "After one pop, top element: " << s.top() << endl;
  s.pop();
  cout << "After another pop, top element: " << s.top() << endl;

  // Verificar tamaño
  cout << "Stack size: " << s.size() << endl;

  // Vaciar la pila
  s.pop();
  cout << "Stack empty after popping all elements? " << (s.empty() ? "Yes" : "No") << endl;

  // Probar push después de vaciar
  s.push(50);
  cout << "After pushing 50, top element: " << s.top() << endl;

  cout << "All Stack tests completed!" << endl;
  return 0;
}