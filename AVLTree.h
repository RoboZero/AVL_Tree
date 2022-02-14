//
// Created by tirio on 2/9/2022.
//

#ifndef PROJECTS_AVLTREE_H
#define PROJECTS_AVLTREE_H

#include<iostream>
#include<queue>
#include "TreeNode.h"

using namespace std;

//From Project 1 Breakdown
class AVLTree {

private:
    TreeNode* head;

    int getChildHeight(TreeNode* currentNode);
    bool isValidId(string id);
    void balance(TreeNode* currentNode, int balanceValue);

    TreeNode* rotateRight(TreeNode node);
    TreeNode* rotateLeft(TreeNode node);

    TreeNode* insertRecursive(TreeNode* currentNode, string name, string id);
    void deleteAllPostorder();

    void printPreorderRecursive(TreeNode* currentNode);
    void printInorderRecursive(TreeNode* currentNode);
    void printPostorderRecursive(TreeNode* currentNode);
    void deletePostorderRecursive(TreeNode* currentNode);

public:
    AVLTree();
    ~AVLTree();

    void insert(string name, string id);
    void remove(string id);
    void searchID(string id);
    void searchName(string name);

    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelorder();
    void printLevelCount();

    void removeInorder(int index);
};


#endif //PROJECTS_AVLTREE_H
