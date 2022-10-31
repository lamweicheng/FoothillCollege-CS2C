// Assignment #5 Top-Down Splay Trees Using Inheritance
// Instructor Solution

// Client / Splay Tree ----------------------------------------------

#include <iostream>
#include "FHsplayTree.h"
#include <vector>
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
    int k, k2, t;
    FHsplayTree<int> searchTree;
    PrintObject<int> intPrinter;
    vector<int> ints;

    searchTree.traverse(intPrinter);

    while (cin >> t)
        ints.push_back(t);

    cout << "Initial size: " << searchTree.size() << endl;
    for (k = 0; k < ints.size(); k++)
        searchTree.insert(ints[k]);
    cout << "New size: " << searchTree.size() << endl;

    cout << "\nTraversal: \n";
    searchTree.traverse(intPrinter);
    cout << endl << endl;

    for (k = -1; k < 13; k++)
    {
        // test contains()
        k2 = 10 - k;
        if (!searchTree.contains(k2))
            cout << " oops on contains " << k2 << endl;
        cout << "contains " << k2 << " --> root: " << searchTree.showRoot()
            << " height: " << searchTree.showHeight() << endl;

        // test find()
        try
        {
            searchTree.find(k);
        }
        catch (...)
        {
            cout << " oops on find " << k << endl;
        }
        cout << "find " << k << " --> root: " << searchTree.showRoot()
            << " height: " << searchTree.showHeight() << endl;
    }

    return 0;
}

