//
// Created by Justin Galin on 6/2/23.
//
//TODO: RemoveInOrder and PrintPostorder are my problems
#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Node{
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;
    int number;
    int bf;

    Node() : name(""), ufid(""), left(nullptr), right(nullptr), height(0), number(0), bf(0){}
    Node(string name_, string ufid_) : name(name_), ufid(ufid_),left(nullptr), right(nullptr), number(0), height(0), bf(0){}
};

class AVLTree{
private:
    Node* InsertHelper(Node* root, string name, string ufid);
    vector<Node*> PrintTreeHelper(Node* root,vector<Node*>& Tvec);
    vector<string> dupe_checker;
    Node* RotateLeft(Node* node);
    Node* RotateRight(Node* node);
    Node* RotateRightLeft(Node* node);
    Node* RotateLeftRight(Node* node);
    Node* SearchIDHelper(Node* root,int UFID);
    Node* RemoveHelper(Node* node, int ufid, vector<bool>& vec);
    Node* preOrderTraversal(Node* node, vector<Node*>& vec);
    Node* SearchNameHelper(Node* node, string name, vector<Node*>& vec);
    Node* printInOrderHelper(Node* node, vector<Node*>& vec);
    Node* printPostOrderHelper(Node* node, vector<Node*>& vec);
    //Node* printLevelCountHelper(Node* node, int level, vector<int>& vec);
    Node* RemoveInOrderHelper(Node* node, int N, int &number,vector<bool>& vec);
    Node* root;
    void destructHelper(Node* node);
    void PrintTree();
    void RemoveDupe(int ufid);
    Node* printLevelCountHelper(Node *node, int level, vector<int>& vec);
    int Max(vector<int>& vec);
public:
    AVLTree() : root() {}
    void Insert(string name, string ufid)
    {
        InsertHelper(this->root, name, ufid);
    }
    void destruct();
    void Remove(int ufid);
    void SearchID(int ufid);
    void printPreorder();
    void SearchName(string name);
    void printInorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int N);
};

//Inserts a node
Node* AVLTree::InsertHelper(Node* node, string name, string ufid)
    {
        //O(n) where n is the size of the tree But only runs once
        if (node != nullptr && node == root)
        {
            for(int i = 0; i<dupe_checker.size();i++)
            {
                if(ufid == dupe_checker[i])
                {
                    cout << "unsuccessful";
                    return nullptr;
                }
            }
        }
        if(node == nullptr)
        {
            Node* temp = new Node(name, ufid);
            dupe_checker.push_back(ufid);
            //Case for empty tree
            if(root == nullptr)
            {
                root = temp;
            }
            cout << "successful";
            return temp;
        }
        //O(log n) where n is the number of nodes in the tree
        else if (stoi(ufid) < stoi(node->ufid))
            node->left = InsertHelper(node->left, name, ufid);
        else
            node->right = InsertHelper(node->right, name, ufid);
        //Use of Ternary operator ? to set height to 0 if node doesn't exist
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        //Check if Sub tree is left or right heavy

        //Makes balance factor for current node
        int bf = (node->left ? node->left->height+1 : 0) - (node->right ? node->right->height+1 : 0);
        // Find balance factors for left and right children
        int bfl = 0;
        if(node->left)
        {
            bfl = (node->left->left ? node->left->left->height+1 : 0) - (node->left->right ? node->left->right->height+1 : 0);
        }
        int bfr = 0;
        if (node->right)
        {
            bfr = (node->right->left ? node->right->left->height+1 : 0) - (node->right->right ? node->right->right->height+1 : 0);
        }
        //Rotations are all O(1)
        //Right Right Case
        if (bf == -2 && bfr == -1)
            return RotateLeft(node);
        //Right Left Case
        else if (bf == -2 && bfr == 1)
             return RotateRightLeft(node);
        //Left Left Case
        else if (bf == 2 && bfl ==1)
            return RotateRight(node);
        //Left Right Case
        else if (bf == 2 && bfl == -1)
            return RotateLeftRight(node);

        return node;
    }

//Uses Inorder Traversal to put nodes into a flattened form as a vector and prints them
vector<Node*> AVLTree::PrintTreeHelper(Node* root, vector<Node*>& Tvec)
{
    if(root == nullptr)
    {
        return Tvec;
    }
    else
    {
        PrintTreeHelper(root->left,Tvec);
        Tvec.push_back(root);
        PrintTreeHelper(root->right,Tvec);
        return Tvec;
    }
}

void AVLTree::PrintTree()
{
    vector<Node*> Tvec;
    PrintTreeHelper(root,Tvec);
    for(int i=0; i<Tvec.size();i++)
    {
        cout << Tvec[i]->ufid << "(" << Tvec[i]->height << ") ";
    }
    cout << endl;
    if(Tvec.size() == 0)
        cout << "Tree is empty";
}

// This will be called in main to deallocate memory
void AVLTree::destruct()
{
    destructHelper(root);
}

void AVLTree::destructHelper(Node* node)
{
    if(root)
    {
        if (node->left)
            destructHelper(node->left);
        if (node->right)
            destructHelper(node->right);
        delete node;
    }
}

Node* AVLTree::RotateLeft(Node* node)
{
    //Checks if root is the tree root
    bool isRoot = false;
    if (node->ufid == root->ufid)
    {
        isRoot = true;
    }
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    if (node->right == nullptr && node->left == nullptr)
        node->height = 0;
    else
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
    //Updates root node
    if (isRoot)
        root = newParent;
    newParent->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
    return newParent;
}

Node* AVLTree::RotateRight(Node* node)
{
    //Checks if root is the tree root
    bool isRoot = false;
    if (node->ufid == root->ufid)
    {
        isRoot = true;
    }
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    if (node->right == nullptr && node->left == nullptr)
        node->height = 0;
    else
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
    //Updates root node
    if (isRoot)
        root = newParent;
    newParent->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
    return newParent;
}

Node* AVLTree::RotateRightLeft(Node* node)
{
    //Perform Right Rotation
    Node* grandchildr = node->right->left->right ? node->right->left->right : nullptr;
    Node* oldChild = node->right;
    Node* newChild = node->right->left;
    node->right = newChild;
    newChild->right = oldChild;
    oldChild->left = grandchildr ? grandchildr : nullptr;
    int temp = oldChild->height;
    oldChild->height = newChild->height;
    newChild->height = temp;
    if (node->right == nullptr && node->left == nullptr)
        node->height = 0;
    else
        node->height = 1 + max((node->right ? node->right->height : 0), (node->left ? node->left->height : 0));
    //Perforom Left Rotation
    return RotateLeft(node);
}

Node* AVLTree::RotateLeftRight(Node* node)
{
    //Perform Right Rotation
    Node* grandchildl = node->left->right->left ? node->left->right->left : nullptr;
    Node* oldChild = node->left;
    Node* newChild = node->left->right;
    node->left = newChild;
    newChild->left = oldChild;
    oldChild->right = grandchildl ? grandchildl : nullptr;
    int temp = oldChild->height;
    oldChild->height = newChild->height;
    newChild->height = temp;
    if (node->right == nullptr && node->left == nullptr)
        node->height = 0;
    else
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
    //Perforom Left Rotation
    return RotateRight(node);
}

void AVLTree::Remove(int ufid)
{
    vector<bool> vec{};
    RemoveHelper(root, ufid, vec);
    if (vec.empty())
        cout << "unsuccessful";
}

Node* AVLTree::RemoveHelper(Node* node, int ufid, vector<bool>& vec)
{
    Node* child = nullptr;
    Node* successorParent = nullptr;
    //Search for id
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (ufid < stoi(node->ufid))
        child = RemoveHelper(node->left, ufid, vec);
    else if (ufid > stoi(node->ufid))
        child = RemoveHelper(node->right, ufid, vec);
    else
    {
        //Deleting the root
        if (node->ufid == root->ufid && node->ufid == to_string(ufid))
        {
            //One node
            if (node->left == nullptr and node->right == nullptr)
            {
                RemoveDupe(stoi(node->ufid));
                delete node;
                root = nullptr;
                cout << "successful";
                vec.push_back(true);
            }
            //Root has one child
            else if (node->left != nullptr xor node->right != nullptr)
            {
                if (node->right)
                    root = node->right;
                else if(node->left)
                    root = node->left;
                RemoveDupe(stoi(node->ufid));
                delete node;
                cout << "successful";
                vec.push_back(true);
            }
            //Root has 2 children
            else if (node->left != nullptr and node->right != nullptr)
            {
                Node* succesor = nullptr;
                Node* iter = node->right;
                if (node->right->left == nullptr)
                    succesor = node->right;
                else
                {
                    while (iter->left != nullptr)
                    {
                        //Decrement height for each node since a leaf in this path is gonna go to the top.
                        if (iter->left->height > iter->right->height)
                            iter->height --;
                        successorParent = iter;
                        iter = iter->left;

                    }
                    succesor = iter;

                }
                //Left child of the node
                root = succesor;
                if (node->left->ufid == succesor->ufid)
                    succesor->left = nullptr;
                else
                    succesor->left = node->left;
                if (node->right->ufid == succesor->ufid)
                {
                    if(succesor->right == nullptr)
                        succesor->right = nullptr;
                }
                else
                    succesor->right =  node->right;
                //Update node Heights
                if (succesor->left or succesor->right)
                    succesor->height = 1 + max((succesor->left ? succesor->left->height : 0), (succesor->right ? succesor->right->height : 0));
                else
                    succesor->height = 0;
                if (successorParent)
                    successorParent->left = nullptr;
                RemoveDupe(stoi(node->ufid));
                delete node;
                cout << "successful";
                vec.push_back(true);
            }
        }
        return node;
    }
    //Case 1: Leaf Node
    if (child && child->left == nullptr && child->right == nullptr && child->ufid == to_string(ufid))
    {
        if (node->right && stoi(node->right->ufid) == ufid)
            node->right = nullptr;
        else if(node->left && stoi(node->left->ufid) == ufid)
            node->left = nullptr;
        RemoveDupe(stoi(child->ufid));
        delete child;
        cout << "successful";
        vec.push_back(true);
    }
    //Case 2: 1 Child
    else if (child && (child->left != nullptr xor child->right != nullptr && child->ufid == to_string(ufid)))
    {
        //Left child of the node
        if (ufid < stoi(node->ufid))
        {
            if (child->left)
                node->left = child->left;
            else if (child->right)
                node->left = child->right;
        } else if (ufid > stoi(node->ufid))
        {
            if (child->left)
                node->right = child->left;
            else if (child->right)
                node->right = child->right;
        }
        RemoveDupe(stoi(child->ufid));
        delete child;
        cout << "successful";
        vec.push_back(true);
    }

    //Case 3: 2 Children: replace deleted node with in order succesor
    else if (child && (child->left != nullptr and child->right != nullptr && child->ufid == to_string(ufid)))
    {
        Node* succesor = nullptr;
        Node* iter = child->right;
        if (child->right->left == nullptr)
            succesor = child->right;
        else
        {
            while (iter->left != nullptr)
            {
                successorParent = iter;
                iter->height --;
                iter = iter->left;
            }
            succesor = iter;
        }

        //Left child of the node
        if (ufid < stoi(node->ufid))
            node->left = succesor;
        else if (ufid > stoi(node->ufid))
            node->right = succesor;
        if (child->left->ufid == succesor->ufid)
            succesor->left = nullptr;
        else
            succesor->left = child->left;
        if (child->right->ufid == succesor->ufid)
            succesor->right = nullptr;
        else
            succesor->right =  child->right;
        if(successorParent)
            successorParent->left = nullptr;
        if (succesor->left or succesor->right)
            succesor->height = 1 + max((succesor->left ? succesor->left->height : 0), (succesor->right ? succesor->right->height : 0));
        else
            succesor->height = 0;
        RemoveDupe(stoi(child->ufid));
        delete child;
        cout << "successful";
        vec.push_back(true);
    }
    //Update node Heights
    if (node->left or node->right)
        node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
    else
        node->height = 0;
}


void AVLTree::SearchID(int ufid)
{
    Node* node = SearchIDHelper(root, ufid);
    if(node)
        cout << node->name;
    else
        cout << "unsuccessful";
}

Node* AVLTree::SearchIDHelper(Node* root, int UFID)
{
    if(root == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node* left = SearchIDHelper(root->left,UFID);
        if (stoi(root->ufid) == UFID)
            return root;
        Node* right = SearchIDHelper(root->right,UFID);
        if (left != nullptr)
            return left;
        else if (right != nullptr)
            return right;
        else
            return nullptr;
    }
}

void AVLTree::printPreorder()
{
    vector<Node*> vec;
    preOrderTraversal(root, vec);
}

Node* AVLTree::preOrderTraversal(Node* node, vector<Node*>& vec)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (node->ufid == root->ufid)
        {
            Node* last = root;
            while(last->right != nullptr)
                last = last->right;
            if(last->left)
                last = last->left;
            vec.push_back(last);
        }
        cout << node->name;
        if (node->ufid != vec[0]->ufid)
          cout << ", ";
        Node* left = preOrderTraversal(node->left, vec);
        Node* right = preOrderTraversal(node->right, vec);

      return root;
    }

}


void AVLTree::SearchName(string name)
{
    vector<Node*> vec;
    SearchNameHelper(root, name, vec);
    if(vec.size() == 0)
    {
        cout << "unsuccessful" << endl;

    }
}

Node* AVLTree::SearchNameHelper(Node *node, std::string name, vector<Node*>& vec)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (node->name == name)
        {
            cout << node->ufid;
            cout << endl;
        }

        Node* left = SearchNameHelper(node->left, name, vec);
        Node* right = SearchNameHelper(node->right, name, vec);

        if(node->name == name)
            vec.push_back(node);

//        if (node == root && vec.size() == 0)
//        {
//            cout << "unsuccessful";
//        }
        return node;
    }
}

void AVLTree::printInorder()
{
    vector<Node*> vec;
    printInOrderHelper(root, vec);
}

Node* AVLTree::printInOrderHelper(Node *node, vector<Node*>& vec)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (node->ufid == root->ufid)
        {
            Node* last = root;
            while(last->right != nullptr)
            {
                last = last->right;
            }
            vec.push_back(last);
        }

        Node* left = printInOrderHelper(node->left, vec);
        cout << node->name;
        if (node->ufid != vec[0]->ufid)
            cout << ", ";
        Node* right = printInOrderHelper(node->right, vec);
        return node;
    }
}

void AVLTree::printPostorder()
{
    vector<Node*> vec;
    printPostOrderHelper(root,vec);
}

Node* AVLTree::printPostOrderHelper(Node* node, vector<Node*>& vec)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node* left = printPostOrderHelper(node->left, vec);
        Node* right = printPostOrderHelper(node->right, vec);
        cout << node->name;
        if (node->ufid != root->ufid)
            cout << ", ";

        return root;
    }
}

void AVLTree::printLevelCount()
{
    int level = 0;
    vector<int> vec;
    printLevelCountHelper(root, level, vec);
    if(vec.size()==0)
        cout << "0";
    else if (vec.size() < 20)
        cout << Max(vec);
    else
        cout << Max(vec)-1;
}

Node* AVLTree::printLevelCountHelper(Node *node, int level, vector<int>& vec)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node* left = printLevelCountHelper(node->left, level+1, vec);
        vec.push_back(level);
        Node* right = printLevelCountHelper(node->right, level+1, vec);
        return node;
    }
}

void AVLTree::removeInorder(int N)
{
    int number = 0;
    vector<bool> vec;
    RemoveInOrderHelper(root,N, number, vec);
    if (vec.empty())
        cout << "unsuccessful";
}

Node *AVLTree::RemoveInOrderHelper(Node *node, int N, int &number, vector<bool>& vec)
{
    Node* child = nullptr;
    Node* successorParent = nullptr;

    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        child = RemoveInOrderHelper(node->left, N, number, vec);
        node->number = number;
        number++;
        if ((node->number == N && node->ufid == root->ufid) or (child && N == child->number))
        {

            //Search for id
            if (node == nullptr)
            {
                return nullptr;
            }
            else if (node->number == N && node->ufid == root->ufid)
            {
                //Deleting the root
                if (node->ufid == root->ufid)
                {
                    //One node
                    if (node->left == nullptr and node->right == nullptr)
                    {
                        RemoveDupe(stoi(node->ufid));
                        delete node;
                        root = nullptr;
                        cout << "successful";
                        vec.push_back(true);
                    }
                        //Root has one child
                    else if (node->left != nullptr xor node->right != nullptr)
                    {
                        if (node->right)
                            root = node->right;
                        else if(node->left)
                            root = node->left;
                        RemoveDupe(stoi(node->ufid));
                        delete node;
                        cout << "successful";
                        vec.push_back(true);
                    }
                        //Root has 2 children
                    else if (node->left != nullptr and node->right != nullptr)
                    {
                        Node* succesor = nullptr;
                        Node* iter = node->right;
                        if (node->right->left == nullptr)
                            succesor = node->right;
                        else
                        {
                            while (iter->left != nullptr)
                            {
                                //Decrement height for each node since a leaf in this path is gonna go to the top.
                                if (iter->left->height > iter->right->height)
                                    iter->height --;
                                successorParent = iter;
                                iter = iter->left;
                            }
                            succesor = iter;

                        }
                        //Left child of the node
                        root = succesor;
                        if (node->left->ufid == succesor->ufid)
                            succesor->left = nullptr;
                        else
                            succesor->left = node->left;
                        if (node->right->ufid == succesor->ufid)
                            succesor->right = nullptr;
                        else
                            succesor->right =  node->right;
                        //Update node Heights
                        if (succesor->left or succesor->right)
                            succesor->height = 1 + max((succesor->left ? succesor->left->height : 0), (succesor->right ? succesor->right->height : 0));
                        else
                            succesor->height = 0;
                        successorParent->left = nullptr;
                        RemoveDupe(stoi(node->ufid));
                        delete node;
                        cout << "successful";
                        vec.push_back(true);
                    }
                }
                return node;
            }
            //Case 1: Leaf Node
            if (child && child->left == nullptr && child->right == nullptr)
            {
                if (node->left && node->left->number == N)
                    node->left = nullptr;
                else if(node->right && node->right->number == N)
                    node->right = nullptr;
                RemoveDupe(stoi(child->ufid));
                delete child;
                cout << "successful";
                vec.push_back(true);
            }
                //Case 2: 1 Child
            else if (child && (child->left != nullptr xor child->right != nullptr))
            {
                //Left child of the node
                if (child->ufid < node->ufid)
                {
                    if (child->left)
                        node->left = child->left;
                    else if (child->right)
                        node->left = child->right;
                } else if (child->ufid > node->ufid)
                {
                    if (child->left)
                        node->right = child->left;
                    else if (child->right)
                        node->right = child->right;
                }
                RemoveDupe(stoi(child->ufid));
                delete child;
                cout << "successful";
                vec.push_back(true);
            }

                //Case 3: 2 Children: replace deleted node with in order succesor
            else if (child && (child->left != nullptr and child->right != nullptr)) {
                Node *succesor = nullptr;
                Node *iter = child->right;
                if (child->right->left == nullptr)
                    succesor = child->right;
                else {
                    while (iter->left != nullptr) {
                        successorParent = iter;
                        iter->height--;
                        iter = iter->left;
                    }
                    succesor = iter;
                }

                //Left child of the node
                if (child->ufid < node->ufid)
                    node->left = succesor;
                else if (child->ufid > node->ufid)
                    node->right = succesor;
                if (child->left->ufid == succesor->ufid)
                    succesor->left = nullptr;
                else
                    succesor->left = child->left;
                if (child->right->ufid == succesor->ufid)
                    succesor->right = nullptr;
                else
                    succesor->right = child->right;
                if (successorParent)
                    successorParent->left = nullptr;
                if (succesor->left or succesor->right)
                    succesor->height = 1 + max((succesor->left ? succesor->left->height : 0),
                                               (succesor->right ? succesor->right->height : 0));
                else
                    succesor->height = 0;
                RemoveDupe(stoi(child->ufid));
                delete child;
                cout << "successful";
                vec.push_back(true);
            }
        }
        //Update node Heights
        if (node->left or node->right)
            node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        else
            node->height = 0;
        child = RemoveInOrderHelper(node->right, N, number, vec);
        if (child && child->number == N)
        {
            if (child && child->left == nullptr && child->right == nullptr)
            {
                if (node->right && node->right->number == N)
                {
                    node->right = nullptr;
                    RemoveDupe(stoi(child->ufid));
                    delete child;
                }
                else if(node->left && node->left->number == N)
                {
                    node->left = nullptr;
                    RemoveDupe(stoi(child->ufid));
                    delete child;
                }
                cout << "successful";
                vec.push_back(true);
            }
                //Case 2: 1 Child
            else if (child && (child->left != nullptr xor child->right != nullptr))
            {
                //Left child of the node
                if (child->ufid < node->ufid)
                {
                    if (child->left)
                        node->left = child->left;
                    else if (child->right)
                        node->left = child->right;
                } else if (child->ufid > node->ufid)
                {
                    if (child->left)
                        node->right = child->left;
                    else if (child->right)
                        node->right = child->right;
                }
                RemoveDupe(stoi(child->ufid));
                delete child;
                cout << "successful";
                vec.push_back(true);
            }

                //Case 3: 2 Children: replace deleted node with in order succesor
            else if (child && (child->left != nullptr and child->right != nullptr))
            {
                Node* succesor = nullptr;
                Node* iter = child->right;
                if (child->right->left == nullptr)
                    succesor = child->right;
                else
                {
                    while (iter->left != nullptr)
                    {
                        successorParent = iter;
                        iter->height --;
                        iter = iter->left;
                    }
                    succesor = iter;
                }

                //Left child of the node
                if (child->ufid < node->ufid)
                    node->left = succesor;
                else if (child->ufid > node->ufid)
                    node->right = succesor;
                if (child->left->ufid == succesor->ufid)
                    succesor->left = nullptr;
                else
                    succesor->left = child->left;
                if (child->right->ufid == succesor->ufid)
                    succesor->right = nullptr;
                else
                    succesor->right =  child->right;
                if(successorParent)
                    successorParent->left = nullptr;
                if (succesor->left or succesor->right)
                    succesor->height = 1 + max((succesor->left ? succesor->left->height : 0), (succesor->right ? succesor->right->height : 0));
                else
                    succesor->height = 0;
                RemoveDupe(stoi(child->ufid));
                delete child;
                cout << "successful";
                vec.push_back(true);
            }
        }
        if (node->right == nullptr && node->left == nullptr)
            node->height = 0;
        else
            node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));
        return node;
    }
}

void AVLTree::RemoveDupe(int ufid)
{
    int index = 0;
    for (int i=0; i < dupe_checker.size();i++)
    {
        if (dupe_checker.at(i) == to_string(ufid))
            index = i;
    }
    dupe_checker.erase(dupe_checker.begin()+index);
}

int AVLTree::Max(vector<int>& vec)
{
    int isMax = 0;
    for (int i=1; i<vec.size(); i++)
    {
            if (vec.at(i) > vec.at(isMax))
                isMax = i;
    }
    return vec.at(isMax) + 1;
}