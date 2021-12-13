#include <iostream>

using namespace std;

template <class T>

class BTree{
private:
    T order;
public:
    BTree(T order){

        this->order = order;

    }



};



int main() {
    BTree<int> t1(3);


    return 0;
}
