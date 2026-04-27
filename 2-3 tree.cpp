#include <iostream>
using namespace std;

class Node {
public:
    int data[2];        // max 2 keys
    Node* child[3];     // max 3 children
    int count;          // number of keys

    Node(int val) {
        data[0] = val;
        count = 1;
        child[0] = child[1] = child[2] = NULL;
    }
};

class TwoThreeTree {
private:
    Node* root;

    // Utility to insert into node and split if needed
    Node* insertUtil(Node* node, int val, int &upKey) {
        if (node == NULL) {
            upKey = val;
            return NULL;
        }

        // Leaf node
        if (node->child[0] == NULL) {
            if (node->count == 1) {
                // Insert directly
                node->data[1] = val;
                node->count = 2;

                if (node->data[0] > node->data[1])
                    swap(node->data[0], node->data[1]);

                return NULL;
            } else {
                // Split leaf node
                int temp[3] = {node->data[0], node->data[1], val};

                // Sort 3 elements
                for (int i = 0; i < 3; i++)
                    for (int j = i + 1; j < 3; j++)
                        if (temp[i] > temp[j])
                            swap(temp[i], temp[j]);

                // Middle key goes up
                upKey = temp[1];

                // Left node
                node->data[0] = temp[0];
                node->count = 1;

                // Right node
                Node* newNode = new Node(temp[2]);

                return newNode;
            }
        }

        // Internal node
        int pos;
        if (val < node->data[0])
            pos = 0;
        else if (node->count == 1 || val < node->data[1])
            pos = 1;
        else
            pos = 2;

        int newKey;
        Node* newChild = insertUtil(node->child[pos], val, newKey);

        if (newChild == NULL)
            return NULL;

        // Insert promoted key
        if (node->count == 1) {
            // Insert into node
            if (pos == 0) {
                node->data[1] = node->data[0];
                node->data[0] = newKey;
                node->child[2] = node->child[1];
                node->child[1] = newChild;
            } else {
                node->data[1] = newKey;
                node->child[2] = newChild;
            }
            node->count = 2;
            return NULL;
        } else {
            // Split internal node
            int tempKeys[3];
            Node* tempChild[4];

            // Merge keys
            if (pos == 0) {
                tempKeys[0] = newKey;
                tempKeys[1] = node->data[0];
                tempKeys[2] = node->data[1];

                tempChild[0] = node->child[0];
                tempChild[1] = newChild;
                tempChild[2] = node->child[1];
                tempChild[3] = node->child[2];
            } else if (pos == 1) {
                tempKeys[0] = node->data[0];
                tempKeys[1] = newKey;
                tempKeys[2] = node->data[1];

                tempChild[0] = node->child[0];
                tempChild[1] = node->child[1];
                tempChild[2] = newChild;
                tempChild[3] = node->child[2];
            } else {
                tempKeys[0] = node->data[0];
                tempKeys[1] = node->data[1];
                tempKeys[2] = newKey;

                tempChild[0] = node->child[0];
                tempChild[1] = node->child[1];
                tempChild[2] = node->child[2];
                tempChild[3] = newChild;
            }

            // Promote middle key
            upKey = tempKeys[1];

            // Left node
            node->data[0] = tempKeys[0];
            node->count = 1;
            node->child[0] = tempChild[0];
            node->child[1] = tempChild[1];

            // Right node
            Node* newNode = new Node(tempKeys[2]);
            newNode->child[0] = tempChild[2];
            newNode->child[1] = tempChild[3];

            return newNode;
        }
    }

    void inorder(Node* node) {
        if (!node) return;

        if (node->count == 1) {
            inorder(node->child[0]);
            cout << node->data[0] << " ";
            inorder(node->child[1]);
        } else {
            inorder(node->child[0]);
            cout << node->data[0] << " ";
            inorder(node->child[1]);
            cout << node->data[1] << " ";
            inorder(node->child[2]);
        }
    }

public:
    TwoThreeTree() {
        root = NULL;
    }

    void insert(int val) {
        int upKey;
        Node* newChild = insertUtil(root, val, upKey);

        if (newChild != NULL) {
            // New root
            Node* newRoot = new Node(upKey);
            newRoot->child[0] = root;
            newRoot->child[1] = newChild;
            root = newRoot;
        }
    }

    void display() {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    TwoThreeTree t;

    int n, x;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> x;
        t.insert(x);
    }

    t.display();

    return 0;
}