// CS 02C Assignment #7 - Analyzing Shellsort's Gaps
// Client code

#include <iostream>
#include "shellSortX.h"
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int arraySize;
    vector<int> gapBasic = getBasicSequence();
    vector<int> gapSedgewick = getSedgewickSequence();
    vector<int> gapCustom = getCustomSequence();

    cin >> arraySize;

    vector<int> data(arraySize), copyOfData(arraySize);

    float randFraction;
    for (int i = 0; i < arraySize; i++)
    {
        randFraction = (float)rand() / RAND_MAX;
        data[i] = (int)(randFraction * 999);
    }

    float startTime, stopTime;

    for (int i = 0; i < arraySize; i++)
        copyOfData[i] = data[i];
    startTime = clock();
    shellSort1(copyOfData.data(), copyOfData.size());
    stopTime = clock();
    cout << "ShellSort1 time: " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << endl;


    for (int i = 0; i < arraySize; i++)
        copyOfData[i] = data[i];
    startTime = clock();
    shellSortX(copyOfData.data(), copyOfData.size(), gapBasic);
    stopTime = clock();
    cout << "ShellSort with Basic time: " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << endl;

    for (int i = 0; i < arraySize; i++)
        copyOfData[i] = data[i];
    startTime = clock();
    shellSortX(copyOfData.data(), copyOfData.size(), gapSedgewick);
    stopTime = clock();
    cout << "ShellSort with Sedgewick time: " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << endl;


    for (int i = 0; i < arraySize; i++)
        copyOfData[i] = data[i];
    startTime = clock();
    shellSortX(copyOfData.data(), copyOfData.size(), gapCustom);
    stopTime = clock();
    cout << "ShellSort with Custom time: " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << endl;

    shellSort1(copyOfData.data(), copyOfData.size());
    shellSortX(copyOfData.data(), copyOfData.size(), gapSedgewick);
   

    return 0;
}
