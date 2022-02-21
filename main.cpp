/*
Project name: Huffman Coding
Project version:  1.0
File name:  main.cpp
Project description:  David Huffman algorithm based text files encoding/decoding script
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
#include <iostream>
#include <string>
//
#include "code.hpp"

// defining possible to obtain cases
enum option { ENCODE, DECODE, UNDEFINED };

void UsageDescrip() {
  std::cout << "Possible script options:"
            << "\n"    
            << "--encode"
            << "\n"
            << "--decode"
            << "\n"
            << "\n"
            << "Usage example:"
            << "\n" 
            << "./huff --encode sample_text_file.txt -o encoded_sample_text_file.txt"
            << "\n"     
            << "./huff --decode encoded_sample_text_file.txt -o decoded_sample_text_file.txt"
            << std::endl;
}

option getOptionForArgument(const std::string &argument) {
  if (argument == "--encode") {
    return ENCODE;
  }

  if (argument == "--decode") {
    return DECODE;
  }

  return UNDEFINED;
}

#include "vector.hpp"
#include <cstdint>

int main(int argc, char *argv[]) {
  if (argc < 5) {
    // if there is not enough number of arguments -> above defined function is printing the usage description
    UsageDescrip(); 
    return 1;
  }

  const std::string option = argv[1];
  const std::string inputFile = argv[2];
  const std::string outputArgument = argv[3];
  const std::string outputFile = argv[4];

  // argument 3 ( argv[3] ) has to be -o
  if (outputArgument != "-o") {
    UsageDescrip();
    return 1;
  }
  // initialization of possible to obtain cases
  HuffCode j = HuffCode();

  switch (getOptionForArgument(option)) {
  case ENCODE:
    j.fileEncode(inputFile, outputFile);
    break;
  case DECODE:
    j.fileDecode(inputFile, outputFile);
    break;
  case UNDEFINED:
    UsageDescrip();
    return 1;
  }

  return 0;
}
