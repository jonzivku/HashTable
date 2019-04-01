// Jon Zivku, jzivku, jonzivku@me.com, HashTable.cpp, A05 Hash Table
#include <cmath>
#include <iostream> // for testing
#include <sstream>
#include <iomanip>
#include "HashTable.h"

/*Record::Record(const Record &p2){ unneccessary because dynamic classes
  id = p2.id;
  data = p2.data;
  }*/


//using std::vector;
using std::endl;
using std::cout;

std::string Record::str(){
  std::stringstream ss;
  ss << std::setw(9) << std::setfill('0') << id << data;
  return ss.str();
}
  
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
  // int index = hash(s->getId());
  A[hash(s->getId())].push_front(s);
  // cout << "the table at spot " << index << " has " << A[index].size() << endl;
  
}

void HashTable::remove(int key){
  int index = hash(key);
  if (!A[index].empty()){
    //if list is not empty
    //iterate through the list at A[hash(key)
    for (std::list<Record*>::iterator it = A[index].begin();
	 it != A[index].end(); ++it)
      if((*it)->getId() == key){
	delete *it; *it = NULL;
	A[index].erase(it);
	return;
      }
  }       
}

Record *HashTable::search(int key){
  int index = hash(key);
  if (!A[index].empty()){
    //if list is not empty
    //iterate through the list at A[hash(key)
    for (std::list<Record*>::iterator it = A[index].begin();
	 it != A[index].end(); ++it)
      if((*it)->getId() == key)
	return *it;
    //return the first Record* whose Id matches key
    // once the for loop is done, return NULL
    // return A[hash(key)].front();
  }
  return NULL;
}

int HashTable::hash(int key){
  double c = (sqrt(5)-1)/2; // our constant for hashing
  return floor( m * ( key*c - floor(key*c)));
}

