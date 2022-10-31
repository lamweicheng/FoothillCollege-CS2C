#include <iostream>
#include <string>
using namespace std;
#include "EBookEntry.h"

// ----------- prototypes for hash include -------------
int Hash(const EBookEntry& item);
int Hash(const string& key);
int Hash(int key);

#include "FHhashQPwFind.h"

// ----------- local prototypes -------------
void displayOneEBook(EBookEntry book);
string getKey(const EBookEntry& item);

int main()
{
    FHhashQPwFind<EBookEntry, string> hashTable;  // for string equality
    EBookEntry book;
    int NUM_RANDOM_INDICES;

    cin >> NUM_RANDOM_INDICES;
    EBookEntryReader bookInput("catalog-short4m.txt");
    cout << bookInput.getFileName() << endl;
    cout << bookInput.getNumBooks() << endl;
    cout << "Number of books: " << bookInput.getNumBooks() << endl;

    EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

    srand(0);

    vector<int> randomIndices;
    float randomFrac;
    int randomIndex;
    int numberOfBooks = bookInput.getNumBooks();

    for (int i = 0; i < NUM_RANDOM_INDICES; i++) {
        randomFrac = rand() / (double)RAND_MAX;
        randomIndex = randomFrac * numberOfBooks;
        randomIndices.push_back(randomIndex);
    }
    cout << "Random indices generated: ";
    for (int i = 0; i < NUM_RANDOM_INDICES; i++) {
        cout << randomIndices[i] << " ";
    }
    cout << endl << endl;

    for (int i = 0; i < bookInput.getNumBooks(); i++) {
        hashTable.insert(bookInput[i]);
    }

    cout << "Size of the hash table:  " << hashTable.size() << endl;

    cout << "Some random books from the EBookEntryReader " << endl;
    for (int i = 0; i < NUM_RANDOM_INDICES; i++) {
        displayOneEBook(bookInput[randomIndices[i]]);
    }

    cout << "The same random books from the hash table " << endl;
    for (int k = 0; k < NUM_RANDOM_INDICES; k++)
    {
        try
        {
            book = hashTable.find(bookInput[randomIndices[k]].getCreator());
            cout << "Book #" << randomIndices[k] << " YES: " << book.getCreator().substr(0, 8)
                << " " << book.getTitle().substr(0, 10);
        }
        catch (...)
        {
            cout << "no.  ";
        }
        cout << endl;
    }

    // test known failures exceptions:
    try
    {
        book = hashTable.find("Jack Kerouac");
        cout << "YES: " << book.getCreator().substr(0, 8)
            << " " << book.getTitle().substr(0, 10);
    }
    catch (...)
    {
        cout << "no.  ";
    }

    // test known failures exceptions:
    try
    {
        book = hashTable.find(" no one");
        cout << "YES: " << book.getCreator().substr(0, 8)
            << " " << book.getTitle().substr(0, 10);
    }
    catch (...)
    {
        cout << "no.  ";
    }

    // test known failures exceptions:
    try
    {
        book = hashTable.find("Leacock, Stephen, 2010 - 2009");
        cout << "YES: " << book.getCreator().substr(0, 8)
            << " " << book.getTitle().substr(0, 10);
    }
    catch (...)
    {
        cout << "no.  ";
    }

    return 0;
}




void displayOneEBook(EBookEntry book)
{
    cout << "   # " << book.getETextNum() << "  ---------------" << endl;
    cout << "   \"" << book.getTitle() << "\"" << endl;
    cout << "   by " << book.getCreator() << endl;
    cout << "   re: " << book.getSubject() << endl << endl;
}

int Hash(int key) {
    return key;
}

int Hash(const string& key) {
    unsigned int k, retVal = 0;

    for (k = 0; k < key.length(); k++) {
        retVal = 37 * retVal + key[k];
    }

    return retVal;
}

int Hash(const EBookEntry& item) {
    return Hash(getKey(item));
}

string getKey(const EBookEntry& item) {
    return item.getCreator();
}