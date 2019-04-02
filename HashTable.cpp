// Jon Zivku, jzivku, jonzivku@me.com, HashTable.cpp, A05 Hash Table
#include <cmath>
#include <iostream> // for testing
#include <sstream>
#include <iomanip>
#include "HashTable.h"

//for testing
using std::endl;
using std::cout;

std::string Record::str(){
  std::stringstream ss;
  ss << std::setw(9) << std::setfill('0') << id << " " << data;
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
}

void HashTable::insert(Record *r){
  if (!r)
    return;
  Record *s = new Record(r->getId(), r->getData());
  int index = hash(s->getId()); //testing
  A[hash(s->getId())].push_front(s);
  cout << "the table at index " << index << " has " << A[index].size() << " elements" << endl;
  //testing 
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
    // once the for loop is done, return NULL for no match
  }
  return NULL;
}

std::vector<Record> HashTable::content(){
  std::vector<Record> content;
  // iterate through A
  for(int i = 0; i < m; i++){
    if(!A[i].empty()){ // if A[i] is not empty
      // iterate through list at A[i] and copy records to content
      for(std::list<Record*>::reverse_iterator rit = A[i].rbegin();
	  rit != A[i].rend(); ++rit){
	content.push_back(**rit); //two-star programming!
	//testing
	std::cout << (*rit)->str() << std::endl;
      }
    }
  }
  return content;
}

int HashTable::hash(int key){
  double c = (sqrt(5)-1)/2; // our constant for hashing
  return floor( m * ( key*c - floor(key*c)));
}

