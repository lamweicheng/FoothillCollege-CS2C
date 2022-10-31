// Assignment #4 Lazy Deletion in Binary Search Trees (Part A)
// Instructor Solution
// Simple Search Tree Client - Lazy Deletion, int data

// --------------- main ---------------
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include "FHlazySearchTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
    void operator()(Object obj)
    {
        cout << obj << " ";
    }
};

int main()
{
    int k, t;
    FHlazySearchTree<int> searchTree;
    PrintObject<int> intPrinter;
    vector<int> ints;

    while (cin >> t)
        ints.push_back(t);

    searchTree.traverse(intPrinter);

    cout << "initial size: " << searchTree.size() << endl;
    for (vector<int>::iterator it = ints.begin(); it != ints.end(); ++it)
        searchTree.insert(*it);

    cout << "After populating -- traversal and sizes: \n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting garbage on new tree - should be no garbage." << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    // test assignment operator
    FHlazySearchTree<int> searchTree2 = searchTree;

    cout << "\nAttempting 1 removal: \n";
    if (searchTree.remove(ints[1]))
        cout << "removed " << ints[1] << endl;
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting garbage - should clean 1 item. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Collecting garbage again - no change expected. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    // test soft insertion and deletion:

    cout << "Adding 'hard' " << ints[1] + 2 << " - should see new sizes. " << endl;
    searchTree.insert(ints[1] + 2);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAfter soft removal. " << endl;
    searchTree.remove(ints[1] + 2);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Repeating soft removal. Should see no change. " << endl;
    searchTree.remove(ints[1] + 2);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "Soft insertion. Hard size should not change. " << endl;
    searchTree.insert(ints[1] + 2);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    cout << "\nAttempting 100 removals: \n";
    for (k = 100; k > 0; k--)
    {
        if (searchTree.remove(k))
            cout << "removed " << k << endl;
    }
    searchTree.collectGarbage();

    cout << "\nsearchTree now:\n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
        << "  Hard size: " << searchTree.sizeHard() << endl;

    searchTree2.insert(500);
    searchTree2.insert(200);
    searchTree2.insert(300);
    searchTree2.insert(700);
    searchTree2.insert(100);
    searchTree2.insert(600);
    cout << "\nsearchTree2:\n";
    searchTree2.traverse(intPrinter);
    cout << "\ntree 2 size: " << searchTree2.size()
        << "  Hard size: " << searchTree2.sizeHard() << endl;

    return 0;
}
