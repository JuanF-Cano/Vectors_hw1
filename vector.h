#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>
#include <initializer_list>

using namespace std;

template <typename T>
class Vector {
  private:
    T* storage_;
    unsigned int capacity_;
    unsigned int size_;
  public:
    Vector() {
      capacity_ = 5;
      storage_ = new T[capacity_];
      size_ = 0;
    }
    Vector(unsigned int c, T element = T()) {
      assert(c > 0);
      capacity_ = c;
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < capacity_; i++) {
        storage_[i] = element;
      }
      size_ = capacity_;
    }
    Vector(initializer_list<T> list) {
      capacity_ = list.size() > 5 ? list.size() : 5;
      storage_ = new T[capacity_];
      size_ = list.size();
      unsigned int i = 0;
      for (const T& elem : list) {
        storage_[i++] = elem;
      }
    }
    Vector(const Vector<T>& v) {
      capacity_ = v.capacity_;
      size_ = v.size_;
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < size_; i++) {
        storage_[i] = v.storage_[i];
      }
    }
    ~Vector() { delete[] storage_; }
    
    void push_back(const T& element) {
      if (size_ == capacity_) resize();
      storage_[size_++] = element;
    }
    void push_front(const T& element) {
      if (size_ == capacity_) resize();
      for (int i = size_; i > 0; i--) {
        storage_[i] = storage_[i - 1];
      }
      storage_[0] = element;
      size_++;
    }
    void pop_back() {
      assert(size_ > 0);
      size_--;
    }
    void pop_front() {
      assert(size_ > 0);
      for (unsigned int i = 0; i < size_ - 1; i++) {
        storage_[i] = storage_[i + 1];
      }
      size_--;
    }
    void insert(unsigned int index, const T& element) {
      assert(index <= size_);
      if (size_ == capacity_) resize();
      for (unsigned int i = size_; i > index; i--) {
        storage_[i] = storage_[i - 1];
      }
      storage_[index] = element;
      size_++;
    }
    void erase(unsigned int index) {
      assert(index < size_);
      for (unsigned int i = index; i < size_ - 1; i++) {
        storage_[i] = storage_[i + 1];
      }
      size_--;
    }
    bool empty() const { return size_ == 0; }
    unsigned int size() const { return size_; }
    unsigned int capacity() const { return capacity_; }
    int waste() const { return capacity_ - size_; }
    T& at(unsigned int pos) const {
      assert(pos < size_);
      return storage_[pos];
    }
    const T& operator[](unsigned int index) const {
      assert(index < size_);
      return storage_[index];
    }
    void shrink_to_fit() {
      T* storage2_ = new T[size_];
      for (unsigned int i = 0; i < size_; i++) {
        storage2_[i] = storage_[i];
      }
      delete[] storage_;
      capacity_ = size_;
      storage_ = storage2_;
    }
    void print() const {
      cout << "{";
      if (size_ == 0) {
        cout << "}" << endl;
        return;
      }
      for (unsigned int i = 0; i < size_ - 1; i++) {
        cout << storage_[i] << ", ";
      }
      cout << storage_[size_ - 1] << "}" << endl;
    }
  private:
    void resize() {
      unsigned int capacity2 = capacity_ + 1;
      T* newStorage = new T[capacity2];
      for (unsigned int i = 0; i < size_; i++) {
        newStorage[i] = storage_[i];
      }
      delete[] storage_;
      storage_ = newStorage;
      capacity_ = capacity2;
    }
};

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

#endif