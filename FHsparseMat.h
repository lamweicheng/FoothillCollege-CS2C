// ------------------------- TARGET CLASS FILE  ----------------------

// Assignment #2 
// Include file FHsparseMat.h

#ifndef FHSPARSE_MAT_H
#define FHSPARSE_MAT_H

#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

#include "FHvector.h"
#include "FHlist.h"

// forward declaration for benefit of MatNodePtB prototype
template <class Object>
class SparseMat;

template <class Object>
class MatNode
{
protected:
    int col;

public:
    Object data;
    // we need a default constructor for lists
    MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
    int getCol() const { return col; }
};

template <class Object>
class SparseMat   // prototype ------------------------------------------------
{
protected:
    typedef FHlist< MatNode<Object> > MatRow;
    typedef FHvector<MatRow> MasterCol;

    MasterCol rows;
    Object defaultVal;
    int rowSize, colSize;

public:
    static const int MIN_SIZE = 1;
    static const int DFLT_SIZE = 100;
    SparseMat<Object>(int numRows, int numCols, const Object& defaultVal);
    const Object& get(int r, int c) const;
    bool set(int r, int c, const Object& x);
    void clear();
    int getRowSize() { return rowSize; }
    int getColSize() { return colSize; }
    // show submatrix, square upper left (start, start)
    void showSubSquare(int start, int size);

private:
    bool valid(int r, int c) const;

public:
    class MatBoundsException { };
};

// SparseMat method definitions  -------------------------------
// constructor
template <class Object>
SparseMat<Object>::SparseMat(int numRows, int numCols,
    const Object& defaultValue)
{
    defaultVal = defaultValue;
    rowSize = numRows < MIN_SIZE ? DFLT_SIZE : numRows;
    colSize = numCols < MIN_SIZE ? DFLT_SIZE : numCols;
    for (int i = 0; i < rowSize; i++)
        rows.push_back(MatRow());
}

// basic set()
template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object& x)
{
    if ((r < 0 || r >= rowSize) || (c < 0 || c >= colSize))
        return false;

    if (x == defaultVal)
    {
        for (typename MatRow::iterator iter = rows[r].begin(); iter != rows[r].end(); iter++)
        {
            if ((*iter).getCol() == c)
                rows[r].erase(iter);
            else
                return true;
        }
    }
    else
        for (typename MatRow::iterator iter = rows[r].begin(); iter != rows[r].end(); iter++)
        {
            if ((*iter).getCol() == c)
                (*iter).data = x;
            else
            {
                MatNode<Object> temp = MatNode<Object>(c, x);
                rows[r].push_back(temp);
            }
        }
    MatNode<Object> temp = MatNode<Object>(c, x);
    rows[r].push_back(temp);
    return true;
}

template <class Object>
const Object& SparseMat<Object>::get(int r, int c) const
{
    if (valid(r, c))
    {
        for (typename MatRow::const_iterator iter = rows[r].begin(); iter != rows[r].end(); iter++)
        {
            if ((*iter).getCol() == c)
            {
                return (*iter).data;
            }

        }
        return defaultVal;
    }
    else
    {
        throw MatBoundsException();

    }

  
}

template <class Object>
void SparseMat<Object>::clear()
{
    for (int i = 0; i < rowSize; i++)
    {
        rows[i].clear();
    }
}

template <class Object>
bool SparseMat<Object>::valid(int r, int c) const
{
  
    return r >= 0 && r < rowSize && c >= 0 && c < colSize;
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
    int temp = start + size;
    for (int i = start; i < temp; i++)
    {
        for (int j = start; j < temp; j++)
            cout << setw(5) << setfill('0') << setprecision(2) << fixed << get(i, j) << " ";
        cout << endl;

    }
 
    cout << endl;
}
#endif
