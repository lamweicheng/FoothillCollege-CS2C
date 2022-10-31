// Assignment #6 - Quadratic Probing with a find() (Part A) 

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "EBookEntry.h"

// ----------- prototypes for hash include -------------
int Hash( const EBookEntry & item );
int Hash( const string & key );
int Hash( int key );

#include "FHhashQPwFind.h"

// ----------- local prototypes -------------
void displayOneEBook(EBookEntry book);
int getKey( const EBookEntry & item);

int main()
{
   FHhashQPwFind<EBookEntry, int> hashTable;  // for ID equality
   EBookEntry book;
   int NUM_RANDOM_INDICES;
   // ...
   
   cin >> NUM_RANDOM_INDICES;


   EBookEntryReader bookInput("catalog-short4m.txt");
   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl;
   cout << "Number of books: " << bookInput.getNumBooks() << endl; 
   
   srand (0);      
   
   vector<int> randomIndices;
   float randFrac;
   int randIndex;
   int numberOfBooks = bookInput.getNumBooks();
   
   for(int i = 0; i < NUM_RANDOM_INDICES; i++){
      randFrac = rand() / (double)RAND_MAX;
      randIndex = randFrac * numberOfBooks;
      randomIndices.push_back(randIndex);
   }
   cout << "Random indices generated: ";
   for(int i = 0; i < NUM_RANDOM_INDICES; i++){
      cout << randomIndices[i] << " ";
   }
   cout << endl << endl;
   
   for(int i = 0; i < bookInput.getNumBooks(); i++){
      hashTable.insert(bookInput[i]);
   }
   
   cout << "Size of the hash table:  " << hashTable.size() << endl;

   cout << "Some random books from the EBookEntryReader " << endl;
   for(int i = 0; i < NUM_RANDOM_INDICES; i++){
      displayOneEBook(bookInput[randomIndices[i]]);
   }
   
  

   // attempt to find on the selected key
   cout << "The same random books from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         book = hashTable.find(bookInput[randomIndices[k]].getETextNum());
         cout << "Book #" << randomIndices[k] << " YES: " << book.getCreator().substr(0,8) << " " << book.getTitle().substr(0,10);
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
      book = hashTable.find( -3 );
      cout << "YES: " << book.getCreator().substr(0,8)
         << " " << book.getTitle().substr(0,10); 
   }
   catch (...)
   {
      cout << "no.  ";
   }

   // test known failures exceptions:
   try
   {
      book = hashTable.find( 9000 );
       cout << "YES: " << book.getCreator().substr(0,8)
         << " " << book.getTitle().substr(0,10);
   }
   catch (...)
   {
      cout << "no.  ";
   }

   // test known failures exceptions:
   try
   {
      book = hashTable.find( 5000 );
       cout << "YES: " << book.getCreator().substr(0,8)
         << " " << book.getTitle().substr(0,10);
   }
   catch (...)
   {
      cout << "no.  ";
   }

   return 0;
}


void displayOneEBook(EBookEntry book)
{
   cout << "   # "<< book.getETextNum() << "  ---------------" << endl;
   cout << "   \"" << book.getTitle() <<"\"" << endl;
   cout << "   by " << book.getCreator()  << endl;
   cout << "   re: " << book.getSubject() << endl << endl;
}


int Hash(const EBookEntry& item)
{
    return Hash(item.getETextNum());  // used for ID equality
                                      //return Hash( item.getCreator() );  // used for author equality
}

// a hash routine for strings that admits negative returns
int Hash(const string& key)
{
    unsigned int k, retVal = 0;

    for (k = 0; k < key.length(); k++)
        retVal = 37 * retVal + key[k];

    return retVal;
}

int Hash(int key)
{
    return key;
}

// used for ID equality
int getKey(const EBookEntry& item)
{
    return item.getETextNum();
}