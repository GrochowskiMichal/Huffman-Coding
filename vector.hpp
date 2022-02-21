/*
Project name: Huffman Coding
Project version:  1.0
File name:  vector.hpp
Project description:  David Huffman algorithm based text files encoding/decoding as a command line utility.
Created by Michał Grochowski on 20 Feb 2022.

Copyright © 2022 Michał Grochowski. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once
#include <cstdint>
#include <cstring>

template <class T> class HuffVector {
public:
  HuffVector() { elements = new T[currentSize]; }

  // copy some other huffvector's contents to the new one
  HuffVector(const HuffVector &other) {
    elements = new T[other.currentSize];

    std::memcpy(elements, other.elements, other.currentIndex * sizeof(T));

    currentIndex = other.currentIndex;
    currentSize = other.currentSize;
  }

  ~HuffVector() {}

  // pushing an item to the vector
  void push_back(T const &item) {
    // resizing (double the size) if occuring no space
    if (currentIndex == currentSize) {
      resize();
    }

    elements[currentIndex++] = item;
  }

  size_t size() const { return currentIndex; }

  T &operator[](size_t index) const { return elements[index]; }

private:
  T *elements;
  size_t currentIndex = 0;
  size_t currentSize = 4;

  void resize() {
    // doubling the size
    currentSize <<= 1;

    // creating the new array and copying the old contents into it
    T *temp = new T[currentSize];

    std::memcpy(temp, elements, (currentIndex) * sizeof(T));

    delete[] elements;
    elements = temp;
  }
};
