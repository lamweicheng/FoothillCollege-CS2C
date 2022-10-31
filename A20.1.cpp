// Assignment #9 The Maximum Flow Problem
// client file --------------------------------------------------
// FHflowGraph client

#include <iostream>
#include <string>
using namespace std;
#include "FHflowGraph.h"
// --------------- main ---------------
int main()
{
    int finalFlow;

    // build graph
    FHflowGraph<string, int> myG;

    int numberEdges;
    string src, dest;
    int cap;

    cin >> numberEdges;
    for (int i = 0; i < numberEdges; ++i)
    {
        cin >> src >> dest >> cap;
        myG.addEdge(src, dest, cap);
    }

    // show the original flow graph
    myG.showResAdjTable();
    myG.showFlowAdjTable();

    myG.setStartVert("s");
    myG.setEndVert("t");
    finalFlow = myG.findMaxFlow();

    cout << "Final flow: " << finalFlow << endl;

    myG.showResAdjTable();
    myG.showFlowAdjTable();

    return 0;
}
