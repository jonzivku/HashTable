// Jon Zivku, jzivku, jonzivku@me.com, HashTable.cpp, A05 Hash Table
#include <cmath>
#include <sstream>
#include <iomanip>
#include "HashTable.h"

// uses <sstream>, <iomanip>
std::string Record::str(){
  std::stringstream ss;
  ss << std::setw(9) << std::setfill('0') << id << " " << data;
  return ss.str();
}
// uses <list>
HashTable::HashTable(int pSize) : m(pSize){
  A = new std::list<Record*>[m];
}

HashTable::~HashTable(){
  emptyTable();
  delete [] A;
}

// uses <list>
void HashTable::emptyTable(){
  for(int i = 0; i < m; i++){
    for(std::list<Record*>::iterator it = A[i].begin();
	it != A[i].end(); ++it){
      delete *it; *it = NULL;
    }
     A[i].clear();
  } 
}
// uses <list>, Record::getId(), Record::getData(), HashTable::hash(int)
void HashTable::insert(Record *r){
  if (!r)
    return;
  Record *s = new Record(r->getId(), r->getData());
  A[hash(s->getId())].push_front(s); s = NULL;
}

// uses <list> 
void HashTable::remove(int key){
  int i = hash(key);
    for(std::list<Record*>::iterator it = A[i].begin(); it != A[i].end(); ++it){
      if((*it)->getId() == key){
	  delete *it; *it = NULL;
	  A[i].erase(it);
	  return;
	}
    }
}

// uses HashTable::find(int)
Record *HashTable::search(int key){
  Record* temp = find(key); 
  if(temp){
    //if it exists, make a copy and return it
    Record *cp = new Record();
    *cp = *temp;
    return cp; temp = NULL;
  }
  else
    return NULL;
}
// uses <vector>, <list>
std::vector<Record> HashTable::content(){
  std::vector<Record> content;
  // iterate through A
  for(int i = 0; i < m; i++){
      // iterate through list at A[i] and copy records to content
      for(std::list<Record*>::reverse_iterator rit = A[i].rbegin();
	  rit != A[i].rend(); ++rit){
	content.push_back(**rit); //two-star programming!
      }// end of for(std::list...
  }// end of for(int i...
  return content;
}

// uses <list>, Record::getId()
Record* HashTable::find(int key){
  int i = hash(key);
    //iterate through the list at A[hash(key)]
    for(std::list<Record*>::iterator it = A[i].begin(); it != A[i].end(); ++it){
      if((*it)->getId() == key)
	return *it;
      //return the first Record* whose Id matches key
    }// once the for loop is done, return NULL for no match
  return NULL;
}

// uses <cmath>
int HashTable::hash(int key){
  double c = (sqrt(5)-1)/2; // our constant for hashing
  return floor( m * ( key*c - floor(key*c)));
}

