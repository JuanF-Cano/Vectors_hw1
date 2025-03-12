#include <vector.h>


int main() {
  Vector<int> numbers = {1, 2, 2, 3, 4, 4, 5};
  Vector<int> uniqueNumbers = removeDuplicates(numbers);
  
  uniqueNumbers.print(); // Expected: {1, 2, 3, 4, 5}
  
  Vector<int> numbers2 = {1,1,1,1,1,1};
  Vector<int> uniqueNumbers2 = removeDuplicates(numbers2);
  uniqueNumbers2.print(); // Expected: {1}
  
  Vector<int> numbers3 = {};
  Vector<int> uniqueNumbers3 = removeDuplicates(numbers3);
  uniqueNumbers3.print(); // Expected: {}
  
  Vector<int> numbers4 = {1};
  Vector<int> uniqueNumbers4 = removeDuplicates(numbers4);
  uniqueNumbers4.print(); // Expected: {1}

  return 0;
}