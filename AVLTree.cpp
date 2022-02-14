//
// Created by tirio on 2/9/2022.
//
#include "AVLTree.h"

AVLTree::AVLTree()
{
    head = nullptr;
}

AVLTree::~AVLTree()
{
    deleteAllPostorder();
}

bool AVLTree::isValidId(string id)
{
    bool isDigit = true;

    for(char c : id)
    {
        if(!isdigit(c))
            isDigit = false;
    }

    return isDigit;
}

void AVLTree::insert(string name, string id)
{
    //Do error checking/validate here.
    if(!isValidId(id)) return;

    TreeNode* insertedNode = insertRecursive(head, name, id);

    if(head == nullptr)
        head = insertedNode;
}

//Obtained from lecture notes
TreeNode* AVLTree::insertRecursive(TreeNode* currentNode, string name, string id)
{
    //Exit case: Can insert here.
    if(currentNode == nullptr)
    {
        cout << "successful" << endl;

        TreeNode* insertNode =  new TreeNode(name, id);
        insertNode->height = 1;

        return insertNode;
    }

    //Keep going
    int insertID = stoi(id);
    int nodeID = stoi(currentNode->id);

    if(insertID < nodeID)
        currentNode->left = insertRecursive(currentNode->left, name, id);
    else if(insertID > nodeID)
        currentNode->right = insertRecursive(currentNode->right, name, id);
    else //If equal
    {
        //Exit case: Do not insert duplicate values
        cout << "unsuccessful" << endl;
        return currentNode;
    }

    /*
    //Recurse back
    //Determine node height after potential insertion
    int leftHeight = GetChildHeight(currentNode->left);
    int rightHeight = GetChildHeight(currentNode->right);
    currentNode->height = 1 + max(leftHeight, rightHeight);

    //Balance
    int balance = leftHeight - rightHeight;

    bool leftHeavy = balance > 1;
    bool rightHeavy = balance < -1;

    if(leftHeavy)
    {
        //Check if should do left left or left right.
        int leftChildHeight = GetChildHeight(currentNode->left);
        int rightChildHeight = GetChildHeight(currentNode->right);

        bool leftRightHeavy =
    }
    else if (rightHeavy)
    {

    }
    */

    return currentNode;
}

int AVLTree::getChildHeight(TreeNode* childNode)
{
    //Helper that handles if childNode is null.

    if(childNode != nullptr)
        return childNode->height;
    else
        return 0;
}

void AVLTree::balance(TreeNode* currentNode, int balanceValue)
{

}

void AVLTree::printPreorder()
{
    if(head == nullptr) return;

    printPreorderRecursive(head);
}

//Preorder - NLR
void AVLTree::printPreorderRecursive(TreeNode* currentNode)
{
    cout << currentNode->name << ", ";

    if(currentNode->left != nullptr)
        printPreorderRecursive(currentNode->left);

    if(currentNode->right != nullptr)
        printPreorderRecursive(currentNode->right);
}

//O(n)
void AVLTree::printInorder()
{
    if(head == nullptr) return;

    printInorderRecursive(head);
}

//Inorder - LNR
void AVLTree::printInorderRecursive(TreeNode* currentNode)
{
    if(currentNode->left != nullptr)
        printInorderRecursive(currentNode->left);

    cout << currentNode->name << ", ";

    if(currentNode->right != nullptr)
        printInorderRecursive(currentNode->right);
}

//O(n)
void AVLTree::printPostorder()
{
    if(head == nullptr) return;

    printPostorderRecursive(head);
}

//O(n)
//Postorder - LRN
void AVLTree::printPostorderRecursive(TreeNode* currentNode)
{
    if(currentNode->left != nullptr)
        printPostorderRecursive(currentNode->left);

    if(currentNode->right != nullptr)
        printPostorderRecursive(currentNode->right);

    cout << currentNode->name << ", ";
}

void AVLTree::printLevelorder(){
    int currentLevel = 1;

    queue<TreeNode*> levelNodesQ;

    levelNodesQ.push(head);

    cout << "Level: " << currentLevel << endl;
    cout << head->name << " " << endl;

    currentLevel++;

    while(!levelNodesQ.empty())
    {
        bool displayedLevel = false;
        int levelSize = levelNodesQ.size();

        for(int i = 0; i < levelSize; i++)
        {
            TreeNode* currentNode = levelNodesQ.front();

            if(currentNode->left != nullptr)
            {
                if(!displayedLevel)
                {
                    cout << "Level: " << currentLevel << endl;
                    displayedLevel = true;
                }

                levelNodesQ.push(currentNode->left);
                cout << currentNode->left->name << " ";
            }

            if(currentNode->right != nullptr)
            {
                if(!displayedLevel)
                {
                    cout << "Level: " << currentLevel << endl;
                    displayedLevel = true;
                }

                levelNodesQ.push(currentNode->right);
                cout << currentNode->right->name << " ";
            }

            levelNodesQ.pop();
        }

        currentLevel++;
        cout << endl;
    }
}

//O(n)
void AVLTree::deleteAllPostorder()
{
    if(head == nullptr) return;

    deletePostorderRecursive(head);
}

void AVLTree::deletePostorderRecursive(TreeNode* currentNode)
{
    if(currentNode->left != nullptr)
        deletePostorderRecursive(currentNode->left);

    if(currentNode->right != nullptr)
        deletePostorderRecursive(currentNode->right);

    delete currentNode;
}

