#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>


using namespace std;

class Sublist {
public:
	Sublist(vector<int>* orig = NULL) : sum(0), originalObjects(orig) { }
	Sublist addItem(int indexOfItemToAdd);
	void showSublist() const;
	int getSum() const { return sum; }

private:
	int sum;
	vector<int>* originalObjects;
	vector<int> indices;
};


Sublist Sublist::addItem(int indexOfItemToAdd) {
	Sublist sub2 = *this;
	sub2.indices.push_back(indexOfItemToAdd);
	sub2.sum = sum + (originalObjects->at(indexOfItemToAdd));
	return sub2;
}


void Sublist::showSublist() const {
	vector<int>::const_iterator iter;
	int i = 0;

	for (iter = indices.begin(); iter != indices.end(); iter++) {

		cout << "  array[" << indices[i] << "] = " << originalObjects->at(*iter);
		if (iter != indices.end() - 1) cout << ", ";
		else cout << endl << endl;

		i++;
	}
}

int main()

{

	int TARGET;
	vector<int> dataSet;//S
	vector<Sublist> choices;//Col
	vector<int>::iterator sIter;//iterator for the 'S' set of numbers/dataSet
	vector<Sublist>::iterator iter;//iterator arnd iterator to find best sublist
	int i, j, choices_size, maxSum, sum;
	bool foundPerfect;

	dataSet.push_back(20);
	dataSet.push_back(12);
	dataSet.push_back(22);
	dataSet.push_back(15);
	dataSet.push_back(25);
	dataSet.push_back(19);
	dataSet.push_back(29);
	dataSet.push_back(18);
	dataSet.push_back(11);
	dataSet.push_back(13);
	dataSet.push_back(17);

	choices.clear();

	cin >> TARGET;
	cout << "Target time: " << TARGET;
	if (TARGET < 201) cout << "\nSublist ----------------------------- " << endl;
	else cout << "\nSolution is entire master set with sum = 201" << endl;


	Sublist sublist(&dataSet);
	choices.push_back(sublist);
	Sublist sublist2;
	Sublist maxSublist;
	foundPerfect = false;
	maxSum = 0;


	
	for (i = 0; i < dataSet.size(); i++) {
		choices_size = choices.size();
		for (j = 0; j < choices_size; j++) {

			sublist2 = choices[j].addItem(i);
			sum = sublist2.getSum();


			if (sum < TARGET) {
				choices.push_back(sublist2);
				if (sum > maxSum) {
					maxSum = sum;
					maxSublist = sublist2;
				}
			}

			else if (sum == TARGET) {
				foundPerfect = true;
				maxSublist = sublist2;
				break;
			}

		}

		if (foundPerfect) {
			break;
		}


	}

	for (iter = choices.begin(); iter != choices.end(); iter++) {
		iter;
	}

	if (TARGET < 201) cout << "  sum: " << maxSublist.getSum() << endl;
	maxSublist.showSublist();

	return 0;
}