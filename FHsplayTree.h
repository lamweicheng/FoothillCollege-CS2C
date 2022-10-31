#ifndef FHSPLAYTREE_H

#define FHSPLAYTREE_H

#include "FHsearch_tree.h"

// -------------------- FHsplayTree Prototype ----------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>
{
public:
    FHsplayTree() : FHsearch_tree<Comparable>() { }
    ~FHsplayTree() {}

    // override base class
    bool insert(const Comparable& x);
    bool remove(const Comparable& x);
    bool contains(const Comparable& x);
    const Comparable& find(const Comparable& x);

    // new method
    const Comparable& showRoot();

protected:
    void splay(FHs_treeNode<Comparable>*& root, const Comparable& x);
    void rotateWithLeftChild(FHs_treeNode<Comparable>*& k2);
    void rotateWithRightChild(FHs_treeNode<Comparable>*& k2);

};


template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable& x) {

    if (contains(x))
        return false;

    FHs_treeNode<Comparable>* newNode = new FHs_treeNode<Comparable>(x);

    if (!this->mRoot) {}
    else if (x < this->mRoot->data)
    {
        newNode->lftChild = this->mRoot->lftChild;
        this->mRoot->lftChild = NULL;
        newNode->rtChild = this->mRoot;
    }
    else if (x > this->mRoot->data)
    {
        newNode->rtChild = this->mRoot->rtChild;
        this->mRoot->rtChild = NULL;
        newNode->lftChild = this->mRoot;
    }

    this->mRoot = newNode;
    this->mSize++;

    return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable& x) {
    if (!contain(x))
        return false;
    else
        splay(this->mRoot, x);

    if (x != this->mRoot)
        return false;

    FHs_treeNode<Comparable>* newRoot;

    if (this->mRoot->lftChild == NULL)
        newRoot = this->mRoot->rtChild;
    else
    {
        newRoot = this->mRoot->lftChild;
        splay(newRoot, x);
        newRoot->rtChild = this->mRoot->rtChild;
    }

    delete this->mRoot;
    this->mRoot = newRoot;

    return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable& x) {
    try
    {
        find(x);
    }
    catch (typename FHsearch_tree<Comparable>::NotFoundException&)
    {
        return false;
    }
    catch (typename FHsearch_tree<Comparable>::EmptyTreeException&)
    {
        return false;
    }

    return true;
}

template <class Comparable>
const Comparable& FHsplayTree<Comparable>::find(const Comparable& x) {
    if (!this->mRoot)
        throw typename FHsearch_tree<Comparable>::NotFoundException();

    splay(this->mRoot, x);

    if (x < this->mRoot->data || x > this->mRoot->data)
        throw typename FHsearch_tree<Comparable>::NotFoundException();

    return x;
}


template <class Comparable>
const Comparable& FHsplayTree<Comparable>::showRoot() {
    if (this->mRoot)
        return this->mRoot->data;
    static Comparable defaultObj = Comparable();
    return defaultObj;
}


template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable>*& root, const Comparable& x) {

    FHs_treeNode<Comparable>* rightTree = NULL, * leftTree = NULL, * rightTreeMin = NULL,
        * leftTreeMax = NULL;

    while (root != NULL)
    {
        if (x < root->data)
        {
            if (root->lftChild == NULL)
                break;
            if (x < root->lftChild->data)
            {
                rotateWithLeftChild(root);
                if (root->lftChild == NULL)
                    break;
            }

            if (rightTree == NULL)
            {
                rightTree = root;
                rightTreeMin = rightTree;
            }
            else
            {
                rightTreeMin->lftChild = root;
                rightTreeMin = rightTreeMin->lftChild;
            }
            root = root->lftChild;
            rightTreeMin->lftChild = NULL;
        }

        else if (x > root->data)
        {
            if (root->rtChild == NULL)
                break;
            if (x > root->rtChild->data)
            {
                rotateWithRightChild(root);
                if (root->rtChild == NULL)
                    break;
            }

            if (leftTree == NULL)
            {
                leftTree = root;
                leftTreeMax = leftTree;
            }
            else
            {
                leftTreeMax->rtChild = root;
                leftTreeMax = leftTreeMax->rtChild;
            }
            root = root->rtChild;
            leftTreeMax->rtChild = NULL;
        }
        else
            break;
    }

    if (leftTree)
    {
        if (root->lftChild)
            leftTreeMax->rtChild = root->lftChild;
        root->lftChild = leftTree;
    }

    if (rightTree)
    {
        if (root->rtChild)
            rightTreeMin->lftChild = root->rtChild;
        root->rtChild = rightTree;
    
    }
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(FHs_treeNode<Comparable>*& k2) {

    FHs_treeNode<Comparable> * k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(FHs_treeNode<Comparable>*& k2) {

    FHs_treeNode<Comparable>* k1 = k2->rtChild;
    k2->rtChild = k1->lftChild;
    k1->lftChild = k2;
    k2 = k1;
}


#endif