// Assignment #2 - Sparse Matrices (Part A)
//
// ------------------------- CLIENT FILE ----------------------

#include <iostream>
using namespace std;
#include "FHsparseMat.h"

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

// --------------- main ---------------
int main()
{
    int row = 0, col = 0;
    SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

    cin >> row >> col;

    // test mutators
    mat.set(row, col, 77);
    mat.set(2, 5, 10);
    mat.set(2, 5, 35);   // should overwrite the 10
    mat.set(3, 9, 21);
    mat.set(MAT_SIZE, 1, 5);  // should fail silently
    mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
    mat.set(4, 4, -9);
    mat.set(4, 4, 0);   // should remove the -9 node entirely
    mat.set(MAT_SIZE - 1, MAT_SIZE - 1, 99);

    // test accessors and exceptions
    try
    {
        cout << mat.get(row, col) << endl; // may throw an exception
        cout << mat.get(7, 8) << endl;
        cout << mat.get(2, 5) << endl;
        cout << mat.get(9, 9) << endl;
        cout << mat.get(-4, 7) << endl;  // should throw an exception
    }
    catch (...)
    {
        cout << "oops" << endl;
    }

    // show top left 15x15
    mat.showSubSquare(0, 15);

    // show bottom right 15x15
    mat.showSubSquare(MAT_SIZE - 15, 15);


   
    // Test the first part above, make sure it works as you expected
    // then uncomment the following line to enable the second part 
#define SECOND_PART
#ifdef SECOND_PART
   // additional test for option A
    cout << "testing constructor error:" << endl;
    SpMat matBad(MAT_SIZE, -MAT_SIZE, 0);
    cout << "   constructed row size: " << matBad.getRowSize()
        << "   constructed col  size: " << matBad.getColSize() << endl;

    // test optoin A mutators
    cout << "\ntesting basic set()" << endl;
    for (int k = 0; k < 10; k++)
    {
        mat.set(k, k, k * 1.);
        mat.set(4, k, k * 10.);
    }
    mat.set(row, col, 77);
    mat.set(MAT_SIZE - 1, MAT_SIZE - 2, 123);

    // show top left 12x12
    cout << "\nSee results of set()s. Upper Left 12x12 subsquare:" << endl;
    mat.showSubSquare(0, 12);

    cout << "testing get() bounds error:" << endl;
    try
    {
        cout << mat.get(7, 8) << endl;
        cout << mat.get(2, 5) << endl;
        cout << mat.get(9, 9) << endl;
        cout << mat.get(-4, 7) << endl;  // should throw an exception
    }
    catch (SpMat::MatBoundsException)
    {
        cout << "oops - bounds in get()" << endl;
    }

    // show bottom right  12x12
    cout << "\nLast 12x12 subsquare:" << endl;
    mat.showSubSquare(MAT_SIZE - 12, 12);
#endif
}



