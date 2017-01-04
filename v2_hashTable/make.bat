if exist EKTAppV2.exe rm EKTAppV2.exe
g++ -I -g -Wall -o EKTAppV2 EKTAppV2.cpp hash.cpp hashList.cpp BinaryNode.h BinarySearchTree.h Entry.cpp -std=gnu++11