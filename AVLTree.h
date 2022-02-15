//
// Created by tirio on 2/9/2022.
//

#ifndef PROJECTS_AVLTREE_H
#define PROJECTS_AVLTREE_H

#include <iostream>
#include <queue>
#include <vector>
#include "TreeNode.h"

using namespace std;

//From Project 1 Breakdown
class AVLTree {

private:
    TreeNode* head;

    int getHeight(TreeNode* currentNode);
    int updateHeight(TreeNode* currentNode);

    bool isValidName(string name);
    bool isValidId(string id);

    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateLeftRight(TreeNode* node);
    TreeNode* rotateRightLeft(TreeNode* node);

    TreeNode* insertRecursive(TreeNode* currentNode, string name, string id);
    TreeNode* searchIdRecursive(TreeNode* currentNode, string id);
    TreeNode* removeIdRecursive(TreeNode* currentNode, string id);
    void deleteAllPostorder();

    void preorder(queue<TreeNode*>& allNodes);
    void inorder(queue<TreeNode*>& allNodes);
    void postorder(queue<TreeNode*>& allNodes);
    void levelorder(queue<pair<TreeNode*, int>>& allNodes);

    void preorderRecursive(TreeNode* currentNode, queue<TreeNode*>& allNodes);
    void inorderRecursive(TreeNode* currentNode, queue<TreeNode*>& allNodes);
    void postorderRecursive(TreeNode* currentNode, queue<TreeNode*>& allNodes);

public:
    AVLTree();
    ~AVLTree();

    void insert(string name, string id);
    void remove(string id);
    void searchId(string id);
    void searchName(string name);
    string getName(string id);
    vector<string> getIds(string name);

    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelorder();
    void printLevelCount();

    void removeInorder(int index);

    //For testing, but works on it's own.
    void getNamesInorder(vector<string>& names);
    void getIdsInorder(vector<string>& ids);
    void getNamesLevelorder(vector<string>& names);
    void getIdsLevelorder(vector<string>& ids);
    int getLevelCount();
};


#endif //PROJECTS_AVLTREE_H
