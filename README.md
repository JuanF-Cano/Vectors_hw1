<h1 style="font-size:3rem; text-align:center"> Exercicies on vectors - Task review </h1>


# **Insert and Erase Methods**

The file `./vector.cc` include, on lines 107 and 118, the insert and erase methods. 

**The Insert Method** moves the elements of vector one position to the right, from the index at which it is to be inserted. Keeping in mind that if there is no space, it uses a resize function. Increasing its size by one.

**The Erase Method** moves the elements of the vector one position to the left, from the end to the index. Decreasing its size by one.

## Insert Method
```c++
void insert(unsigned int index, const T& element) {
  assert(index <= size_);
  if (size_ == capacity_) {
    resize();
  }
  for (unsigned int i = size_; i > index; i--) { 
    storage_[i] = storage_[i - 1];
  }
  storage_[index] = element;
  size_++;
}
```
## Erase Method
```c++
void erase(unsigned int index) {
  assert(index < size_);
  for (unsigned int i = index; i < size_ - 1; i++) {
    storage_[i] = storage_[i + 1];
  } 
  size_--;
}
``` 
---
## Time Complexity Analysis

### 1. Insertion at a specific index (`insert(index, element)`)

- If the vector is full, it first calls resize(), which takes O(n) time because it copies all elements to a new storage. 

- Then, shifting elements to the right from index to size_ takes `O(n - index) ≈ O(n)` in the worst case (if inserting at the beginning).  
- Finally, inserting the new element at index takes `O(1)`.
- Overall worst-case time complexity: `O(n)`.

### 2. Erasing an element at a specific index (`erase(index)`).

- The operation shifts elements to the left from index + 1 to size_, which takes `O(n - index) ≈ O(n)` in the worst case (if erasing at the beginning). 
- The size is decremented, which is `O(1)`. 
- Overall worst-case time complexity: `O(n)`.

| Operation	| Best Case	| Worst Case |
|-----------|-----------|------------|
|`insert(index, element)`|	O(1) (if inserting at the end and no resize)| O(n) (if shifting all elements) |
|`erase(index)`|	O(1) (if removing the last element) |	O(n) (if shifting all elements) |

---
# **Removing Duplicates**

The file `./vector.cc` include, on line 139, the removeDuplicates function. This function deletes all duplicate elements while preserving the original order of the remaining elements in the vector.

This function creates a vector that holds all non-repeated elements, in order, of the vector sent as a parameter.

```c++
Vector<int> removeDuplicates(const Vector<int>& v) {
  Vector<int> v2;
  bool isDuplicate;
  for (unsigned int i = 0; i < v.size(); i++) {
    int element = v[i];
    isDuplicate = false;
    for (unsigned int j = 0; j < v2.size(); j++) {
      if (v2[j] == element) { 
        isDuplicate = true;
        break;
      }
    }
    if (!isDuplicate) {
      v2.push_back(element);
    }
  }
  return v2;
}
```

## Time Complexity Analysis

- The outer loop runs O(n) times.
- The inner loop (searching for duplicates) runs O(n) in the worst case.
- Overall complexity: O(n × n) = O(n²).

---
# **Dynamic Array Resizing Analysis**
Graphs are created to analyze the size and capacity data, using python and Google Colab: https://colab.research.google.com/drive/1bu4DRTwN80esIYb4VYtAB35tLM5HzzTv?usp=sharing

Using this code in colab, the 4 graphs are created:
```python
import matplotlib.pyplot as plt

file_path = "/content/vector_growth.dat"

with open(file_path, "r", encoding="utf-8") as file:
    content = file.readlines()

resizes = {}
current_resize = None

for line in content:
    line = line.strip()
    if line.startswith("policy"):
        current_resize = line
        resizes[current_resize] = {"size": [], "capacity": []}
    elif line and current_resize and not line.startswith("size capacity"):
        size, capacity = map(int, line.split())
        resizes[current_resize]["size"].append(size)
        resizes[current_resize]["capacity"].append(capacity)

fig, axes = plt.subplots(2, 2, figsize=(12, 10))
axes = axes.flatten()

for i, (resize_type, data) in enumerate(resizes.items()):
    axes[i].plot(data["size"], data["capacity"], marker='o', linestyle='-')
    axes[i].set_title(resize_type)
    axes[i].set_xlabel("Size")
    axes[i].set_ylabel("Capacity")

plt.tight_layout()
plt.show()

```

---
# **Stack Using a Vector**

A stack is a data structure that follows the **Last In, First Out (LIFO) principle** meaning the last element added is the first element to be removed.

The file `./vector.cc` include, on lines 183, the Stack class which is using the vector data struct.

```c++
template <typename T>
class Stack {
  private:
    Vector<T> storage_;
  public:
    void push(const T& element) { storage_.push_back(element); } 
    void pop() { assert(!storage_.empty()); storage_.pop_back(); }
    T& top() { assert(!storage_.empty()); return storage_.at(storage_.size() - 1); } 
    bool empty() const { return storage_.empty(); }
    unsigned int size() const { return storage_.size(); }
};
```

# **Merge Sorted Vectors**
The file `./vector.cc` include, on lines 158, the Stack class which is using the vector data struct.

This function creates a vector that stores the elements of the two vectors in order, using logic similar to MergeSort.

```c++
template <typename T>
Vector<T> mergeSortedVectors(Vector<T>& v1, Vector<T>& v2) {
  Vector<T> v;
  unsigned i = 0, j = 0;
  while (i < v1.size() && j < v2.size()) {
    if (v1[i] < v2[j]) {
      v.push_back(v1[i]);
      i++;
    } else {
      v.push_back(v2[j]);
      j++;
    }
  }
  while (i < v1.size()) {
    v.push_back(v1[i]);
    i++;
  }
  while (j < v2.size()) {
    v.push_back(v2[j]);
    j++;
  }

  return v;
}
```