#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    } else {
      capacity_ = capacity;
      size_ = 0;
      data_ = new int[capacity];
      for (int i = 0; i < capacity; i++) {
        data_[i] = 0;
      }
    }
  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;
    delete data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    data_[size_] = value;
    size_++;
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index >= size_ || index < 0) {
      return false;
    } else {
      if (size_ >= capacity_) {
        Resize(capacity_ + kCapacityGrowthCoefficient);
      }
      int* temp = data_;
      for (int i = index; i < size_ + 1; i++) {
        data_[i + 1] = temp[i];
      }
      delete temp;
      data_[index] = value;
      size_++;
      return true;
    }
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index >= size_ || index < 0) {
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (index >= size_ || index < 0) {
      return false;
    }
    int value = data_[index];
    for (int i = index; i < size_-1; i++) {
      data_[i] = data_[i + 1];
    }
    size_--;
    return value;

  }

  void DynamicArray::Clear() {
    size_ = 0;
    delete data_;
    data_ = nullptr;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index >= size_ || index < 0) {
      return std::nullopt;
    }
    return data_[index];
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (capacity_ >= new_capacity) {
      return false;
    } else {
      int* temp = new int[new_capacity];
      std::copy(data_, data_ + size_, temp);
      delete data_;
      data_ = temp;
      capacity_ = new_capacity;
      return true;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }
}