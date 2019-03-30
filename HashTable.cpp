// Jon Zivku, jzivku, jonzivku@me.com, HashTable.cpp, A05 Hash Table
#include <cmath>
#include <iostream>
#include "HashTable.h"

/*Record::Record(const Record &p2){ unneccessary because dynamic classes
  id = p2.id;
  data = p2.data;
  }*/

//using std::vector;
using std::list;
using std::endl;
using std::cout;

HashTable::HashTable(int pSize) : m(pSize){
  A = new std::list<Record*>[m];
}

HashTable::~HashTable(){
  for(int i = 0; i < m; i++)
    while(!A[i].empty()){
      delete A[i].front(); A[i].front() = NULL;
      A[i].pop_back();
    }
  delete [] A;
    //for(int j = A[i].size()-1; j >= 0; j--)
    //delete A[i][j]; A[i][j] = NULL; 
}


//does it need a copy constructor?
 
//which order should insert and delete happen in?
void HashTable::insert(Record *r){
  if (!r)
    return;
  Record *s = new Record(r->getId(), r->getData());
  int index = hash(s->getId());
  A[hash(s->getId())].push_front(s);
  cout << "the table at spot " << index << " has " << A[index].size() << endl;
  
}

void HashTable::remove(int key){
  if (!A[hash(key)].empty()){
    delete A[hash(key)].front(); A[hash(key)].front() = NULL;
    A[hash(key)].pop_back();
  }
   
}

Record *HashTable::search(int key){
  if (!A[hash(key)].empty())
    return A[hash(key)].front();
  else
    return NULL;
}

int HashTable::hash(int key){
  double c = (sqrt(5)-1)/2; // our constant for hashing
  return floor( m * ( key*c - floor(key*c)));
}

