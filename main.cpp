#include <iostream>

using namespace std;


template <class T,int m>

class BtreeNode{

private:
    //bool root = false;
    int order = m;
    int NUM_K = 0;
    T* keys;
    BtreeNode** children;
public:

    BtreeNode(){

        keys = new T[m-1];

        children = new BtreeNode*[m];
    }
    //This function is for testing only and it's not accurate
    void getKeys(){

        for(int i = 0 ; i < m ; i++){

            cout <<  keys[i] << endl;


        }

    }

    ~BtreeNode(){

        delete[] keys;
        delete[] children;
    }

template<class T,int m> friend class BTree;



};


template <class T,int m>

class BTree{

private:
    int order;
    BtreeNode<int,m> *root;

public:
    BTree(){
      root = nullptr;
        order = m;
    }

    void insert(T key){

        if (root == nullptr){

            root = new BtreeNode<T,m>;
            root->keys[0] = key;
            root->NUM_K++;
        }

    }




};



int main() {
    BTree<int,3> t1;




    return 0;
}
