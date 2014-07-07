#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Item
{
private:
  string name_;
  int qty_;
  double price_;
public:
  Item();
  Item(string name, int qty, double price);
  string getName() const;
  int getQty() const;
  double getPrice() const;
  void setName(string name);
  void setQty(int qty);
  void setPrice(double price);
};

Item::Item() {
  name_ = ""; qty_ = -1; price_ = -1; 
}

/* Complete the Item class methods here */

// Constructors
Item::Item(string name, int qty, double price) { 
  name_ = name;
  qty_ = qty;
  price_ = price;
}


// Accessors
string Item::getName() const {
  return name_;
}

int Item::getQty() const {
  return qty_;
}

double Item::getPrice() const {
  return price_;
}


// Mutators
void Item::setName(string name) {
  name_ = name;
}

void Item::setQty(int qty) {
  qty_ = qty;
}

void Item::setPrice(double price) {
  price_ = price;
}



// Prototypes
void printItems(const Item *items, const int len);
Item *readData(const char *filename, int &len);

// Accepts a data filename as a command line arguments
int main(int argc, char *argv[])
{
  if(argc < 2){
    cerr << "Please supply an input filename as a command line argument" << endl;
    return 1;
  }
  int len;
  Item *dataArray = readData(argv[1], len); 
  if(dataArray == NULL){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;	
  }
  cout << "Read " << len << " Items from the file: " << argv[1] << endl;
  printItems(dataArray, len);

  // Add a statement to deallocate the dataArray memory
  delete [] dataArray;
  return 0;
}

// Print Item information in a tabular format
void printItems(const Item *items, int len)
{
  cout << setw(15) << "Name" << setw(10) << "Qty" << setw(10) << "Price" << endl;
  for (int i = 0; i < len; i++) {
    cout.precision(2);
    cout << setw(15) << items[i].getName() << setw(10) << items[i].getQty() << setw(10) << fixed << items[i].getPrice() << endl;
  }
}


// Read Items from a datafile and store them in an array 
//  Return the address of the array and update the len
//  argument.
Item *readData(const char *filename, int &len)
{
  ifstream openfile(filename);
  if ( !openfile.is_open() ) {
    return NULL;
  }
  if ( openfile.fail() ) {
    return NULL;
  }
  string line;
  // get first line from data text file, will represent how many lines of data are in the file
  getline(openfile, line);
  len = atoi(line.c_str());
  line.clear();

  // create the Item* array
  Item *array = new Item[len];

  // using data from first line, parse rest of data and create items accordingly
  string name;
  int qty;
  double price;
  for (int i = 0; i < len; i++ ) {
     getline(openfile, line, ' ');
     name = line;
     line.clear();

     getline(openfile, line, ' ');
     qty = atoi(line.c_str());
     line.clear();

     getline(openfile, line);
     price = atof(line.c_str());
     line.clear();

     Item *current = new Item(name, qty, price);
     array[i] = *current;
  }
  return array;  

}
