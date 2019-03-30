// Jon Zivku, jzivku, jonzivku@me.com, HashTable.h, A05 Hash Table
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
  //Record(const Record &p2); // maybe not needed?
  //std::string toString(){return
  int getId(){return id;}
  std::string getData(){return data;}
 private:
  int id;
  std::string data;
  };

class HashTable{
public:
  HashTable(int=100); // build a table
  ~HashTable();
  void insert(Record *); // insert copy of record
  void remove(int); // remove a record
  Record *search(int); //segfault in here
  // return pointer to a copy of found record, or 0
 private:
  // find return value: some type of index
  Record *find(int); // helper search fn
  int hash(Record *); // hash value for record
  int hash(int); // hash value for key  
  const int m; // size of table
  
  std::list<Record*> *A;
  // array of m lists that hold records
  // other members as desired
};



