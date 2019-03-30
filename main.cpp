// Jon Zivku, jzivku, jonzivku@me.com, main.cpp, A05 Hash Table

/* 
   Status: compiling/tested
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "HashTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ostream;

void loadTable(ifstream& input);


int main(){
  int m = 178000;
  int option;
  int key;
  string data;
  string filename;
  Record* temp;
  HashTable *A = new HashTable(m);
  
  while(true){
    
    cout << "(1)load (2)insert (3)delete (4)search (5)clear (6)save (7)quit -- "
	 << "Your choice? ";
    cin >> option;
    if(option == 1){
      cout << "read hash table - filename? ";
      cin >> filename;
      
      ifstream input(filename.c_str(), std::ios::in);
      if(!input.fail()){
	//run load function to fill hash table
	loadTable(input);
	//undefined function

	input.close();
      }else{
	cout << "Invalid filename: " << filename << endl; 
      }
    }
    else if(option == 2){
      cout << "input new record:" << endl;
      cin >> key;
      getline(cin, data);
      // make a new record
      temp = new Record(key, data);
      // run insert DONT FORGET ABOUT PRIVACY LEAK
      A->insert(temp);
      delete temp; temp = NULL;
    }
    else if(option == 3){
      cout << "delete record - key? ";
      cin >> key;
      // search for the record
      temp = A->search(key);
      // if temp, display key, data
      if(temp){
      	cout << "Delete: " << std::setw(9) << std::setfill('0')
	     << temp->getId() << " " << temp->getData() << endl;
	A->remove(key);
      }else{
	cout << "Delete not found: "
	     << std::setw(9) << std::setfill('0') << key << endl;
      }	
    }
    else if(option == 4){
      cout << "search for record - key? ";
      cin >> key;
      cout << endl;
      temp = A->search(key); //segfault in this call when invalid
      // cout << "search completed" << endl; //testing
      if(temp){ 
	cout << "Found: " << std::setw(9) << std::setfill('0')
	     << temp->getId() << temp->getData() << endl;
      }else{
	cout << "Search not found: "
	     << std::setw(9) << std::setfill('0') << key << endl;
      }	
    }
    else if(option == 5){//clear
      cout << "clearing hash table." << endl;
      delete A; A = new HashTable(m);  
    }
    else if(option == 6){ // write to file
      cout << "write hash table - filename? ";
      cin >> filename;
      // open ostream, check for fail, write. maybe a record.tostring would be appropriate?
    }else if(option == 7){
      delete A; A = NULL;
      return 0;
    }
  }
}

void loadTable(ifstream& input){
  
}

ostream &nineDig(ostream &output){
  output << std::setw(9) << std::setfill('0');
  return output;
}