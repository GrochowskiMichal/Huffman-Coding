/*
Project name: Huffman Coding
Project version:  1.0
File name:  code.hpp
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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
//
#include "node.hpp"
#include "queue.hpp"
#include "vector.hpp"

class HuffCode {
public:
  HuffCode();
  void fileEncode(const std::string &input, const std::string &output);
  void fileDecode(const std::string &input, const std::string &output);

private:
  // encoding part
  void calculateFrequencies();
  void createTree();
  void generateHuffCode(const Node *node, const HuffVector<bool> &code);

  void encode(const Node *node, HuffVector<bool> &v);
  void bitsToBytes();

  void appendEncodedBits();

  // decoding part
  Node *rebuildTree();
  bool getBit();
  uint8_t getByte();

  char getCharacter(const Node *n);

  size_t decodingIndex = 0;

  std::string stringToEncode;

  // in need of room for 256 values, where UINT8_MAX is 255
  std::array<HuffVector<bool>, UINT8_MAX + 1> codes;
  std::array<uint64_t, UINT8_MAX + 1> frequencies = {{0}};

  HuffVector<bool> bits;
  HuffVector<uint8_t> bytes;

  Node *root = 0;
};
