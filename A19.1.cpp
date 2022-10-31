// CS 2C Assignment 8 - Analyzing quickSort's Recursion Limits

#include <iostream>
using namespace std;
#include "FHsort.h"
#include "FHvector.h"
#include <time.h>

template <typename Comparable>
void quickSortX(FHvector<Comparable>& a, int recLim)
{
    if (recLim < 2)
        recLim = 2;

    quickSortX(a, 0, a.size() - 1, recLim);

}

template <typename Comparable>
void quickSortX(FHvector<Comparable>& a, int left, int right, int recLim)
{

    Comparable pivot;
    int i, j;

    if (left + recLim <= right)
    {
        pivot = median3(a, left, right);
        for (i = left, j = right - 1;;)
        {
            while (a[++i] < pivot)
                ;
            while (pivot < a[--j])
                ;
            if (i < j)
                mySwapFH(a[i], a[j]);
            else
                break;
        }

        mySwapFH(a[i], a[right - 1]);

        quickSortX(a, left, i - 1, recLim);
        quickSortX(a, i + 1, right, recLim);
    }
    else
        insertionSort(a, left, right);

}


// --------------- main ---------------
// change the following directive to an int so we can modify it from input
//#define ARRAY_SIZE 2500

int main()
{
    int k, recLim;
    int ARRAY_SIZE, MAX_RECLIM;
    FHvector<int> fhVectorOfInts;
    float randFrac;
    clock_t startTime, stopTime;
    ;
    cin >> ARRAY_SIZE >> MAX_RECLIM;

    if (ARRAY_SIZE > 25000)
        ARRAY_SIZE = 25000;
    cout << "The array size is: " << ARRAY_SIZE << endl;
    cout << "The max recursion limit is: " << MAX_RECLIM << endl;
    int arrayOfInts[25000];

    srand(0);


    // build master array of random numbers
    for (k = 0; k < ARRAY_SIZE; k++)
    {
        randFrac = rand() / (double)RAND_MAX;
        arrayOfInts[k] = randFrac * ARRAY_SIZE;
    }
    cout << "|---------------------------------------|" << endl;
    cout << "|           Array Size of "<<ARRAY_SIZE<<"         |" << endl;
    cout << "|-----------------------|---------------|" << endl;
    for (recLim = 2; recLim <= MAX_RECLIM; recLim += 2)
    {
        fhVectorOfInts.clear();
        for (int k = 0; k < ARRAY_SIZE; k++) {
            fhVectorOfInts.push_back(arrayOfInts[k]);
        }
        startTime = clock();
        quickSortX(fhVectorOfInts, recLim);
        stopTime = clock();
        double time = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
        cout << "|Time for recLim " << recLim << " : \t|" << 
          time << "\t seconds|" << endl;
      
        
     
    }
    cout << "|---------------------------------------|" << endl;
    return 0;
}
