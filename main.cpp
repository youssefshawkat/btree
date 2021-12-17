// C++ program for B-Tree insertion
#include<iostream>
using namespace std;

// A BTree node
class BTreeNode
{
    int* keys; // An array of keys
    int t;	 // Minimum degree (defines the range for number of keys)
    int order; // order of the tree
    BTreeNode** children; // An array of child pointers
    int num_keys;	 // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(bool _leaf, int m)
    {
        t = ceiling(m / 2);
        leaf = _leaf;
        order = m;

        // Allocate memory for maximum number of possible keys
        // and child pointers
        keys = new int[order - 1];
        children = new BTreeNode * [order];

        // Initialize the number of keys as 0
        num_keys = 0;
    }

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k)
    {
        // Initialize index as index of rightmost element
        int i = num_keys - 1;

        // If this is a leaf node
        if (leaf == true)
        {
            // The following loop does two things
            // a) Finds the location of new key to be inserted
            // b) Moves all greater keys to one place ahead
            while (i >= 0 && keys[i] > k)
            {
                keys[i + 1] = keys[i];
                i--;
            }

            // Insert the new key at found location
            keys[i + 1] = k;
            num_keys = num_keys + 1;
        }
        else // If this node is not leaf
        {
            // Find the child which is going to have the new key
            while (i >= 0 && keys[i] > k)
                i--;

            // See if the found child is full
            if (children[i + 1]->num_keys == 2 * t - 1)
            {
                // If the child is full, then split it
                splitChild(i + 1, children[i + 1]);

                // After split, the middle key of C[i] goes up and
                // C[i] is splitted into two.  See which of the two
                // is going to have the new key
                if (keys[i + 1] < k)
                    i++;
            }
            children[i + 1]->insertNonFull(k);
        }
    }

    //rounding up
    int ceiling(float num)
    {
        int inum = (int)num;
        if (num == (float)inum) {
            return inum;
        }
        return inum + 1;
    }

    // A utility function to split the child y of this node. i is index of y in
    // child array C[]. The Child y must be full when this function is called
    void splitChild(int i, BTreeNode* y)
    {
        // Create a new node which is going to store (t-1) keys
        // of y
        BTreeNode* z = new BTreeNode(y->leaf, y->order);
        z->num_keys = t - 1;

        // Copy the last (t-1) keys of y to z
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        // Copy the last t children of y to z
        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                z->children[j] = y->children[j + t];
        }

        // Reduce the number of keys in y
        y->num_keys = t - 1;

        // Since this node is going to have a new child,
        // create space of new child
        for (int j = num_keys; j >= i + 1; j--)
            children[j + 1] = children[j];

        // Link the new child to this node
        children[i + 1] = z;

        // A key of y will move to this node. Find the location of
        // new key and move all greater keys one space ahead
        for (int j = num_keys - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        // Copy the middle key of y to this node
        keys[i] = y->keys[t - 1];

        // Increment count of keys in this node
        num_keys = num_keys + 1;
    }

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse()
    {
        // There are n keys and n+1 children, traverse through n keys
        // and first n children
        int i;
        for (i = 0; i < num_keys; i++)
        {
            // If this is not leaf, then before printing key[i],
            // traverse the subtree rooted with child C[i].
            if (leaf == false)
                children[i]->traverse();
            cout << " " << keys[i];
        }

        // Print the subtree rooted with last child
        if (leaf == false)
            children[i]->traverse();
    }


    // Make BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode* root; // Pointer to root node
    int t; // Minimum degree
    int order; // order of the tree
public:

    int ceiling(float num)
    {
        int inum = (int)num;
        if (num == (float)inum) {
            return inum;
        }
        return inum + 1;
    }

    // Constructor (Initializes tree as empty)
    BTree(int m)
    {
        root = NULL;
        t= ceiling(m/2);
        order = m;
    }

    // function to traverse the tree
    void traverse()
    {
        if (root != NULL) root->traverse();
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int k)
    {
        // If tree is empty
        if (root == NULL)
        {
            // Allocate memory for root
            root = new BTreeNode(true, order);
            root->keys[0] = k;  // Insert key
            root->num_keys = 1;  // Update number of keys in root
        }
        else // If tree is not empty
        {
            // If root is full, then tree grows in height
            if (root->num_keys == 2 * t - 1)
            {
                // Allocate memory for new root
                BTreeNode* s = new BTreeNode(false, order);

                // Make old root as child of new root
                s->children[0] = root;

                // Split the old root and move 1 key to the new root
                s->splitChild(0, root);

                // New root has two children now.  Decide which of the
                // two children is going to have new key
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->children[i]->insertNonFull(k);

                // Change root
                root = s;
            }
            else  // If root is not full, call insertNonFull for root
                root->insertNonFull(k);
        }
    }
};


// Driver program to test above functions
int main()
{
    BTree t(3); // A B-Tree of order 3
    t.insert(1);
    t.insert(5);
    t.insert(0);
    t.insert(4);
    t.insert(3);
    t.insert(2);


    cout << "Traversal of the constructed tree is: ";
    t.traverse();

    return 0;
}