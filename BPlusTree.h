#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "Typedefs.h"

#include <sstream>
#include <iterator>

using Value = ImageInfo;

class BPlusNode {

public:
    friend class BPlusTree;

    int d;  // branching factor
    bool isLeaf;

    vector<int> keys;

    BPlusNode * parent;
    vector<BPlusNode*> kids; // child nodes

    // TODO? : these parameters can be stored in kids vector
    BPlusNode * next;  // pointer to the next leaf node
    vector<Value> vals;  // associated leaf values

    BPlusNode * prev; // pointer to the previous leaf node

public:
    BPlusNode( bool isLeaf = false, BPlusNode* parent = nullptr, int d = 4);

    inline bool isFull() { return keys.size() >= d-1; }

    /* Finds the number of keys smaller than k in this node
       returns the index of this key in keys */
    int keyRank(int k) {
        int i = 0;

        while (i < keys.size() && keys[i] < k )
            i++;

        return i;
    }

    BPlusNode * search(int k);

private:
    // A utility function
    // The leaf must be non-full when this function is called
    void insertNonFullLeaf(int k, const Value& val);

    // A utility function
    // The leaf must be full when this function is called
    void insertFullLeaf(int k, const Value& val);

    // A utility function
    // The root or an inner node must be non full when this function is called
    int insertNonFullNode(int k, BPlusNode * child);

    // A utility function
    // The root or an inner node must be full when this function is called
    void insertFullNode(int k, BPlusNode * child);

public:
    string toString();

};

class BPlusTree {

public:
    int d;
    BPlusNode * root;

public:
    BPlusTree(int branching_factor=4);

    inline BPlusNode * search(int k) { return root->search(k); }
    void insert(int k, const Value & val = Value());

    string toString() {return root->toString();}
};

#endif // BPLUSTREE_H
