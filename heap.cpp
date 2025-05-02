#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int main(){
    int n,marks;
    cout<<"Enter no of students : ";
    cin>>n;

    priority_queue<int> maxHeap;
    priority_queue<int,vector<int>,greater<int>> minHeap;

    cout<<"enter marks"<<endl;

    for(int i =0;i<n;i++){
        cin>>marks;
        maxHeap.push(marks);
        minHeap.push(marks);
    }

    cout<<"max :"<<maxHeap.top();
    cout<<"min :"<<minHeap.top();

    return 0;
}
