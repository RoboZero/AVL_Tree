cmake_minimum_required(VERSION 3.21)
project(Projects)

set(CMAKE_CXX_STANDARD 11)

add_executable(Projects main.cpp AVLTree.cpp AVLTree.h TreeNode.h AVLTree_Tests.cpp)
