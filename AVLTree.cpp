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

bool AVLTree::isValidName(string name)
{
    bool isCharacters = true;

    for(char c : name)
    {
        if(isdigit(c))
            isCharacters = false;
    }

    return isCharacters;
}

void AVLTree::insert(string name, string id)
{
    //Do error checking/validate here.
    if(!isValidId(id) || !isValidName(name))
    {
        cout << "unsuccessful";
        return;
    }

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

        //if(head == nullptr)
        //    head = insertNode;

        return insertNode;
    }

    //Not leaf, keep going
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

    //Inserted, recurring back.
    int balance = updateHeight(currentNode);

    bool leftHeavy = balance > 1;
    bool rightHeavy = balance < -1;

    if(rightHeavy)
    {
        TreeNode* rightChild = currentNode->right;
        int rightSubtreeBalance = getHeight(rightChild->left) - getHeight(rightChild->right);
        bool rightSubtreeLeftHeavy = rightSubtreeBalance == 1;

        TreeNode* newRoot;

        if(rightSubtreeLeftHeavy)
            newRoot = rotateRightLeft(currentNode);
        else
            newRoot = rotateLeft(currentNode);

        if(currentNode == head)
            head = newRoot;

        currentNode = newRoot;
    }
    else if (leftHeavy)
    {
        TreeNode* leftChild = currentNode->left;
        int leftSubtreeBalance = getHeight(leftChild->left) - getHeight(leftChild->right);
        bool leftSubtreeRightHeavy = leftSubtreeBalance == -1;

        TreeNode* newRoot;

        if(leftSubtreeRightHeavy)
            newRoot = rotateLeftRight(currentNode);
        else
            newRoot = rotateRight(currentNode);

        if(currentNode == head)
            head = newRoot;

        currentNode = newRoot;
    }

    return currentNode;
}

//Wrapper for accessing height. If nullptr, return 0.
int AVLTree::getHeight(TreeNode* node)
{
    if(node != nullptr)
        return node->height;
    else
        return 0;
}

//Updates height and returns updated balance. If node is null, return 0.
int AVLTree::updateHeight(TreeNode* currentNode)
{
    if(currentNode == nullptr) return 0;

    int leftHeight = getHeight(currentNode->left);
    int rightHeight = getHeight(currentNode->right);
    currentNode->height = 1 + max(leftHeight, rightHeight);

    int balance = leftHeight - rightHeight;
    return balance;
}

TreeNode* AVLTree::rotateLeft(TreeNode* node)
{
    TreeNode* previousRoot = node;
    TreeNode* newRoot = previousRoot->right;

    if(newRoot == nullptr) return node;

    TreeNode* nodeShiftedDown = newRoot->left;
    newRoot->left = previousRoot;
    previousRoot->right = nodeShiftedDown;

    updateHeight(previousRoot);
    updateHeight(nodeShiftedDown);
    updateHeight(newRoot);

    return newRoot;
}

TreeNode* AVLTree::rotateRight(TreeNode* node)
{
    TreeNode* previousRoot = node;
    TreeNode* newRoot = previousRoot->left;

    if(newRoot == nullptr) return node;

    TreeNode* nodeShiftedDown = newRoot->right;
    newRoot->right = previousRoot;
    previousRoot->left = nodeShiftedDown;

    updateHeight(previousRoot);
    updateHeight(nodeShiftedDown);
    updateHeight(newRoot);

    return newRoot;
}

TreeNode* AVLTree::rotateLeftRight(TreeNode* node)
{
    TreeNode* subRoot = rotateLeft(node->left);
    node->left = subRoot;

    TreeNode* newRoot = rotateRight(node);

    return newRoot;
}

TreeNode* AVLTree::rotateRightLeft(TreeNode* node)
{
    TreeNode* subRoot = rotateRight(node->right);
    node->right = subRoot;

    TreeNode* newRoot = rotateLeft(node);

    return newRoot;
};

void AVLTree::remove(string id)
{
    //Validate here
    if(!isValidId(id))
    {
        cout << "unsuccessful";
        return;
    }

    removeIdRecursive(head, id);
}

TreeNode* AVLTree::removeIdRecursive(TreeNode* currentNode, string id)
{
    if(currentNode == nullptr) return currentNode;

    int numId = stoi(id);
    int nodeId = stoi(currentNode->id);

    if(numId < nodeId)
        currentNode->left = removeIdRecursive(currentNode->left, id);
    else if(numId > nodeId)
        currentNode->right = removeIdRecursive(currentNode->right, id);
    else if(numId != nodeId && currentNode->left == nullptr && currentNode->right == nullptr)
    {
        cout << "unsuccessful";
        return currentNode;
    } else
    {
        if(currentNode->left == nullptr && currentNode->right == nullptr)
        {
            delete currentNode;
            return nullptr;
        }
        else if(currentNode->left == nullptr){
            TreeNode* rightChild = currentNode->right;
            delete currentNode;
            return rightChild;
        }
        else if(currentNode->right == nullptr) {
            TreeNode* leftChild = currentNode->left;
            delete currentNode;
            return leftChild;
        } else //Both children exist
        {
            //From lecture notes and from Geeks for Geeks.
            TreeNode* successorParent = currentNode;
            TreeNode* successor = currentNode->right;

            while(successor->left != nullptr)
            {
                successorParent = successor;
                successor = successor->left;
            }

            //Reattach it's parent
            if(successorParent != currentNode)
                successorParent->left = successorParent->right;
            else
                successorParent->right = successor->right;

            //Replace it with this node
            successor->left = currentNode->left;
            successor->right = currentNode->right;
            delete currentNode;
            return successor;
        }

        cout << "successful";
    }

    return currentNode;
}

//O(n * log n) could be better by only using remove logic for that node?
void AVLTree::removeInorder(int index)
{
    if(index < 0)
    {
        cout << "unsuccessful";
        return;
    }

    queue<TreeNode*> preorderNodes;
    preorder(preorderNodes);

    if(preorderNodes.size() < index)
        cout << "unsuccessful";

    bool success = false;
    int i = 0;

    while(i <= index)
    {
        preorderNodes.pop();
        i++;
    }

    //Remove logic
    remove(preorderNodes.front()->id);
}

//O(log n )
void AVLTree::searchId(string id)
{
    if(!isValidId(id))
    {
        cout << "unsuccessful";
        return;
    }


    TreeNode* searchedNode = searchIdRecursive(head, id);

    if(searchedNode != nullptr)
        cout << searchedNode->name;
    else
        cout << "unsuccessful";
}

//Return Id as string. If not found, returns ""
string AVLTree::getName(string id)
{
    TreeNode* searchedNode = searchIdRecursive(head, id);

    if(searchedNode != nullptr)
        return searchedNode->name;
    else
        return "";
}

TreeNode* AVLTree::searchIdRecursive(TreeNode* currentNode, string id)
{
    if(currentNode == nullptr) return nullptr;

    int numId = stoi(id);
    int nodeId = stoi(currentNode->id);

    TreeNode* foundNode;

    if(numId < nodeId)
        foundNode = searchIdRecursive(currentNode->left, id);
    else if(numId > nodeId)
        foundNode = searchIdRecursive(currentNode->right, id);
    else //if equal, found it!
        foundNode = currentNode;

    return foundNode;
}

//O(n * name length)
void AVLTree::searchName(string name)
{
    if(!isValidName(name))
    {
        cout << "unsuccessful";
        return;
    }

    //Pre-order traverse whole tree
    queue<TreeNode*> allNodes;

    preorder(allNodes);

    bool found = false;

    while(!allNodes.empty())
    {
        TreeNode* currentNode = allNodes.front();

        if(currentNode->name == name)
        {
            found = true;
            cout << currentNode->id << endl;
        }

        allNodes.pop();
    }

    if(found == false)
        cout << "unsuccessful";
}

vector<string> AVLTree::getIds(string name)
{
    //Pre-order traverse whole tree
    vector<string> ids;
    queue<TreeNode*> allNodes;

    preorder(allNodes);

    while(!allNodes.empty())
    {
        TreeNode* currentNode = allNodes.front();

        if(currentNode->name == name)
            ids.push_back(currentNode->id);

        allNodes.pop();
    }

    return ids;
}

void AVLTree::printPreorder()
{
    queue<TreeNode*> allNodes;

    preorder(allNodes);

    while (!allNodes.empty())
    {
        TreeNode* node = allNodes.front();

        if(allNodes.size() > 1)
            cout << node->name << ", ";
        else
            cout << node->name;

        allNodes.pop();
    }
}

void AVLTree::preorder(queue<TreeNode*>& allNodes)
{
    if(head == nullptr) return;

    preorderRecursive(head, allNodes);
}

//Preorder - NLR
void AVLTree::preorderRecursive(TreeNode* currentNode, queue<TreeNode*>& allNodes)
{
    allNodes.push(currentNode);

    if(currentNode->left != nullptr)
        preorderRecursive(currentNode->left, allNodes);

    if(currentNode->right != nullptr)
        preorderRecursive(currentNode->right, allNodes);
}

//O(n)
void AVLTree::printInorder()
{
    queue<TreeNode*> allNodes;

    inorder(allNodes);

    while (!allNodes.empty())
    {
        TreeNode* node = allNodes.front();

        if(allNodes.size() > 1)
            cout << node->name << ", ";
        else
            cout << node->name;

        allNodes.pop();
    }
}

void AVLTree::inorder(queue<TreeNode*>& allNodes)
{
    if(head == nullptr) return;

    inorderRecursive(head, allNodes);
}

//Inorder - LNR
void AVLTree::inorderRecursive(TreeNode* currentNode, queue<TreeNode*>& allNodes)
{
    if(currentNode->left != nullptr)
        inorderRecursive(currentNode->left, allNodes);

    allNodes.push(currentNode);

    if(currentNode->right != nullptr)
        inorderRecursive(currentNode->right, allNodes);
}

//O(n)
void AVLTree::printPostorder()
{
    queue<TreeNode*> allNodes;

    postorder(allNodes);

    while (!allNodes.empty())
    {
        TreeNode* node = allNodes.front();

        if(allNodes.size() > 1)
            cout << node->name << ", ";
        else
            cout << node->name;

        allNodes.pop();
    }
}

//O(n)
void AVLTree::deleteAllPostorder()
{
    if(head == nullptr) return;

    queue<TreeNode*> allNodes;

    postorder(allNodes);

    while(!allNodes.empty())
    {
        TreeNode* currentNode = allNodes.front();
        delete currentNode;
        allNodes.pop();
    }
}

void AVLTree::postorder(queue<TreeNode*>& allNodes)
{
    if(head == nullptr) return;

    postorderRecursive(head, allNodes);
}

//O(n)
//Postorder - LRN
void AVLTree::postorderRecursive(TreeNode* currentNode, queue<TreeNode*>& allNodes)
{
    if(currentNode->left != nullptr)
        postorderRecursive(currentNode->left, allNodes);

    if(currentNode->right != nullptr)
        postorderRecursive(currentNode->right, allNodes);

    allNodes.push(currentNode);
}

void AVLTree::printLevelorder()
{
    queue<pair<TreeNode*, int>> allNodes;

    levelorder(allNodes);

    if(allNodes.empty()) return;

    int level = allNodes.front().second;
    cout << "Level: " << level << endl;

    while(!allNodes.empty())
    {
        TreeNode* currentNode = allNodes.front().first;
        int currentLevel = allNodes.front().second;

        if(level != currentLevel)
        {
            //Next level
            cout << endl;
            cout << "Level: " << currentLevel << endl;
            level = currentLevel;
        }

        cout << currentNode->name << ", ";
        allNodes.pop();
    }
}

void AVLTree::getNamesInorder(vector<string>& names)
{
    queue<TreeNode*> allNodes;

    inorder(allNodes);

    while(!allNodes.empty())
    {
        names.push_back(allNodes.front()->name);
        allNodes.pop();
    }
}

void AVLTree::getIdsInorder(vector<string>& ids)
{
    queue<TreeNode*> allNodes;

    inorder(allNodes);

    while(!allNodes.empty())
    {
        ids.push_back(allNodes.front()->id);
        allNodes.pop();
    }
}

void AVLTree::getNamesLevelorder(vector<string>& names)
{
    queue<pair<TreeNode*, int>> allNodes;

    levelorder(allNodes);

    while(!allNodes.empty())
    {
        names.push_back(allNodes.front().first->name);
        allNodes.pop();
    }
}

void AVLTree::getIdsLevelorder(vector<string>& ids)
{
    queue<pair<TreeNode*, int>> allNodes;

    levelorder(allNodes);

    while(!allNodes.empty())
    {
        ids.push_back(allNodes.front().first->id);
        allNodes.pop();
    }
}

void AVLTree::levelorder(queue<pair<TreeNode*, int>>& allNodes)
{
    if(head == nullptr) return;

    int currentLevel = 1;

    queue<TreeNode*> levelNodesQ;
    levelNodesQ.push(head);
    allNodes.push(make_pair(head, currentLevel));

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
                levelNodesQ.push(currentNode->left);
                allNodes.push(make_pair(currentNode->left, currentLevel));
            }

            if(currentNode->right != nullptr)
            {
                levelNodesQ.push(currentNode->right);
                allNodes.push(make_pair(currentNode->right, currentLevel));
            }

            levelNodesQ.pop();
        }

        currentLevel++;
    }
}

void AVLTree::printLevelCount()
{
    int height = getHeight(head);

    cout << height << endl;
}

int AVLTree::getLevelCount()
{
    if(head == nullptr) return 0;

    return getHeight(head);
}