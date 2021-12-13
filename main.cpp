#include <iostream>

using namespace std;


template <class T,int m>

class BtreeNode{

private:
    bool root = false;
    T* keys;
    BtreeNode** children;






};


template <class T,int m>

class BTree{

private:
    int order;

public:
    BTree(){

        order = m;

    }



};



int main() {
    BTree<int,3> t1;


    return 0;
}
