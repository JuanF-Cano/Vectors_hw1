#include <iostream>
#include "vector.h"

int main() {
  Vector<int> vector1 = {1, 3, 5};
  Vector<int> vector2 = {2, 4, 6};
  Vector<int> mergedVector = mergeSortedVectors(vector1, vector2);
  
  mergedVector.print(); // Expected: {1, 2, 3, 4, 5, 6}
  
  Vector<int> vector3 = {1, 2, 3};
  Vector<int> vector4 = {};
  Vector<int> mergedVector2 = mergeSortedVectors(vector3, vector4);
  mergedVector2.print(); // Expected: {1, 2, 3}
  
  Vector<int> vector5 = {};
  Vector<int> vector6 = {4,5,6};
  Vector<int> mergedVector3 = mergeSortedVectors(vector5, vector6);
  mergedVector3.print(); // Expected: {4, 5, 6}
  
  Vector<int> vector7 = {1,1,1,1};
  Vector<int> vector8 = {1,1,1,1};
  Vector<int> mergedVector4 = mergeSortedVectors(vector7, vector8);
  mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1}

  return 0;
}