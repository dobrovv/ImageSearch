#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;
using Value = int;
using std::vector;

class BPNode {
public:
    friend class BPTree;

    int d;  // branching factor
    bool isLeaf;

    vector<int> keys;

    BPNode * parent;
    vector<BPNode*> kids; // child nodes

    // TODO? : these parameters can be stored in kids vector
    BPNode * next;  // explicit pointer to the next leaf node
    vector<Value> vals;  // associated leaf values

public:
    BPNode( bool isLeaf = false, BPNode* parent = nullptr, int d = 4)
        : d(d), isLeaf(isLeaf), parent(parent), next(nullptr)
    {
        keys.reserve(d-1);
        kids.reserve(d);

        if ( isLeaf ) {
            vals.reserve(d-1);
        }
    }

    bool isFull() { return keys.size() >= d-1; }

    BPNode * search(int k)
    {
        if ( isLeaf )
            return this;

        // Find the first key greater than k
        int i = 0;
        while (i < keys.size() && keys[i] <= k )
            i++;

        // Go to the appropriate child
        return kids[i]->search(k);
    }


    // A utility function to insert a new key in this leaf node
    // The assumption is, the node must be non-full when this
    // function is called
    int insertNonFullLeaf(int k, const Value& val)
    {
        // Initialize index as index of rightmost element
        int i = keys.size()-1;

        // Finds the location of new key to be inserted
        while (i >= 0 && keys[i] > k)
            i--;
        i += 1;

        keys.insert(keys.begin()+i,k);
        vals.insert(vals.begin()+i,val);

        return i;
    }

    void insertFullLeaf(int k, const Value& val)
    {
        insertNonFullLeaf(k, val);

        // Split the node
        BPNode * new_node  = new BPNode(true, parent, d);
        new_node->next = this;

        for ( int i = 0; i < d/2; i++ ) {
            new_node->keys.push_back(keys[0]);
            new_node->vals.push_back(vals[0]);
            keys.erase(keys.begin());
            vals.erase(vals.begin());
        }

        if ( parent == nullptr ) {
            parent = new BPNode(false, nullptr, d);
            new_node->parent = parent;
            parent->keys.push_back(keys[0]);
            parent->kids.push_back(new_node);
            parent->kids.push_back(this);

        } else if ( !parent->isFull() ) {
            parent->insertNonFullNode(keys[0], new_node);
        } else {
            parent->insertFullNode(keys[0], new_node);
        }
    }

    // A utility function to insert a new key in this inner node
    // The assumption is, the node must be non-full when this
    // function is called
    int insertNonFullNode(int k, BPNode * child)
    {
        // Initialize index as index of rightmost element
        int i = keys.size()-1;

        // Finds the location of new key to be inserted
        while (i >= 0 && keys[i] > k)
            i--;
        i += 1;

        keys.insert(keys.begin()+i, k);
        kids.insert(kids.begin()+i, child);

        return i;
    }

    void insertFullNode(int k, BPNode * child)
    {
        insertNonFullNode(k, child);
        // Split the node
        BPNode * new_node  = new BPNode(false, parent, d);
        new_node->next = this;

        for ( int i = 0; i < d/2; i++ ) {
            new_node->keys.push_back(keys[0]);
            new_node->kids.push_back(kids[0]);
            keys.erase(keys.begin());
            kids.erase(kids.begin());
        }

        // remove the copied up key from the child
        // and give it's kid to the new left node
        int key_up = keys[0];
        BPNode * kid_left = kids[0];
        keys.erase(keys.begin());
        kids.erase(kids.begin());
        new_node->kids.push_back(kid_left);

        if ( parent == nullptr ) {
            parent = new BPNode(false, nullptr, d);
            new_node->parent = parent;
            parent->keys.push_back(key_up);
            parent->kids.push_back(new_node);
            parent->kids.push_back(this);
        } else if ( !parent->isFull() ) {
            parent->insertNonFullNode(key_up, new_node);
        } else {
            parent->insertFullNode(key_up, new_node);
        }

    }

    string toString() {
        std::stringstream result;
        result << "{";
        for ( int i  = 0; i < keys.size(); ++i ) {
            if ( !isLeaf )
                result << kids[i]->toString() << " " <<  keys[i] << " ";
            else
                //result << keys[i] << ": " << vals[i] << ((i == keys.size() -1 ) ? "" : ", ");
                result << keys[i] << "*" << ((i == keys.size() -1 ) ? "" : ", ");
        }

        if ( !isLeaf )
            result << kids[keys.size()]->toString();
        result << "}";
        return result.str();
    }

};

class BPTree {
public:
    int d;
    BPNode * root;

public:
    BPTree(int branching_factor=4)
        : d(branching_factor) {
        root = new BPNode(true, nullptr, d);
    }

//private:

    BPNode * search(int k) {
        return root->search(k);
    }

    void insert(int k, const Value & val) {
        BPNode * leafNode = search(k);

        // If the leaf node is not full
        if ( !leafNode->isFull() ) {
            leafNode->insertNonFullLeaf(k, val);
        } else {
            leafNode->insertFullLeaf(k, val);
        }

        while(root->parent != nullptr)
            root = root->parent;
    }
};

#endif // SEARCHTREE_H
