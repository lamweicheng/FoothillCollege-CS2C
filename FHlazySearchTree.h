#ifndef FHSEARCHTREE
#define FHSEARCHTREE

// ---------------------- FHlazySearchTreeNode Prototype --------------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
    FHlazySearchTreeNode(const Comparable& d = Comparable(),
        bool deleteNode = false,
        FHlazySearchTreeNode* lt = NULL,
        FHlazySearchTreeNode* rt = NULL)
        : lftChild(lt), rtChild(rt), data(d), deleted(deleteNode)
    { }

    FHlazySearchTreeNode* lftChild, * rtChild;
    Comparable data;
    bool deleted;

    // for use only with AVL Trees
    virtual int getHeight() const { return 0; }
    virtual bool setHeight(int height) { return true; }
};

// ---------------------- FHlazySearchTree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
    int mSize;
    int mSizeHard;
    FHlazySearchTreeNode<Comparable>* mRoot;

public:
    FHlazySearchTree() { mSize = 0; mSizeHard = 0; mRoot = NULL; }
    FHlazySearchTree(const FHlazySearchTree& rhs)
    {
        mRoot = NULL; mSize = 0; mSizeHard = 0; *this = rhs;
    }
    ~FHlazySearchTree() { clear(); }

    // added code
    const Comparable& findMinHard() const;
    const Comparable& findMaxHard() const;

    const Comparable& findMin() const;
    const Comparable& findMax() const;
    const Comparable& find(const Comparable& x) const;

    bool empty() const { return (mSize == 0); }
    int size() const { return mSize; }
    void clear() { makeEmpty(mRoot); }
    const FHlazySearchTree& operator=(const FHlazySearchTree& rhs);
    int sizeHard() const { return mSizeHard; }

    // The private method is the recursive counterpart of the public one).
    // This allows the client to truly remove all deleted (stale) nodes.
    void collectGarbage();

    bool insert(const Comparable& x);
    bool remove(const Comparable& x);
    bool contains(const Comparable& x) const { return find(mRoot, x) != NULL; }

    template <class Processor>
    void traverse(Processor func) const { traverse(mRoot, func); }
    int showHeight() const { return findHeight(mRoot); }

protected:
    FHlazySearchTreeNode<Comparable>* clone(FHlazySearchTreeNode<Comparable>* root) const;
    FHlazySearchTreeNode<Comparable>* findMin(FHlazySearchTreeNode<Comparable>* root) const;
    FHlazySearchTreeNode<Comparable>* findMax(FHlazySearchTreeNode<Comparable>* root) const;

    // new functions
    FHlazySearchTreeNode<Comparable>* findMinHard(FHlazySearchTreeNode<Comparable>* root) const;
    FHlazySearchTreeNode<Comparable>* findMaxHard(FHlazySearchTreeNode<Comparable>* root) const;

    FHlazySearchTreeNode<Comparable>* find(FHlazySearchTreeNode<Comparable>* root,
        const Comparable& x) const;
    bool insert(FHlazySearchTreeNode<Comparable>*& root,
        const Comparable& x);
    bool remove(FHlazySearchTreeNode<Comparable>*& root, const Comparable& x);

    // new functions
    bool removeHard(FHlazySearchTreeNode<Comparable>*& root, const Comparable& x);
    void collectGarbage(FHlazySearchTreeNode<Comparable>*& root);
    void makeEmpty(FHlazySearchTreeNode<Comparable>*& subtreeToDelete);
    template <class Processor>
    void traverse(FHlazySearchTreeNode<Comparable>* treeNode,
        Processor func, int level = -1) const;
    int findHeight(FHlazySearchTreeNode<Comparable>* treeNode, int height = -1) const;

public:
    // for exception throwing
    class EmptyTreeException {};
    class NotFoundException {};
};

// FHlazySearchTree public method definitions -----------------------------
template <class Comparable>
const Comparable& FHlazySearchTree<Comparable>::findMinHard() const
{
    if (mRoot == NULL)
        throw EmptyTreeException();
    return findMinHard(mRoot)->data;
}

template <class Comparable>
const Comparable& FHlazySearchTree<Comparable>::findMin() const
{
    if (mRoot == NULL || mSize == 0)
        throw NotFoundException();
    return findMin(mRoot)->data;
}

template <class Comparable>
const Comparable& FHlazySearchTree<Comparable>::findMaxHard() const
{
    if (mRoot == NULL)
        throw EmptyTreeException();
    return findMaxHard(mRoot)->data;
}

template <class Comparable>
const Comparable& FHlazySearchTree<Comparable>::findMax() const
{
    if (mRoot == NULL || mSize == 0)
        throw NotFoundException();
    return findMax(mRoot)->data;
}

template <class Comparable>
const Comparable& FHlazySearchTree<Comparable>::find(
    const Comparable& x) const
{
    FHlazySearchTreeNode<Comparable>* result;

    result = find(mRoot, x);
    if (result == NULL)
        throw NotFoundException();
    return result->data;
}

template <class Comparable>
const FHlazySearchTree<Comparable>& FHlazySearchTree<Comparable>::operator=
(const FHlazySearchTree& rhs)
{
    if (&rhs != this)
    {
        clear();
        mRoot = clone(rhs.mRoot);
        mSize = rhs.size();
        mSizeHard = rhs.sizeHard();
    }
    return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable& x)
{
    if (insert(mRoot, x))
    {
        mSize++;
        return true;
    }
    return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable& x)
{
    if (remove(mRoot, x))
    {
        mSize--;
        return true;
    }
    return false;
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse(FHlazySearchTreeNode<Comparable>* treeNode,
    Processor func, int level) const
{
    if (treeNode == NULL)
        return;
    // we're not doing anything with level but its there in case we want it
    traverse(treeNode->lftChild, func, level + 1);
    if (!(treeNode->deleted))
        func(treeNode->data);

    traverse(treeNode->rtChild, func, level + 1);
}

// FHlazySearchTree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::clone(
    FHlazySearchTreeNode<Comparable>* root) const
{
    FHlazySearchTreeNode<Comparable>* newNode;
    if (root == NULL)
        return NULL;

    newNode = new FHlazySearchTreeNode<Comparable>(
        root->data, root->deleted,
        clone(root->lftChild), clone(root->rtChild));
    return newNode;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::findMinHard(
    FHlazySearchTreeNode<Comparable>* root) const
{
    if (root == NULL)
        return NULL;
    if (root->lftChild == NULL)
        return root;
    return findMinHard(root->lftChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::findMin(
    FHlazySearchTreeNode<Comparable>* root) const
{
    if (root == NULL)
        return NULL;

    FHlazySearchTreeNode<Comparable>* Min = findMin(root->lftChild);

    if (Min != NULL)
        return Min;

    if (root->deleted == false)
        return root;

    Min = findMax(root->rtChild);

    return Min;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::findMaxHard(
    FHlazySearchTreeNode<Comparable>* root) const
{
    if (root == NULL)
        return NULL;
    if (root->lftChild == NULL)
        return root;
    return findMaxHard(root->rtChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::findMax(
    FHlazySearchTreeNode<Comparable>* root) const
{
    if (root == NULL)
        return NULL;

    FHlazySearchTreeNode<Comparable>* Max = findMax(root->rtChild);

    if (Max != NULL)
        return Max;

    if (root->deleted == false)
        return root;

    Max = findMax(root->lftChild);

    return Max;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(
    FHlazySearchTreeNode<Comparable>* root, const Comparable& x) const
{
    if (root == NULL)
        return NULL;

    if (x < root->data)
        return find(root->lftChild, x);
    if (root->data < x)
        return find(root->rtChild, x);

    // added code for bool deleted
    if (root->deleted == true)
        return NULL;
    return root;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(
    FHlazySearchTreeNode<Comparable>*& root, const Comparable& x)
{
    if (root == NULL)
    {
        root = new FHlazySearchTreeNode<Comparable>(x, false, NULL, NULL);
        mSizeHard++;
        return true;
    }
    else if (x < root->data)
        return insert(root->lftChild, x);
    else if (root->data < x)
        return insert(root->rtChild, x);

    else if (root->deleted)
    {
        root->deleted = false;
        return true;
    }
    return false; // duplicate
}

// Revise remove() (recursive version) to implement lazy deletion.
template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(
    FHlazySearchTreeNode<Comparable>*& root, const Comparable& x)
{
    if (root == NULL)
        return false;

    if (x < root->data)
        return remove(root->lftChild, x);
    if (root->data < x)
        return remove(root->rtChild, x);

    // found the node
    if (root->deleted)
        return false;
    else
    {
        root->deleted = true;
        return true;
    }
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(
    FHlazySearchTreeNode<Comparable>*& subtreeToDelete)
{
    if (subtreeToDelete == NULL)
        return;

    // remove children
    makeEmpty(subtreeToDelete->lftChild);
    makeEmpty(subtreeToDelete->rtChild);

    // clear client's pointer
    delete subtreeToDelete;
    subtreeToDelete = NULL;
    --mSize;
    --mSizeHard;
}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight(FHlazySearchTreeNode<Comparable>* treeNode,
    int height) const
{
    int leftHeight, rightHeight;

    if (treeNode == NULL)
        return height;
    height++;
    leftHeight = findHeight(treeNode->lftChild, height);
    rightHeight = findHeight(treeNode->rtChild, height);
    return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage()
{
    collectGarbage(mRoot);
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage(FHlazySearchTreeNode<Comparable>*& root)
{
    if (root == NULL)
        return;

    while (root != NULL && root->deleted == true)
        removeHard(root, root->data);

    if (root != NULL && root->lftChild != NULL)
        collectGarbage(root->lftChild);

    if (root != NULL && root->rtChild != NULL)
        collectGarbage(root->rtChild);

    return;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::removeHard(FHlazySearchTreeNode<Comparable>*& root, const Comparable& x)
{
    if (root == NULL)
        return false;

    if (x < root->data)
        return removeHard(root->lftChild, x);

    if (root->data < x)
        return removeHard(root->rtChild, x);

    // found the node
    if (root->lftChild != NULL && root->rtChild != NULL)
    {
        FHlazySearchTreeNode<Comparable>* minNode = findMinHard(root->rtChild);
        root->data = minNode->data;
        root->deleted = minNode->deleted;
        removeHard(root->rtChild, minNode->data);
    }
    else
    {
        FHlazySearchTreeNode<Comparable>* nodeToRemove = root;
        root = (root->lftChild != NULL) ? root->lftChild : root->rtChild;
        mSizeHard--;
        delete nodeToRemove;
    }
    return true;
}

#endif