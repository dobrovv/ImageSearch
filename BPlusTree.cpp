#include "BPlusTree.h"

BPlusNode::BPlusNode(bool isLeaf, BPlusNode *parent, int d)
    : d(d), isLeaf(isLeaf), parent(parent), next(nullptr), prev(nullptr)
{
    keys.reserve(d-1);

    if ( isLeaf ) {
        vals.reserve(d-1);
    } else {
        kids.reserve(d);
    }
}

BPlusNode * BPlusNode::search(int k)
{
    if ( isLeaf )
        return this;

    // Find the location of the key
    int i = keyRank(k);

    // Go to the appropriate child
    return kids[i]->search(k);
}

void BPlusNode::insertNonFullLeaf(int k, const Value &val)
{
    // Finds the location of new key to be inserted
    int i = keyRank(k);

    keys.insert(keys.begin()+i,k);
    vals.insert(vals.begin()+i,val);

}

void BPlusNode::insertFullLeaf(int k, const Value &val)
{
    // Inserts the new (key,value) pair
    insertNonFullLeaf(k, val);

    // Split the node
    // this node represents right part of the split
    BPlusNode * left_node  = new BPlusNode(true, parent, d);
    if (this->prev) {
        BPlusNode * old_prev = this->prev;
        old_prev->next = left_node;
        left_node->prev = old_prev;
    }
    left_node->next = this;
    this->prev = left_node;

    for ( int i = 0; i < d/2; i++ ) {
        left_node->keys.push_back(keys[0]);
        left_node->vals.push_back(vals[0]);
        keys.erase(keys.begin());
        vals.erase(vals.begin());
    }

    if ( parent == nullptr ) {
        this->parent = new BPlusNode(false, nullptr, d);
        left_node->parent = this->parent;

        parent->keys.push_back(keys[0]);
        parent->kids.push_back(left_node);
        parent->kids.push_back(this);

    } else if ( !parent->isFull() ) {
        parent->insertNonFullNode(keys[0], left_node);
    } else {
        parent->insertFullNode(keys[0], left_node);
    }
}

int BPlusNode::insertNonFullNode(int k, BPlusNode *child)
{
    // Finds the location of new key to be inserted
    int i = keyRank(k);

    keys.insert(keys.begin()+i, k);
    kids.insert(kids.begin()+i, child);

    return i;
}

void BPlusNode::insertFullNode(int k, BPlusNode *child)
{
    insertNonFullNode(k, child);

    // Split the node
    // this node represents right part of the split
    BPlusNode * left_node  = new BPlusNode(false, parent, d);

    for ( int i = 0; i < d/2; i++ ) {
        left_node->keys.push_back(keys[0]);
        left_node->kids.push_back(kids[0]);
        kids[0]->parent = left_node;
        keys.erase(keys.begin());
        kids.erase(kids.begin());
    }

    // Remove a key that gets up to the parent
    // and give its left child node to the left part of the splited node
    int key_up = keys[0];
    BPlusNode * kid_left = kids[0];

    left_node->kids.push_back(kid_left);
    kid_left->parent = left_node;

    keys.erase(keys.begin());
    kids.erase(kids.begin());


    if ( parent == nullptr ) {
        parent = new BPlusNode(false, nullptr, d);
        left_node->parent = parent;
        parent->keys.push_back(key_up);
        parent->kids.push_back(left_node);
        parent->kids.push_back(this);

    } else if ( !parent->isFull() ) {
        parent->insertNonFullNode(key_up, left_node);

    } else {
        parent->insertFullNode(key_up, left_node);
    }
}

std::string BPlusNode::toString() {
    std::stringstream result;
    result << "{";
    for ( int i  = 0; i < keys.size(); ++i ) {
        if ( !isLeaf ) {
            result << kids[i]->toString() << " " <<  keys[i] << " ";
        } else {
            //result << keys[i] << ": " << vals[i] << ((i == keys.size() -1 ) ? "" : ", ");
            result << keys[i] << "*" << ((i == keys.size() -1 ) ? "" : ", ");
        }

        if ( !isLeaf && kids[i]->parent != this )
            cout << "Wrong parent" << endl;
    }

    if ( !isLeaf ) {
        result << kids[keys.size()]->toString();

        if ( !isLeaf && kids[keys.size()]->parent != this )
            cout << "Wrong parent" << endl;
    }
    result << "}";
    return result.str();
}



BPlusTree::BPlusTree(int branching_factor)
    : d(branching_factor) {
    root = new BPlusNode(true, nullptr, d);
}

void BPlusTree::insert(int k, const Value &val) {
    BPlusNode * leafNode = search(k);

    // If the leaf node is not full
    if ( !leafNode->isFull() ) {
        leafNode->insertNonFullLeaf(k, val);
    } else {
        leafNode->insertFullLeaf(k, val);
    }

    while(root->parent != nullptr)
        root = root->parent;
}
