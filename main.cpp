#include <iostream>

using namespace std;

template <class T,int M>

class BTree{
private:
    T order;
public:
    BTree(){

        this->order = M;

    }



};



int main() {
    BTree<int,3> t1();


    return 0;
}
