#include "BPlusTree.h"
#include <sstream>

BPlusNode::BPlusNode(bool isLeaf, BPlusNode *parent, int d)
    : d(d), isLeaf(isLeaf), parent(parent), next(nullptr)
{
    keys.reserve(d-1);

    if ( isLeaf ) {
        vals.reserve(d-1);
    } else {
        kids.reserve(d);
    }
}

int BPlusNode::keyRank(const Key &k) {
    int i = 0;

    while (i < keys.size() && keys[i] < k )
        i++;

    return i;
}

BPlusNode * BPlusNode::search(int k)
{
    if ( isLeaf )
        return this;

    // Find the location of the key
    int i = 0;

    while (i < keys.size() && keys[i] <= k )
        i++;

    // Go to the appropriate child
    return kids[i]->search(k);
}

void BPlusNode::insert(const Key & key, const Value & val) {
    // Find the proper leaf node
    BPlusNode * leaf_node = search(key);

    // Insert the key
    leaf_node->insertLeaf(key, val);
}

BPlusNode * BPlusNode::splitNode(BPlusNode *left_part)
{
    BPlusNode * right_part = new BPlusNode(left_part->isLeaf, left_part->parent, left_part->d);

    if (left_part->next) {
        right_part->next = this->next;
    }

    left_part->next = right_part;

    for ( int i = 0; i < d/2; i++ ) {

        right_part->keys.insert(right_part->keys.begin(), left_part->keys.back());
        left_part->keys.pop_back();

        if ( left_part->isLeaf ) {
            right_part->vals.insert(right_part->vals.begin(), left_part->vals.back());
            left_part->vals.pop_back();
        } else {
            right_part->kids.insert(right_part->kids.begin(), left_part->kids.back());
            left_part->kids.pop_back();
            right_part->kids.front()->parent = right_part;
        }
    }

    return right_part;
}


void BPlusNode::insertLeaf(const Key &key, const Value & val) {

    // Finds the location of new key to be inserted
    int i = keyRank(key);

    keys.insert(keys.begin()+i, key);
    vals.insert(vals.begin()+i, val);

    if ( keys.size() < d )
        return;

    // Split the node
    // this node represents the left part of the split
    BPlusNode * right_node  = splitNode(this);


    if ( parent == nullptr ) {
        this->parent = new BPlusNode(false, nullptr, d);
        right_node->parent = this->parent;
        parent->kids.push_back(this);
        parent->keys.push_back(right_node->keys[0]);
        parent->kids.push_back(right_node);
    } else {
        parent->insertNonLeaf(right_node->keys[0], right_node);
    }

}

void BPlusNode::insertNonLeaf(const Key &key, BPlusNode *node)
{
    // Finds the location of new key to be inserted
    int i = keyRank(key);

    keys.insert(keys.begin()+i, key);
    kids.insert(kids.begin()+i+1, node);

    if ( keys.size() < d )
        return;

    // Split the node
    // this node represents the left part of the split
    BPlusNode * right_node  = splitNode(this);

    // Pop the first key of the right node
    Key key_up = right_node->keys[0];
    right_node->keys.erase(right_node->keys.begin());


    if ( parent == nullptr ) {
        this->parent = new BPlusNode(false, nullptr, d);
        right_node->parent = this->parent;
        parent->kids.push_back(this);
        parent->keys.push_back(key_up);
        parent->kids.push_back(right_node);
    } else {
        parent->insertNonLeaf(key_up, right_node);
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
            std::cout << "Wrong parent" << std::endl;
    }

    if ( !isLeaf ) {
        result << kids[keys.size()]->toString();

        if ( !isLeaf && kids[keys.size()]->parent != this )
            std::cout << "Wrong parent" << std::endl;
    }
    result << "}";
    return result.str();
}


BPlusTree::BPlusTree(unsigned int branching_factor)
    : d(branching_factor)
{
    root = new BPlusNode(true, nullptr, d);
}

void BPlusTree::insert(const Key &key, const Value &val)
{
    root->insert(key, val);

    while(root->parent)
        root = root->parent;
}

