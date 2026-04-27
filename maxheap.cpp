#include <iostream>
#include <queue>
using namespace std;

int main() {
    
    priority_queue<int> maxHeap;

    // Inserting elements
    maxHeap.push(20);
    maxHeap.push(40);
    maxHeap.push(60);
    maxHeap.push(2);

    cout << "Max Heap elements: ";

    while(!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }

    return 0;
}
