// ---------------------------------------------------------------------------
// Assignment #1 The Subset-Sum Problem Part B - iTunes Version

#include <iostream>
#include <string> 
#include <vector>
#include "iTunes.h"
#include <time.h>
using namespace std;

// global scope function prototypes ----------------
int operator+(int n, const iTunesEntry& tune);
ostream& operator<<(ostream& out, const iTunesEntry& tune);

// global scope helper
double computeMasterSum(vector<iTunesEntry> data);
void showEntireVector(vector<iTunesEntry> data);

// --------------- Sublist Prototype ---------------
//class Sublist
//{
//	// code provided by student
//	//
//	//
//
//public:
//	Sublist addItem(int indexOfItemToAdd);
//	void showSublist() const;
//
//	// code provided by student
//	//
//	//
//};
class Sublist {
public:
	Sublist(vector<iTunesEntry>* orig = NULL) : sumOfTimes(0), originalObjects(orig) {}
	Sublist addItem(int indexOfItemToAdd);
	void showSublist() const;
	int getSumOfTimes() const { return sumOfTimes; }

private:
	int sumOfTimes;
	vector<iTunesEntry>* originalObjects;
	vector<int> indices;
};

// ------------------ main ------------------

int main()
{
	int target = 3600;
	vector<iTunesEntry> dataSet;
	vector<Sublist> choices;
	int  arraySize, numSets, indexOfMax, last_input, maxSum;


	// read the data
	iTunesEntryReader tunesInput("itunes_file.txt");
	if (tunesInput.readError())
	{
		cout << "couldn't open " << tunesInput.getFileName()
			<< " for input.\n";
		exit(1);
	}

	// time the algorithm -------------------------
	clock_t startTime, stopTime;
	startTime = clock();

	// create a vector of objects for our own use:
	arraySize = tunesInput.getNumTunes();
	for (int k = 0; k < arraySize; k++)
		dataSet.push_back(tunesInput[k]);

	cin >> target;
	cout << "Target time: " << target << endl;

	// dispose of easy case immediately to save lots of time
	Sublist empty(&dataSet);
	choices.push_back(empty);
	numSets = 1;
	indexOfMax = 0;
	maxSum = 0;

	for (long unsigned int m = 0; m < dataSet.size(); m++) {
		maxSum = maxSum + dataSet[m];
	}


	if (target > maxSum)
	{
		cout << "Solution is entire master set with sum = " << maxSum << endl;

		cout << "  array[" << 0 << "] = " << dataSet[0] << ",   ";

		for (long unsigned int m = 0; m < dataSet.size() - 1; m++)
			cout << "array[" << m << "] = " << dataSet[m] << ",   ";

		last_input = dataSet.size() - 1;
		cout << "array[" << last_input << "] = ";
		cout << dataSet[last_input] << endl;
		cout << "" << endl;

	}
	else {
		bool found_solution = false;

		for (long unsigned int i = 0; i < dataSet.size(); i++) {
			if (found_solution == true) break;

			int value = dataSet[i].getTime();

			for (int j = 0; j < numSets; j++) {
				int choices2 = choices[j].getSumOfTimes() + value;
				if (choices2 <= target)
					choices.push_back(choices[j].addItem(i));

				if (choices2 == target) {
					indexOfMax = choices.size() - 1;
					found_solution = true;
					break;

				}
			}
			numSets = choices.size();
		}

		if (indexOfMax == 0) {

			for (long unsigned int k = 0; k < choices.size(); k++) {
				if (choices[k].getSumOfTimes() > choices[indexOfMax].getSumOfTimes()) {
					indexOfMax = k;
					break;
				}
			}
		}
		choices[indexOfMax].showSublist();
	}



	/*		stopTime = clock();
			cout << "\nAlgorithm Elapsed Time: "
				<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
				<< " seconds." << endl << endl;
	*/
	return 0;

}

// global scope functions ---------------------------
//int operator+(int n, const iTunesEntry & tune)
//{
//	// code provided by student
//	//
//	// 
//}
//
//ostream & operator<<(ostream & out, const iTunesEntry & tune)
//{
//	// code provided by student
//	//
//	//
//}
ostream& operator<<(ostream& out, const iTunesEntry& tune)
{
	out << tune.getTitle() << " by " << tune.getArtist();
	out << "(" << tune.getTime() << ") ";
	return out;
}

int operator+(int num, const iTunesEntry& tune)
{
	return num + tune.getTime();
}

//// Helper method to compute full sum
//double computeMasterSum(vector<iTunesEntry> data)
//{
//	// code provided by student
//	//
//	//
//}
//
//void showEntireVector(vector<iTunesEntry> data)
//{
//	// code provided by student
//	//
//	//
//}

// --------------- Sublist Method Definitions ---------------

void Sublist::showSublist() const
{
	int k;

	cout << "Sublist ----------------------------- " << endl;
	cout << "  sum: " << sumOfTimes << endl;
	for (k = 0; k < (int)indices.size(); k++)
		cout << "  array[" << indices[k] << "] = "
		<< (*originalObjects)[indices[k]]
		<< ((k == (int)indices.size() - 1) ? "\n\n" : " , ");
}

Sublist Sublist::addItem(int indexOfItemToAdd)
{
	Sublist sub2 = *this;
	sub2.indices.push_back(indexOfItemToAdd);
	sub2.sumOfTimes = sumOfTimes + (originalObjects->at(indexOfItemToAdd)).getTime();
	return sub2;

}