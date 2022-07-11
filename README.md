# Huffman-Coding 

![Screenshot_50-removebg-preview](https://user-images.githubusercontent.com/40866831/159987948-7ed6a2fe-8336-4838-af0b-28a6c0fe4191.png)

Program that compresses and decompresses text files with the Huffmann’s method.


## Table of contents
* [General Info](#general-information)
* [Data Structures](#data-structures)
* [Space requirements and time target analysis](#space-requirements-and-time-target-analysis)
* [General assumptions](#general-assumptions)
* [External specification - setup](#setup)
* [External specification - usage](#usage)
* [Internal specification](#internal-specification)
* [Internal code description](#internal-code-description)
* [Testing](#testing)
* [Deficiencies according to my assessment](#deficiencies)
* [Sources for acquiring knowledge](#sources-for-acquiring-knowledge)

## General Information 
Compression of the data has been something that revolutionized
digital media. Compression algorithms are used to reduce the size of a
file while ensuring that files can be fully restored to their original state.
There is a very wide range of algorithms that can be used to perform
lossless data compression. The simplest known data compression
algorithm is the Run-Length Encoding (RLE). Unfortunately, it has some
drawbacks (quite significant ones) - there are no repeated characters,
and the size of output data can be two times more than the size of input
data. To eliminate this problem Huffman Coding was used. Huffman
coding algorithm was introduced by David Huffman in 1952.
The main purpose of information theory is to convey information in
as few bits as possible. Huffman's coding has the same aim and is
largely successful. The algorithm stands on creating a tree in the form of
a leaf node and its children which has a probability of the frequent
appearance of the characters. So, Huffman algorithm has more
efficiency in file compression with greater compression ratio.
In the era of the internet, the transmission of data depends on
time. More data takes more time to transmit. Huffman coding reduces
the data size thus data transmission time is significantly reduced. It is the
basis of many data compression and encoding schemes. mainly
because it is a lossless data conversion. 
This Algorithm is used for compressing / decompressing data -
reducing its size without losing any information. It consists on two major
steps:
1. Generating a Huffman tree from the input characters
2. Traversing the Huffman tree to assign codes to the
characters (encoding)
For decompression, the Huffman tree must be reconstructed.

So the final objectives are:
* Compressing data without losing data
* Statistical coding - more frequently used symbols should
have shorter code words
* Information transmission in fewest possible bits

## Data Structures 
In my project implementation I have used the priority queue and
the binary tree as data structures.
Binary tree is a tree data structure in which each node has at most two
children, which are referred to as the left child and the right child.
A priority queue is an abstract data-type in which each element
additionally has a "priority" associated with it. In a priority queue, an
element with high priority is served before an element with low priority.

## Space requirements and time target analysis
**Space requirement:**

O (n) The algorithm creates a tree with a
maximum of 2n - 1 elements.

**Time requirement:**

O (n log n) The time requirement for adding to the
stack is O (log n) and is done n times in the worst case.

## General assumptions 
The program gets the data to be compressed or decompressed into the
stdin and outputs the corresponding data to the stdout.

## Construction specification 
The compiler used during creating the project: clang 14.0.6

language: c++

language standard: 13

## Setup 
My script implementation is a command line program.
For the purpose of preparing my solution, I have learned how to use ‘make’ so it
is incipiently included. Therefore, to generate the “huff” executable file
you must use the command:

`$  make`

![Screenshot_43](https://user-images.githubusercontent.com/40866831/159994143-17466ce1-7b24-44cd-a8bd-0f8d9dd8ed17.png)

## Usage 
Program gleans two different options:

* --encode

* --decode

Furthermore it requires names of input and output files. 

The input file declaration stands without a parameter and output file is preceded by a “-o” flag, eg:

`$  ./huff –encode input_to_encode.txt -o encoded_output.txt`

`$  ./huff –decode encoded_input.txt -o decoded_output.txt`

Program called without any parameters prints a short manual:

![Screenshot_41](https://user-images.githubusercontent.com/40866831/159994048-c5b08253-53ab-4571-9780-85e1f78b3428.png)

Program called with incorrect input file name prints an error message:

![Screenshot_42](https://user-images.githubusercontent.com/40866831/159994177-c1cfc3b1-81cc-4b61-8231-c4f0f09c59c3.png)


##  Internal specification
The program is implemented with a structural paradigm. User
interface is separated from the program's logic.

## Internal code description
The program accepts the input file in the manner defined above.
Calculates the frequency of occurrences. On this basis creates a binary
tree - ”huffman tree” - and huffman code from these tree(traverse the
tree), encodes the tree data, after rewriting the bits to bytes, writes the
result to the output file.
When decoding, the previously encoded file is opened - the bytes are
converted into bits, the binary tree is regenerated on the basis of which
the date is decoded. Restoring the compressed data to its original form
is based on a data storage algorithm.

## Testing 
The program has been tested with various types of files. An empty
input file does not cause failure - an empty output file is created.
1 of the sample test provided is included into solution directory in img
folder. However, the script did not encounter any problems with slightly
larger files.

## Deficiencies 
* obtaining problems with large (or at least very large) files
* could be more responsive to error situations
* can reserve a significant amount of memory

## Sources for acquiring knowledge
* [huffman wiki](https://en.wikipedia.org/wiki/Huffman_coding)
* [Big-O cheatsheet](https://www.bigocheatsheet.com/)
* [Pragma Once usage tutorial](https://riptutorial.com/cplusplus/example/16851/sharppragma-once)
* [Efficient way of storing Huffman tree - stackoverflow](https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree)
* [geeks4geeks - little and big endian mystery](https://www.geeksforgeeks.org/little-and-big-endian-mystery/)
* [Stanford article about binary trees](http://cslibrary.stanford.edu/110/BinaryTrees.html)
* [Priority queue in data structures - simplilearn youtube](https://www.youtube.com/watch?v=XDxLEUgVDMM)
