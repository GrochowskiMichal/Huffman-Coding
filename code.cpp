/*
Project name: Huffman Coding
Project version:  1.0
File name:  code.cpp
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
#include "code.hpp"

HuffCode::HuffCode() {}

void HuffCode::fileEncode(const std::string &input, const std::string &output) {
  // read the contents of input file
  std::streampos size;
  char *data;
  std::ifstream inputFile(input,std::ios::binary | std::ios::in | std::ios::ate);

  if (!inputFile.is_open()) {
    std::cout << "failed to open the input file!" << std::endl;
    return;
  }

  size = inputFile.tellg(); //getting the current read position
  data = new char[size];
  inputFile.seekg(0, std::ios::beg);
  inputFile.read(data, size);

  inputFile.close();

  stringToEncode = data;
  delete[] data;

  // calculate byte frequencies
  std::cout << "Byte frequencies calculating..." << std::endl;
  calculateFrequencies();

  // create the huffman tree
  std::cout << "Huffman tree creating..." << std::endl;
  createTree();

  // create the huffman code from that tree
  std::cout << "Huffman code generating ..." << std::endl;
   std::cout << "Done!" << std::endl;
  // std::vector<bool> v;
  HuffVector<bool> v;
  generateHuffCode(root, v);

  // encode the tree data; source of the idea taken from:
  // http://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
  HuffVector<bool> b;
  // std::vector<bool> b;
  encode(root, b);
  bits = HuffVector<bool>(b);

  // append the encoded string itself
  appendEncodedBits();

  // converting bits to bytes in purpose of saving
  bitsToBytes();

  // writing the output
  std::ofstream outputFile;
  outputFile.open(output, std::ofstream::out);

  for (size_t i = 0; i < bytes.size(); ++i) {
    const uint8_t byte = bytes[i];
    outputFile << byte;
  }

  outputFile.close();
}

void HuffCode::fileDecode(const std::string &input, const std::string &output) {
  // reading contents of the file
  std::streampos size;
  char *data;
  std::ifstream file(input, std::ios::binary | std::ios::in | std::ios::ate);

  if (!file.is_open()) {
    std::cout << "failed to open" << std::endl;
    return;
  }

  size = file.tellg();
  data = new char[size];
  file.seekg(0, std::ios::beg);
  file.read(data, size);
  file.close();

  size_t fileSize = static_cast<size_t>(size);

  // converting bytes to bits
  for (size_t k = 0; k < fileSize; ++k) {

    char c = data[k];

    uint8_t byte = static_cast<uint8_t>(c);

    size_t shiftCount = 7;

    do {
      bool bit = ((byte >> shiftCount) & 1);
      bits.push_back(bit);
    } while (shiftCount-- != 0);
  }

  delete[] data;

  // rebuilding the tree
  Node *decodedRoot = rebuildTree();

  std::string s = "";

  // decoding the encoded data with the rebuilt tree
  while (true) {
    // in case of hitting the end
    if (decodingIndex >= bits.size()) {
      break;
    }

    char c = getCharacter(decodedRoot);
    s += c;
  }

  // writing the output
  std::ofstream outputFile;
  outputFile.open(output, std::ofstream::out);

  outputFile << s;

  outputFile.close();
}

// calculating character (byte) frequencies
void HuffCode::calculateFrequencies() {
  for (const char &c : stringToEncode) {
    ++(frequencies[static_cast<uint8_t>(c)]);
  }
}

// creating the initial leaves and internal leaves
void HuffCode::createTree() {
  HuffQueue tree;

  // loop through bytes ("characters") and pushing them into the queue
  uint8_t i = 0;

  do {
    const auto frequency = frequencies[i];

    if (frequency == 0) {
      continue;
    }

    Node *node = new Node(frequency, i);
    tree.push(node);
  } while (i++ != UINT8_MAX);

  // creating internal nodes
  while (tree.size() > 1) {
    Node *rightChild = tree.pop();
    Node *leftChild = tree.pop();

    Node *parent = new Node(leftChild, rightChild);
    tree.push(parent);
  }

  root = tree.top();
}

// generating recursivly huffman coding
void HuffCode::generateHuffCode(const Node *node,
                                   const HuffVector<bool> &code) {
  // assigning a code
  if (!node->left && !node->right) {
    size_t index = static_cast<size_t>(node->character);
    codes[index] = code;
    return;
  }

  auto left = HuffVector<bool>(code);
  left.push_back(false);

  auto right = HuffVector<bool>(code);
  right.push_back(true);

  generateHuffCode(node->left, left);
  generateHuffCode(node->right, right);
}

// encoding the codes and the string into bits for packaging into bytes
void HuffCode::encode(const Node *node, HuffVector<bool> &v) {
  if (!node->left) {
    // this is the code for this byte
    v.push_back(true);
    uint8_t b = static_cast<uint8_t>(node->character);

    // byte in bits
    // only works in little endian machines
    v.push_back(((b >> 7) & 1));
    v.push_back(((b >> 6) & 1));
    v.push_back(((b >> 5) & 1));
    v.push_back(((b >> 4) & 1));
    v.push_back(((b >> 3) & 1));
    v.push_back(((b >> 2) & 1));
    v.push_back(((b >> 1) & 1));
    v.push_back((b & 1));

  } else {
    v.push_back(false);

    encode(node->left, v);
    encode(node->right, v);
  }
}

// converting bits to bytes for output purposes
void HuffCode::bitsToBytes() {
  size_t bitCount = 0;
  uint8_t byte = 0;

  for (size_t i = 0; i < bits.size(); ++i) {
    // shift the bit to the right position and or it in place
    byte |= (bits[i] & 1) << (7 - bitCount);
    ++bitCount;

    // byte ready state
    if (bitCount == 8) {
      bytes.push_back(byte);
      byte = 0;
      bitCount = 0;
    }

    if (i == bits.size() - 1) {
      break;
    }
  }
}

void HuffCode::appendEncodedBits() {
  for (const char &c : stringToEncode) {
    uint8_t i = static_cast<uint8_t>(c);
    auto code = codes[i];

    // for (const bool &b : code) {
    for (size_t index = 0; index < code.size(); ++index) {
      bits.push_back(code[index]);
    }
  }
}

bool HuffCode::getBit() { return bits[decodingIndex++]; }

uint8_t HuffCode::getByte() {
  uint8_t byte = 0;

  for (size_t i = 0; i < 8; ++i) {
    bool bit = getBit();
    byte |= bit;

    if (i != 7) {
      byte <<= 1;
    }
  }

  return byte;
}

Node *HuffCode::rebuildTree() {
  if (getBit()) {
    return new Node(0, getByte());
  }

  Node *left = rebuildTree();
  Node *right = rebuildTree();

  return new Node(left, right);
}

// find a character for the current code
char HuffCode::getCharacter(const Node *n) {
  if (!n->left && !n->right) {
    // if it's a leaf -> get the character
    return n->character;
  } else if (getBit()) {
    // bit is 1 -> go right
    return getCharacter(n->right);
  } else {
    // bit is 0 -> go left
    return getCharacter(n->left);
  }
}