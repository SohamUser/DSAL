#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, mark;
    cout << "Enter number of students: ";
    cin >> n;

    // Max-Heap for maximum marks
    priority_queue<int> maxHeap;

    // Min-Heap for minimum marks
    priority_queue<int, vector<int>, greater<int>> minHeap;

    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; i++) {
        cin >> mark;
        maxHeap.push(mark);
        minHeap.push(mark);
    }

    cout << "\n✅ Maximum Marks: " << maxHeap.top() << endl;
    cout << "✅ Minimum Marks: " << minHeap.top() << endl;

    return 0;
}
