// Assignment #3 Timing Matrix Multiplication (Part A)
// CLIENT

#include <iostream>
#include <iomanip>
using namespace std;
#include <time.h>

// --------------- main ---------------
#define MIN_MAT_SIZE 1
#define MIN_PERCENT 1
#define MAX_PERCENT 10.0

// for matrix of fixed sizes
#define MAT_SIZE 5
typedef float* DynMat[MAT_SIZE];
void matMultDyn(const DynMat& matA, const DynMat& matB, DynMat& matC, int size);
void matShowDyn(const DynMat& matA, int start, int show_size);

// for Sparse Matrix of dynamically allocated sizes
void matMultDynSp(float** matA, float** matB, float** matC, int size);
void matShowDynSp(float** matA, int mat_size, int start, int show_size);

int main()
{
    int r, c, mat_size;
    clock_t startTime, stopTime;
    double randFrac;
    int randRow, randCol, numElement;
    float smallPercent;

    // easy initialization, but only for fixed-size matrices
    float m[MAT_SIZE][MAT_SIZE] = { {1, 2, 3, 4, 5}, {-1, -2, -3, -4, -5},
       {1, 3, 1, 3, 1}, {0, 1, 0, 1, 0}, {-1, -1, -1, -1, -1} };

    float n[MAT_SIZE][MAT_SIZE] = { {2, 1, 5, 0, 2}, {1, 4, 3, 2, 7},
       {4, 4, 4, 4, 4}, {7, 1, -1, -1, -1}, {0, 0, 8, -1, -6} };

    // for non-sparse dynamic matrix of fixed size
    DynMat mDyn, nDyn, ansDyn;

    // allocate and load
    for (r = 0; r < MAT_SIZE; r++)
    {
        mDyn[r] = new float[MAT_SIZE];
        nDyn[r] = new float[MAT_SIZE];
        ansDyn[r] = new float[MAT_SIZE];

        // move the static data into the dyn input matrices m, n
        for (c = 0; c < MAT_SIZE; c++)
        {
            mDyn[r][c] = m[r][c];
            nDyn[r][c] = n[r][c];

        }
    }

    matMultDyn(mDyn, nDyn, ansDyn, MAT_SIZE);

    cout << "First Matrix, n: " << endl;
    matShowDyn(mDyn, 0, MAT_SIZE);

    cout << "Second Matrix, m: " << endl;
    matShowDyn(nDyn, 0, MAT_SIZE);

    cout << "Product Matrix, n x m: " << endl;
    matShowDyn(ansDyn, 0, MAT_SIZE);

    // clean up
    for (r = 0; r < MAT_SIZE; r++)
    {
        delete mDyn[r];
        delete nDyn[r];
        delete ansDyn[r];
    }
    cout << endl;

    // after the above simple test, work on the Sparse Matrix of different sizes
    cin >> mat_size >> smallPercent;

    //check the input values and reset to MIN or MAX if out of range
    if (mat_size < MIN_MAT_SIZE)
    {
        mat_size = MIN_MAT_SIZE;
    }
    if (smallPercent < MIN_PERCENT)
    {
        smallPercent = MIN_PERCENT;
    }
    else if (smallPercent > MAX_PERCENT)
    {
        smallPercent = MAX_PERCENT;
    }




    // non fixed size dynamic matrix
    float** matDynSp = new float* [mat_size];
    float** matDynSpAns = new float* [mat_size];

    // allocate rows and initialize to 0
    for (r = 0; r < mat_size; r++)
    {
        matDynSp[r] = new float[mat_size];
        matDynSpAns[r] = new float[mat_size];
        for (c = 0; c < mat_size; c++)
        {

            matDynSp[r][c] = 0;

        }


    }
    // initialize random seed to a fixed start 0
    // so it will generate the same random sequence checked by the Auto Grader
    srand(0);

    // generate small % (between .1 and 10.) non-default values (between 0 and 1.0)
    numElement = mat_size * mat_size * smallPercent / 100;
    for (r = 0; r < numElement; r++)
    {

        randFrac = rand() / (double)RAND_MAX;
        randRow = randFrac * mat_size;
        randFrac = rand() / (double)RAND_MAX;

        randCol = randFrac * mat_size;
        randFrac = rand() / (double)RAND_MAX;
        matDynSp[randRow][randCol] = randFrac;

    }



    matShowDynSp(matDynSp, mat_size, mat_size - 10, 10);

    startTime = clock();  // ------------------ start
    matMultDynSp(matDynSp, matDynSp, matDynSpAns, mat_size);
    stopTime = clock();  // ---------------------- stop

    matShowDynSp(matDynSpAns, mat_size, mat_size - 10, 10);

    cout << "\nSize = " << mat_size << " Dyn Array Mult Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    // clean up
    for (r = 0; r < mat_size; r++)
    {
        delete[] matDynSp[r];
        delete[] matDynSpAns[r];
    }

    cout << endl;
}


void matMultDyn(const DynMat& matA, const DynMat& matB, DynMat& matC, int size)
{
    float product = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            product = 0;
            for (int k = 0; k < size; k++)
            {
                product += matA[i][k] * matB[k][j];

            }
            matC[i][j] = product;
        }
    }

}

void matShowDyn(const DynMat& matA, int start, int show_size)
{

    for (int r = start; r < start + show_size; r++) {
        for (int c = start; c < start + show_size; c++)
        {
            cout << setw(6) << setprecision(2) << fixed << matA[r][c] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void matMultDynSp(float** matA, float** matB, float** matC, int size)
{
    float product = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            product = 0;
            for (int k = 0; k < size; k++)
            {
                product += matA[i][k] * matB[k][j];

            }
            matC[i][j] = product;
        }
    }

}

void matShowDynSp(float** matA, int mat_size, int start, int show_size)
{
    int r, c;

    if (mat_size < 10) {
        start = 0;
        show_size = mat_size;
    }

    for (r = start; r < start + show_size; r++) {
        for (c = start; c < start + show_size; c++)
        {
            cout << setw(6) << setprecision(2) << fixed << matA[r][c] << " ";
        }
        cout << endl;
    }

    cout << endl;
}
