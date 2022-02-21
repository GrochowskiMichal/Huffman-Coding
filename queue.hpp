/*
Project name: Huffman Coding
Project version:  1.0
File name:  queue.hpp
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
#include <array>
//
#include "node.hpp"

class HuffQueue {
public:
  HuffQueue();
  void push(Node *node);
  Node *pop();
  Node *top() const;
  std::size_t size() const;

private:
  const std::size_t firstIndex = 1;
  void heapify(const std::size_t i);
  void swap(const std::size_t first, const std::size_t second);
  void debugPrint() const;

  // at max there will be 256 nodes in the queue
  // by start indexing from 1, we need one (two) more spot
  // UINT8_MAX is 255
  std::array<Node *, UINT8_MAX + 2> queue = {{0}};
  std::size_t queueSize = 0;
};
