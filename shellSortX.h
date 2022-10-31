#pragma once
// CS 02C Assignment #7 - Analyzing Shellsort's Gaps
// shellSortX

#ifndef SHELLSORTX_H
#define SHELLSORTX_H
#include "Foothill_Sort.h"
#include <vector>
#include <cmath>
using namespace std;

// generate basic gap sequence
vector<int> getBasicSequence()
{
    vector<int> gap(20);
    //gap = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
  //    2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288 };
    gap[0] = 1;
    for (int i = 1; i < 20; ++i) {
        gap[i] = gap[i - 1] * 2;
    }
    return gap;
}

// generate Sedgewick gap sequence
vector<int> getSedgewickSequence()
{
    int k, gapNumber;

    vector<int> gap(20);
    for (k = 0; k < 28; k++)
    {
        if (k % 2 == 0)
        {
            gapNumber = 9 * (pow(2, k) - pow(2, k / 2)) + 1;
        }
        else
            gapNumber = 8 * pow(2, k) - 6 * pow(2, (k + 1) / 2) + 1;

        gap.push_back(gapNumber);
    }

    return gap;
}

// my gap sequence
vector<int> getCustomSequence()
{
    vector<int> gap{ 1, 12, 34, 55, 78, 89, 100, 105, 123, 141, 156, 162,183,194,200, 210,234,258, 289, 300};
    return gap;

}

// shell sort with a custom gap
template <typename Comparable>
void shellSortX(Comparable array[], int arraySize, vector<int>& gaps)
{
    int k, pos,gap, gapPos;
    Comparable tmp;
    for (gapPos = 0; gaps[gapPos] < arraySize / 2 && gapPos < gaps.size(); gapPos++)
    {
    }

    for (gapPos; gapPos >= 0; gapPos--)
    {
        gap = gaps[gapPos];
        for (pos = gap; pos < arraySize; pos++)
        {
            tmp = array[pos];
            for (k = pos; k >= gap && tmp < array[k - gap]; k -= gap)  
                array[k] = array[k - gap];
            array[k] = tmp;
        }
    }

}

#endif