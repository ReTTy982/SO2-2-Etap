
// C++ code to demonstrate the working of
// make_heap(), front()
#include <bits/stdc++.h>
using namespace std;

class HeapTest{
    public:
        int x;
        int y=10;
        HeapTest(int x){
            this -> x = x;
            }



};

bool compareByX(const HeapTest& obj1, const HeapTest& obj2){
    return obj1.x > obj2.x; 
}

int main()
{
    vector<HeapTest> v2;
    for(int i =0;i<10;i++){
        std::cout << i << std::endl;
        HeapTest obj = HeapTest(i);
        v2.push_back(obj);
    }

    make_heap(v2.begin(),v2.end(),compareByX);
    // Initializing a vector
    vector<int> v1 = { 20, 30, 40, 25, 15 };
    std::cout << v2.front().x << std::endl;
    // Converting vector into a heap
    // using make_heap()
    make_heap(v1.begin(), v1.end());
 
    // Displaying the maximum element of heap
    // using front()
    cout << "The maximum element of heap is : ";
    cout << v1.front() << endl;
 
    return 0;
}