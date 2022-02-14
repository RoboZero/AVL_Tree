#include <iostream>
#include "AVLTree.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << "Goodbye" << endl;

    AVLTree tree;

    tree.insert("2", "2");
    tree.insert("120", "120");
    tree.insert("12", "12");
    tree.insert("0", "0");
    tree.insert("4", "4");

    //tree.printInorder();
    tree.printLevelorder();

    return 0;
}
