/*
Project name: Huffman Coding
Project version:  1.0
File name:  node.hpp
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
/*
 * Data structure used as the node in the Huffman tree built
 */
struct Node {
  const uint64_t frequency;
  uint8_t character;

  const Node *left;
  const Node *right;

  Node(uint64_t f, uint8_t c) : frequency(f), character(c), left(0), right(0) {}
  Node(Node *l, Node *r)
      : frequency(l->frequency + r->frequency), left(l), right(r) {}
};
