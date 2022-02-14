//
// Created by tirio on 2/9/2022.
//

#ifndef PROJECTS_TREENODE_H
#define PROJECTS_TREENODE_H

#include <string>

using namespace std;

class TreeNode
{
public:
    string name;
    string id;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode()
    {
        name = "";
        id = "00000000";
        height = 0;
    }

    TreeNode(string _name, string _id)
    {
        name = _name;
        id = _id;
        height = 0;

        left = nullptr;
        right = nullptr;
    }
};

#endif //PROJECTS_TREENODE_H
