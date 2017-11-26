#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <cstdint>
#include <vector>
using UInt = std::uint32_t;
using std::vector;

typedef int Key;
typedef int Value;

class SearchTree
{

public:
    struct Node {
        Key key;
        Value val;
        Node * left, * right;
        int N;
        Node(Key key, Value val, int N)
            : key(key), val(val), left(nullptr), right(nullptr), N(N)
        {}
    };

    Node * root;

public:

    SearchTree()
        : root(nullptr)
    {}

    size_t size() {
        return size(root);
    }

    size_t size(Node * node) {
        return node == nullptr ? 0 : node->N;
    }

    Value get(Key key) {
        return get(root, key);
    }

    void put(Key key, Value val) {
        root = put(root, key, val);
    }

    vector<Node *> rangeSearch(Key lo, Key hi) {
        vector<Node *> result;
        rangeSearch(root, result, lo, hi);
        return result;
    }

private:

    Value get(Node * node, Key key)
    {
        if ( node == nullptr )
            return Value{};

        if ( key < node->key )
            return get(node->left, key);
        else if ( node->key < key )
            return get(node->right, key);
        else
            return node->val;
    }

    Node * put(Node * x, Key key, Value val)
    {
        if ( x == nullptr )
            return new Node(key, val, 1);

        if ( key < x->key )
            x->left = put(x->left, key, val);
        else if ( x->key < key )
            x->right = put(x->right, key, val);
        else
            x->val = val;

        x->N = size(x->left) + size(x->right) + 1;

        return x;
    }

    void rangeSearch(Node * x, vector<Node*>& result, Key lo, Key hi) {

        if ( x == nullptr )
            return;

        if ( lo < x->key )
            rangeSearch(x->left, result, lo, hi);

        if ( lo <= x->key && x->key <= hi )
            result.push_back(x);

        if ( x->key < hi )
            rangeSearch(x->right, result, lo, hi);
    }
};

#endif // SEARCHTREE_H
