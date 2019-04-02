// Jon Zivku, jzivku, jonzivku@me.com, HashTable.h, A05 Hash Table
#ifndef HASHTABLE__H
#define HASHTABLE__H

#include <vector>
#include <string>
#include <list>

class Record{
 public:
  Record(int p = -1, std::string d = " "){id = p; data = d;};
  int getId(){return id;} // accessor for id/key
  std::string getData(){return data;} // accessor for data
  std::string str(); // returns a formatted string of "[id] [key]"
 private:
  int id;
  std::string data;
  };

class HashTable{
public:
  HashTable(int=100); // build a table
  ~HashTable();
  void emptyTable();
  // postcond: the table has been emptied
  void insert(Record *);
  // insert a record by key
  // postcond: a copy of the record is placed in the table
  void remove(int);
  // remove a record by key
  // pre-cond: a key for the record
  // postcond: removes last inserted record whose key
  //           matches the argument.
  Record *search(int);
  // search for a record by key
  // pre-cond: a key for the record
  // postcond: returns a pointer to a copy of the last inserted record whose key
  //           matches the argument, otherwise returns NULL
  std::vector<Record> content();
  // postcond: returns a vector of a copy of all Records in the table
 private:
  Record* find(int); 
  // pre-cond: a key for the record
  // postcond: returns an iterator to the last inserted record whose key
  //           matches the argument, otherwise returns NULL
  int hash(int);// hash a key
  // pre-cond: an integer
  // poscond: hash index based on argument and tablesize is returned
  const int m; // size of table
  std::list<Record*> *A;
  // array of m lists that hold records
};

#endif
