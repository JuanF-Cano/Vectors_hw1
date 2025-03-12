#include <iostream>
#include <cassert>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

template <typename T>
class Vector { // Vector class of type T --> Vector<T>
  private:
    T* storage_ ; // Pointer to an array of type T to store the data inside the vector
    unsigned int capacity_; // Stores the vector's capacity
    unsigned int size_; // Stores the number of elements in the vector
  public:
    Vector() { // Default constructor, with a capacity of 5 items
      capacity_ = 5;
      storage_ = new T[capacity_];
      size_ = 0;
    }
    Vector(unsigned int c, T element = T()) { // Constructor to initialize the vector with a predefined size and an optional element
      assert(c > 0); // If the capacity is not greater than 0, the program stops
      capacity_ = c;
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < capacity_; i++) { // Fill the vector with the initialization element
        storage_[i] = element;
      }
      size_ = capacity_;
    }
    Vector(initializer_list<T> list) { // Constructor to initialize the vector using a list --> {a, b, c}
      capacity_ = list.size() > 5 ? list.size() : 5; // Ensure capacity is not 0 if initialized with an empty list
      storage_ = new T[capacity_];
      size_ = list.size();
      unsigned int i = 0;
      for (const T& elem : list) { // For each element in the list, the reference is stored in the i-th position of storage_
        storage_[i++] = elem; // i++ to first evaluate the value of i and then increment it by 1
      }
    }
    Vector(const Vector<T>& v) { // Constructor to initialize the vector using another vector by copying its attributes
      capacity_ = v.capacity_;
      size_ = v.size_;
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < size_; i++) {
        storage_[i] = v.storage_[i]; // Copy elements from the storage_ of the passed vector to the initialized vector
      }
    }
    Vector& operator=(initializer_list<T>) = delete; // Remove the possibility of setting the vector using another list

  private:
    void resize() { // Resize the vector to increase its capacity, using different policies
      unsigned int capacity2 = capacity_ * 2; // capacity_ + 1 || capacity_ + 2 || capacity_ * 2 || capacity_ * 1.5 //...
      T* newStorage = new T[capacity2]; // Create a new storage with the reassigned capacity
      for (unsigned int i = 0; i < size_; i++) { // Copy all elements from the previous storage to the new one
        newStorage[i] = storage_[i];
      }
      delete [] storage_; // Free the heap memory reserved for storage_ using the [] operator to delete the array
      storage_ = newStorage; // Copy the pointer of the new storage
      capacity_ = capacity2; // Set the new capacity
    }
  public:
    bool empty() { return (size_ == 0); } // Returns whether the vector is empty
    void push_back(const T& element) { // Add an element to the end of the vector
      if (size_ == capacity_) { // If there is no space, resize the vector capacity
        resize();
      }
      storage_[size_] = element; // Store the element
      size_++;
    }
    void push_front(const T& element) { // Add an element to the beginning of the vector
      if (size_ == capacity_) { // If there is no space, resize the vector capacity
        resize();
      }
      for (int i = size_; i > 0; i--) { // Shift all elements of the vector one position to the right
        storage_[i] = storage_[i - 1]; 
      }
      storage_[0] = element; // Add the element to the beginning of the vector
      size_++;
    }
    void pop_back() { // Remove the last element of the vector
      assert(size_ > 0); // Check that it is not empty
      size_--;
    }
    void pop_front() { // Remove the first element of the vector
      assert(size_ > 0); // Check that it is not empty
      for (unsigned int i = 0; i < size_ - 1; i++) { // Shift the entire vector one position to the left
        storage_[i] = storage_[i + 1];
      }
      size_--;
    }
    unsigned int size() const { return size_; }
    unsigned int capacity() const { return capacity_; }
    int waste() const { return capacity_ - size_; } // Returns the amount of unused space in the vector
    T& at(unsigned int pos) const { // Method to get the value at an index in the vector
      assert(pos < size_); // Check that it is a valid position
      return storage_[pos];
    }
    const T& operator[](unsigned int index) const { // Define the [] operator to allow referencing using brackets
      assert(index < size_);
      return storage_[index];
    }
    void shrink_to_fit() { // Remove unused space within the vector
      T* storage2_ = new T[size_];
      for(unsigned int i = 0; i < size_; i++) { // Copy the vector to a new one with just enough space for the number of elements
        storage2_[i] = storage_[i];
      }
      delete[] storage_; // Free the heap memory reserved for storage_
      capacity_ = size_; // Set capacity equal to the number of elements in the vector
      storage_ = storage2_; // Copy the pointer of the new storage
    }
    void insert(unsigned int index, const T& element) { // Insert an element at the specified position
      assert(index <= size_); // Ensure the index is valid
      if (size_ == capacity_) { // If there is no space, resize capacity
        resize();
      }
      for (unsigned int i = size_; i > index; i--) { // Copy elements from the last to the index towards the right
        storage_[i] = storage_[i - 1];
      }
      storage_[index] = element; // Place the element at the specified index
      size_++;
    }
    void erase(unsigned int index) { // Delete the element at the specified index
      assert(index < size_); // Ensure the index is valid
      for (unsigned int i = index; i < size_ - 1; i++) { // Copy the entire vector, from the index onwards, one position to the left
        storage_[i] = storage_[i + 1];
      } 
      size_--;
    }
    void print() { // Print the vector elements in the format {a, b, c}
      cout << "{";
      if (size_ == 0) {
          cout << "}" << endl;
          return;
      }
      unsigned int i;
      for (i = 0; i < size_ - 1; i++) {
          cout << storage_[i] << ", ";
      }
      cout << storage_[i] << "}" << endl;
  }
};

Vector<int> removeDuplicates(const Vector<int>& v) { // Function to remove duplicate elements within a vector
  Vector<int> v2; // Initialize a vector where unique elements from v will be stored, which will be returned by the function
  bool isDuplicate; // Initialize a boolean variable to check if the element has already been stored
  for (unsigned int i = 0; i < v.size(); i++) { // Iterate through the entire vector to check each element
    int element = v[i]; // Store the element at the i-th position
    isDuplicate = false; // Set isDuplicate to false
    for (unsigned int j = 0; j < v2.size(); j++) { // Iterate through v2 to check if the element is already stored
      if (v2[j] == element) { // For each element in v, check if it already exists in v2
        isDuplicate = true; // If found, set to true and exit the loop
        break;
      }
    }
    if (!isDuplicate) { // If the element is not in the vector, insert it into v2
      v2.push_back(element);
    }
  }
  return v2; // Return v2 containing only unique elements
}

template <typename T>
Vector<T> mergeSortedVectors(Vector<T>& v1, Vector<T>& v2) { // Function to merge two vectors into one while sorting their elements
  Vector<T> v; // Initialize a vector v to store the sorted elements from v1 and v2
  unsigned i = 0, j = 0; // Initialize values for loop iterations
  while (i < v1.size() && j < v2.size()) { // Iterate until one of the vectors (v1, v2) is fully traversed
    if (v1[i] < v2[j]) { // If the element in v1 is smaller than the one in v2, insert the v1 element into v
      v.push_back(v1[i]);
      i++;
    } else { // Otherwise, the element in v1 is greater than or equal to v2's, so insert v2's element into v
      v.push_back(v2[j]);
      j++;
    }
  }
  while (i < v1.size()) { // Insert the remaining elements from v1 into v, as they are all greater
    v.push_back(v1[i]);
    i++;
  }
  while (j < v2.size()) { // Insert the remaining elements from v2 into v, as they are all greater
    v.push_back(v2[j]);
    j++;
  }

  return v; // Return the new sorted vector containing elements from both input vectors
}

template <typename T>
class Stack { // Stack class (Follows the LIFO (Last In, First Out) principle)
  private:
    Vector<T> storage_; // Built on top of a vector
  public:
    void push(const T& element) { storage_.push_back(element); } // Adds an element; push_back is used instead of push_front for efficiency
    void pop() { assert(!storage_.empty()); storage_.pop_back(); } // Removes an element → the last one added (following LIFO principle)
    T& top() { assert(!storage_.empty()); return storage_.at(storage_.size() - 1); } // Returns the last value added to the stack
    bool empty() const { return storage_.empty(); } // Returns whether the stack is empty
    unsigned int size() const { return storage_.size(); } // Returns the size of the stack
};

int main() {
  /*  Vector<int> vector1 = {1, 3, 5};
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
  mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1} */

  /* ofstream fileInsertTimes("insertion_times.dat", ios::app);
  if (!fileInsertTimes) {
    cout << "Error opening fileInsertTimes!" << endl;
    return 1;
  }

  const int insertions = 100000;
  
  Vector<int> v1;
  Vector<int> v2;

  fileInsertTimes << "Insertion_Index Worst_Case_Time(us) Best_Case_Time(us)" << endl;

  for (int i = 0; i < insertions; i++) {
    auto start = high_resolution_clock::now();
    v1.insert(0, i);
    auto end = high_resolution_clock::now();

    double time_taken = duration<double, microseconds::period>(end - start).count();
    fileInsertTimes << i + 1 << " " << time_taken;
    start = high_resolution_clock::now();
    v2.insert(v2.size(), i);
    end = high_resolution_clock::now();
    time_taken = duration<double, microseconds::period>(end - start).count();
    fileInsertTimes << " " << time_taken << endl;
    } 
    fileInsertTimes.close();
    */

  /* ofstream fileEraseTimes("erase_times.dat", ios::app);
  if (!fileEraseTimes) {
    cout << "Error opening erase_times!" << endl;
    return 1;
  }

  const int insertions = 100000;
  
  Vector<int> v1(insertions);
  Vector<int> v2(insertions);

  fileEraseTimes << "Erase_Index Worst_Case_Time(us) Best_Case_Time(us)" << endl;

  for (int i = insertions; i > 0; i--) {
    auto start = high_resolution_clock::now();
    v1.erase(0);
    auto end = high_resolution_clock::now();
    
    double time_taken = duration<double, microseconds::period>(end - start).count();
    fileEraseTimes << i << " " << time_taken;
    start = high_resolution_clock::now();
    v2.erase(v2.size() - 1);
    end = high_resolution_clock::now();
    time_taken = duration<double, microseconds::period>(end - start).count();
    fileEraseTimes << " " << time_taken << endl;
  }

  fileEraseTimes.close(); */

  /* ofstream fileRemoveTimes("removeDuplicates_times.dat", ios::app);
  if (!fileRemoveTimes) {
    cout << "Error opening removeDuplicates_times!" << endl;
    return 1;
  }

  const int insertions = 10000;
  
  Vector<int> v2;
  
  fileRemoveTimes << "Function_Index Worst_Case_Time(us) Best_Case_Time(us)" << endl;
  
  for (int i = 1; i <= insertions; i++) {
    Vector<int> v1(i);
    v2.push_back(i);

    auto start = high_resolution_clock::now();
    removeDuplicates(v2);
    auto end = high_resolution_clock::now();
    
    double time_taken = duration<double, microseconds::period>(end - start).count();
    fileRemoveTimes << i << " " << time_taken;
    start = high_resolution_clock::now();
    removeDuplicates(v1);
    end = high_resolution_clock::now();
    time_taken = duration<double, microseconds::period>(end - start).count();
    fileRemoveTimes << " " << time_taken << endl;
  }

  fileRemoveTimes.close(); */

  /* ofstream fileVectorGrowth("vector_growth.dat", ios::app);
  if (!fileVectorGrowth) {
      cout << "Error opening fileVectorGrowth!" << endl;
      return 1;
  }

  srand(time(nullptr));
  const int totalInsertions = 1000000;
  const int logInterval = 1000;

  Vector<int> v;
  fileVectorGrowth << "policy*2"; // policy+1, policy+2, policy*1.5, policy*2
  fileVectorGrowth << endl << "size, capacity" << endl;
  for (int i = 0; i < totalInsertions; i++) {
    v.push_back((int)(rand() % 100));
    if ((i + 1) % logInterval == 0) {
        fileVectorGrowth << v.size() << " " << v.capacity() << endl;
    }
  }

  fileVectorGrowth.close(); */

  
  
  return 0;
}