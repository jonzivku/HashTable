// Jon Zivku, jzivku, jonzivku@me.com, HashTable.h, A05 Hash Table
#ifndef HASHTABLE__H
#define HASHTABLE__H

#include <vector>
#include <string>
#include <list>

// abstract base class for data
//   also overload operator= if necessary
//   and/or copy constructor, destructor 


/*
class Record{
 protected:
  int key;
 public:
  virtual
  virtual ~Record() {};
  virtual Record(const Record) = 0;
  virtual int getID() {return key;} ; // or something similar 
  virtual Record *clone()=0;
  // clone method invokes copy constructor
  // to make a copy of the object// or something similar
  
  // anything else that you think is appropriate 
  };
*/


class Record{
 public:
  Record(int p, std::string d){id = p; data = d;};
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
  // postcond: returns a pointer for the last inserted record whose key
  //           matches the argument, otherwise returns NULL
  std::vector<Record> content();
  // 
  // postcond: returns a list of a copy of all Records in the table
 private:
  // find return value: some type of index
  //  Record *find(int); // helper search fn
  //int hash(Record *); // hash value for record
  int hash(int);
  // hash a key
  // pre-cond: an integer
  // poscond: hash index based on argument and tablesize is returned
  const int m; // size of table
  std::list<Record*> *A;
  // array of m lists that hold records

};

#endif
