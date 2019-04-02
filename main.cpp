// Jon Zivku, jzivku, jonzivku@me.com, main.cpp, A05 Hash Table

/* Status: compiling/finished/tested
  Known issues: (3)delete and (4)search act weird when newline is input
                insert(string,HashTable) doesnt like being sent empty input
   Went with std::list<Record*> for this one, to keep insert and delete at O(1). This also gave me a chance to work with iterators. and reverse_iterators - pointers galore! one tricky thing to deal with was being aware that a library function would remove a pointer without calling delete. valgrind was wildly handy here. I might try an abstract class implementation for Record... that could be interesting. I was concerned about negative inputs, but the hash function is wildly robust for its simplicity, always giving a value from 0 to m-1. The toughest part of this assignment was probably the input processing for me - making the code robust enough to handle white space took some time and research.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include "HashTable.h"

using std::cin;
using std::cout;
using std::endl;

void insert(std::string, HashTable*);
// pre-cond: a string in the format "[int] [data]", and a pointer to HashTable
// postcond: a record with key int and data data, is placed in the table

std::string nineDig(int);
// pre-cond: an integer of 9 digits or less
// postcond: int returned as a string with leading '0's and a width of 9

int main(){
  int m = 178000;  
  HashTable *A = new HashTable(m);
  int option;
  int key;
  std::string data;
  std::string filename;  
  Record* temp = NULL;
  std::string buff;
  
  while(true){
    cout << "(1)load (2)insert (3)delete (4)search (5)clear (6)save (7)quit -- "
	 << "Your choice? ";
    std::getline(cin, buff);
    std::istringstream iss(buff);    
    iss >> option;

    if(option == 1){
      cout << "read hash table - filename? ";
      getline(cin, filename);
      std::ifstream input(filename.c_str(), std::ios::in);
      if(!input.fail()){
	input.ignore(0, '\n' );
	while(std::getline(input, buff)){
	  insert(buff, A);
	  input.ignore(0, '\n' );
	}//end of while(getline)
	input.close();
      }// end of if(!input.fail())
      else
	cout << "Invalid filename: " << filename << endl; 
    }

    else if(option == 2){//input
      cout << "input new record:" << endl;
      std::getline(cin, buff);
      insert(buff, A);
    }

    else if(option == 3){//delete
      cout << "delete record - key? ";
      std::getline(cin, buff);
      std::istringstream iss(buff);    
      iss >> key;
      cout << endl;
      // search for the record
      temp = A->search(key);
      // if temp, display key, data
      if(temp){
      	cout << "Delete: " << temp->str() << endl;
	A->remove(key);
	delete temp; temp = NULL;
      }else{
	cout << "Delete not found: " << nineDig(key) << endl;
      }	
    }

    else if(option == 4){//search
      cout << "search for record - key? ";
      std::getline(cin, buff);
      std::istringstream iss(buff);
      iss >> key;
      cout << endl;
      temp = A->search(key);
      if(temp){ 
	cout << "Found: " << temp->str() << endl;
	delete temp; temp = NULL;
      }else{
	cout << "Search not found: " << nineDig(key) << endl;
      }	
    }

    else if(option == 5){//clear
      cout << "clearing hash table." << endl;
      A->emptyTable();
    }
    
    else if(option == 6){ // write to file
      cout << "write hash table - filename? ";
      getline(cin, filename);
      std::ofstream output(filename.c_str(), std::ios::out);
      if(!output.fail()){
	std::vector<Record> content = A->content(); 
	for(std::vector<Record>::iterator it = content.begin();
	    it != content.end(); ++it)
	  output  << it->str() << endl;	  
	content.clear();
	output.close();
      }else
	cout << "invalid filename: " << filename << endl;
    }

    else if(option == 7){
      delete A; A = NULL;
      return 0;
    }
  }
}

void insert(std::string buff, HashTable* A){
  std::istringstream iss(buff);
  char toss;
  int key;
  std::string data = "";
  iss >> key;
  iss.get(toss);
  std::getline(iss, data);
  Record *temp = new Record(key, data);
  A->insert(temp);
  delete temp; temp = NULL;
}

std::string nineDig(int key){
  std::ostringstream ss;
  ss << std::setw(9) << std::setfill('0') << key;
  return ss.str();
}
