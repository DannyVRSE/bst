// similar structure to binary tree
// left<node<right
// each new node is a bst

#include <iostream>
#include <stdlib.h>
using namespace std;

struct node
{
    int root;
    struct node *left;
    struct node *right;
};

// empty tree
struct node *EmptyTree()
{
    return nullptr;
}

// new node insertion
struct node *newNode(int value, struct node *bst)
{
    // create node
    if (bst == nullptr)
    {
        struct node *newNode = new struct node;
        newNode->root = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // recursively add the value, making sure the smallest end up at the furthest left and biggest at furtherst right
    if (value < bst->root)
    {
        bst->left = newNode(value, bst->left);
    }
    else if (value > bst->root)
    {
        bst->right = newNode(value, bst->right);
    }
    else
    {
        cout << "Value already exists in the tree!" << endl;
        return bst; // return the unchanged tree
    }

    return bst;
}

// searching
bool search(int v, struct node *bst)
{
    struct node *temp = bst;
    if (temp == nullptr)
    {
        return false;
    }

    if (v == temp->root)
    {
        return true;
    }
    else if (v < temp->root)
        return search(v, temp->left);
    else if (v > temp->root)
    {
        return search(v, temp->right);
    };

    return false;
}

// ascending
void traverseInOrder(struct node *tree)
{
    if (tree != EmptyTree())
    {
        traverseInOrder(tree->left);
        cout << tree->root << endl;
        traverseInOrder(tree->right);
    }
}

// sort an array with tree
void sort(int a[10])
{
    struct node *t = EmptyTree();
    for (int i = 0; i <= (10 - 1); i++)
    {
        t = newNode(a[i], t);
    }
    traverseInOrder(t);
}

// find smallest node
struct node *findMin(struct node *bst)
{
    if (bst->left == EmptyTree())
    {
        return bst;
    }
    else
    {
        return findMin(bst->left);
    }
}

// delete
struct node *deleteNode(int v, struct node *bst)
{
    if (bst == nullptr)
    {
        throw invalid_argument("Value not found!");
    }

    // Traverse to the left subtree
    if (v < bst->root)
    {
        bst->left = deleteNode(v, bst->left);
    }
    // Traverse to the right subtree
    else if (v > bst->root)
    {
        bst->right = deleteNode(v, bst->right);
    }
    // Node to delete found
    else
    {
        // Case 1: No child (Leaf node)
        if (bst->left == nullptr && bst->right == nullptr)
        {
            delete bst;
            return nullptr;
        }
        // Case 2: One child (Left or Right child)
        else if (bst->left == nullptr)
        {
            struct node *temp = bst->right;
            delete bst;
            return temp;
        }
        else if (bst->right == nullptr)
        {
            struct node *temp = bst->left;
            delete bst;
            return temp;
        }
        // Case 3: Two children
        else
        {
            struct node *temp = findMin(bst->right);         // Find left-most node in right subtree
            bst->root = temp->root;                          // overwrite the node to be deleted
            bst->right = deleteNode(temp->root, bst->right); // Delete the successor
        }
    }

    return bst;
}

// all smaller
bool allSmaller(struct node *bst, int v)
{
    if (bst == nullptr)
    {
        return true;
    }

    if (bst->root < v)
    {
        return allSmaller(bst->left, v) && allSmaller(bst->right, v);
    }
    else
    {
        return false;
    }
}
// all bigger
bool allBigger(struct node *bst, int v)
{
    if (bst == nullptr)
    {
        return true;
    }

    if (bst->root > v)
    {
        return allBigger(bst->left, v) && allBigger(bst->right, v);
    }
    else
    {
        return false;
    }
}
// check if its a binary search tree

bool isBST(struct node *bst)
{
    if (bst == nullptr)
    {
        return true;
    }

    if (allSmaller(bst->left, bst->root) && allBigger(bst->right, bst->root) && isBST(bst->left) && isBST(bst->right))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// entry point
int main()
{
    struct node *bst = EmptyTree();
    bst = newNode(5, bst);
    bst = newNode(3, bst);
    bst = newNode(7, bst);
    bst = newNode(12, bst);

    isBST(bst) ? cout << "It is a BST!" << endl : cout << "It is not a BST!" << endl;
    
    traverseInOrder(bst);

    deleteNode(3, bst);

    traverseInOrder(bst);

    if (search(5, bst))
        cout << "Found 5!" << endl;
    else
        cout << "5 not found!" << endl;

    if (search(6, bst))
        cout << "Found 6!" << endl;
    else
        cout << "6 not found!" << endl;

    int a[10] = {10, 98, 25, 13, 6, 5, 12, 3, 2, 1};

    sort(a);

    return 0;
}