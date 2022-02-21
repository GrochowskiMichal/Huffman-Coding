/*
Project name: Huffman Coding
Project version:  1.0
File name:  queue.cpp
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
#include "queue.hpp"

static std::size_t parent(std::size_t i) { return i / 2; }

static std::size_t leftChild(std::size_t i) { return 2 * i; }

static std::size_t rightChild(std::size_t i) { return 2 * i + 1; }

HuffQueue::HuffQueue() {}  //priority queue

// push an item to the queue
void HuffQueue::push(Node *node) {
  std::size_t i = ++queueSize;

  // keeping the shape
  while (i > 1 && queue[parent(i)]->frequency > node->frequency) {
    queue[i] = queue[parent(i)];
    i = parent(i);
  }

  queue[i] = node;
}

// returning the first node (the node with the smallest frequency) from the queue
// moving the last node to the first position what is allowing me to heapify the queue easily
Node *HuffQueue::pop() {
  Node *top = queue[firstIndex];
  std::size_t lastIndex = queueSize;
  queue[firstIndex] = queue[lastIndex];
  queue[lastIndex] = 0;
  heapify(firstIndex);
  queueSize--;
  return top;
}

void HuffQueue::heapify(const std::size_t i) {
  std::size_t left = leftChild(i);
  std::size_t right = rightChild(i);
  std::size_t smallest =
      (left < queueSize && queue[left]->frequency < queue[i]->frequency) ? left
                                                                         : i;

  smallest = (right < queueSize &&
              queue[right]->frequency < queue[smallest]->frequency)
                 ? right
                 : smallest;

  if (smallest != i) {
    swap(i, smallest);
    heapify(smallest);
  }
}

void HuffQueue::swap(const std::size_t first, const std::size_t second) {
  Node *temp = queue[first];
  queue[first] = queue[second];
  queue[second] = temp;
}

std::size_t HuffQueue::size() const { return queueSize; }

Node *HuffQueue::top() const { return queue[firstIndex]; }
