#include <vector.h>

int main() {
  Vector<int> myVector;

  // Test push_back
  myVector.push_back(10);
  myVector.push_back(20);
  myVector.push_back(30);

  cout << myVector.size() << endl; // Expected: 3
  cout << myVector.capacity() << endl; // Expected: Initial capacity, e.g., 4 or 8

  // Test pop_back
  myVector.pop_back();
  cout << myVector.size() << endl; // Expected: 2

  // Test at with valid and invalid indices
  cout << myVector.at(0) << endl; // Expected: 10
  cout << myVector.at(1) << endl; // Expected: 20

  // Border case: Accessing an out-of-bounds index
  cout << myVector.at(2) << endl; // Should crash!

  // Border case: pop_back on empty vector
  Vector<int> emptyVector;
  emptyVector.pop_back(); // should crash! 

  return 0;
}