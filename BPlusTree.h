// Implementation of B+ Tree
// supports key dublicates
// The tree was designed to produce the same result as the visualisation
//   at https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html
// Insertion algorithm description taken from
//  http://www.cburch.com/cs/340/reading/btree/index.html

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "Typedefs.h"

using Key   = int;
using Value = ImageInfo;

class BPlusNode {

public:
    friend class BPlusTree;

    unsigned int d;  // branching factor
    bool isLeaf;

    vector<Key> keys;

    BPlusNode * parent;
    BPlusNode * next;

    vector<BPlusNode*> kids; // TODO child nodes either a BPlusNode * or a Value
    vector<Value> vals;

public:
    BPlusNode( bool isLeaf = false, BPlusNode* parent = nullptr, int d = 4);

    inline bool isFull() { return keys.size() >= d-1; }

    /* Finds the number of keys smaller than k in this node
       returns the index of this key in keys */
    int keyRank(const Key & k);
    /* Look for the node*/
    BPlusNode * search(Key k);
    void insert(const Key & key, const Value & val);

//private:
    void insertLeaf(const Key &key, const Value & val);
    void insertNonLeaf(const Key &key, BPlusNode * node);
    BPlusNode * splitNode(BPlusNode * node);

public:
    string toString();

};

class BPlusTree {
public:
//private:
    BPlusNode * root;
    unsigned int d; // branching factor

public:
    BPlusTree(unsigned int branching_factor = 4);
    void insert(const Key & key, const Value & val);

    inline BPlusNode * search(const Key & key) {return root->search(key);}
    inline string toString() {return root->toString();}
};


#endif // BPLUSTREE_H
