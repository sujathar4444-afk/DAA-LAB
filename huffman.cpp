#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Node structure
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char d, int f) {
        data = d;
        freq = f;
        left = right = NULL;
    }
};

// Comparator for Min Heap
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to print Huffman Codes
void printCodes(Node* root, string code) {
    if (root == NULL)
        return;

    // Leaf node
    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " : " << code << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {

    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    vector<char> arr(n);
    vector<int> freq(n);

    cout << "Enter characters:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter frequencies:\n";
    for (int i = 0; i < n; i++)
        cin >> freq[i];

    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes
    for (int i = 0; i < n; i++)
        pq.push(new Node(arr[i], freq[i]));

    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    // Print codes
    printCodes(pq.top(), "");

    return 0;
}