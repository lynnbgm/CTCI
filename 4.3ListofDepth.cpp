#include <iostream>
using namespace std;

// Data structure to store a binary tree node
struct Node
{
    int data;
    Node *left, *right, *next;

    // constructor
    Node(int data)
    {
        this->data = data;
        this->left = this->right = this->next = nullptr;
    }
};

// Function to print a given linked list
void printList(Node* head)
{
    while (head)
    {
        cout << head->data << " —> ";
        head = head->next;
    }

    cout << "null" << endl;
}

// Recursive function to find the first node in the next level of a given root node
Node* findNextNode(Node* root)
{
    // base case
    if (root == nullptr || root->next == nullptr) {
        return nullptr;
    }

    // if the left child of the root's next node exists, return it
    if (root->next->left) {
        return root->next->left;
    }

    // if the right child of the root's next node exists, return it
    if (root->next->right) {
        return root->next->right;
    }

    // if root's next node is a leaf node, recur for root's next node
    return findNextNode(root->next);
}

// Recursive function to link nodes present in each level of a binary tree
// in the form of a linked list
void linkNodes(Node* root)
{
    // base case
    if (root == nullptr) {
        return;
    }

    // ensure that the nodes of the current level are linked before the
    // next level nodes
    linkNodes(root->next);

    // Update the next pointer of root's left child to root's right child.
    // If the right child doesn't exist, link it to the first node in the next level.
    if (root->left) {
        root->left->next = (root->right)? root->right: findNextNode(root);
    }

    // update the next pointer of the root's right child to the first node
    // in the next level
    if (root->right) {
        root->right->next = findNextNode(root);
    }

    // recur for the left and right subtree
    linkNodes(root->left);
    linkNodes(root->right);
}

int main()
{
    /* Construct the following tree
             1
           /   \
          2     3
         / \     \
        4   5     6
         \       /
          7     8
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    root->left->left->right = new Node(7);
    root->right->right->left = new Node(8);

    // link nodes at the same level
    linkNodes(root);

    // print the nodes
    Node* node = root;
    while (node)
    {
        // print the current level
        printList(node);

        // find the leftmost node in the next level
        if (node->left) {
            node = node->left;
        }
        else if (node->right) {
            node = node->right;
        }
        else {
            node = findNextNode(node);
        }
    }

    return 0;
}
