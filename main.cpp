// Jon Zivku, jzivku, jonzivku@me.com, main.cpp, A05 Hash Table

/* 
   Status: compiling/tested/unfinished

   Went with std::list<Record*> for this one, to keep insert and delete at O(1). This also gave me a chance to work with iterators. and reverse_iterators - pointers galore! one tricky thing to deal with was being aware that a library function would remove a pointer without calling delete. valgrind was wildly handy here. I might try an abstract class implementation for Record... that could be interesting.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "HashTable.h"

using std::cin;
using std::cout;
using std::endl;

std::string nineDig(int key){
  std::stringstream ss;
  ss << std::setw(9) << std::setfill('0') << key;
  return ss.str();
}

int main(){
  //  int m = 178000; // fuck around with a way too small table
  int m = 3;
  int option;
  int key;
  std::string data;
  std::string filename;
  Record* temp;
  HashTable *A = new HashTable(m);
  
  while(true){
    
    cout << "(1)load (2)insert (3)delete (4)search (5)clear (6)save (7)quit -- "
	 << "Your choice? ";
    cin >> option;
    if(option == 1){
      cout << "read hash table - filename? ";
      cin >> filename;
      
      std::ifstream input(filename.c_str(), std::ios::in);
      if(!input.fail()){
	while(!input.eof()){//ill try eof next
	  input >> key;
	  getline(input, data, ' ');
	  getline(input, data);
	  //if(!input.eof()){ // feels like a hack
	  temp = new Record(key, data);
	  cout << "inserting: " << temp->str() << endl;
	  A->insert(temp); // memory leak here?
	  // can still search and delete the record
	  // if i delete it, no memory leak recorded, no errors
	  delete temp; temp = NULL;
	    //}
	}
	input.close();/*
	while(input){//ill try eof next
	  input >> key;
	  getline(input, data, ' ');
	  getline(input, data);
	  if(!input.eof()){ // feels like a hack
	    temp = new Record(key, data);
	    cout << "inserting: " << temp->str() << endl;
	    A->insert(temp); // memory leak here?
	    // can still search and delete the record
	  // if i delete it, no memory leak recorded, no errors
	    delete temp; temp = NULL;
	  }
	}
	input.close();*/
      }else{
	cout << "Invalid filename: " << filename << endl; 
      }
    }

    else if(option == 2){
      cout << "input new record:" << endl;
      cin >> key;
      getline(cin, data, ' '); //toss ws character
      getline(cin, data);
      temp = new Record(key, data);
      A->insert(temp);
      delete temp; temp = NULL;
    }

    else if(option == 3){
      cout << "delete record - key? ";
      cin >> key;
      cout << endl;
      // search for the record
      temp = A->search(key);
      // if temp, display key, data
      if(temp){
      	cout << "Delete: " << temp->str() << endl;
	A->remove(key);
      }else{
	cout << "Delete not found: " << nineDig(key) << endl;
      }	
    }

    else if(option == 4){
      cout << "search for record - key? ";
      cin >> key;
      cout << endl;
      temp = A->search(key);
      if(temp){ 
	cout << "Found: " << temp->str() << endl;
      }else{
	cout << "Search not found: " << nineDig(key) << endl;
      }	
    }

    else if(option == 5){//clear
      cout << "clearing hash table." << endl;
      delete A; A = new HashTable(m);  
    }
    
    else if(option == 6){ // write to file
      cout << "write hash table - filename? ";
      cin >> filename;
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
