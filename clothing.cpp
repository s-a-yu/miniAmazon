#include <sstream>
#include <iomanip>
#include <string.h>
#include <set>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing (const string category, const string name, double price, int qty, string size, string brand): Product(category, name, price, qty){
  size_ = size;
  brand_ = brand;
}

set<string> Clothing::keywords() const{
  set<string> name = parseStringToWords(name_);
  set<string> size = parseStringToWords(size_);
  set<string> brand = parseStringToWords(brand_);
  set<string> temp = setUnion(name,size);
  set<string> all; //create a set to combine everything
  all = setUnion(temp, brand);
  return all;
}

string Clothing::displayString() const{
  string all;
  stringstream ss;
  ss << name_ << "\n" <<"Size: " << size_ << " Brand: " << brand_ <<"\n" << fixed << setprecision(2) <<price_ <<"\n" <<qty_ << " left."<< "\n";
  all = ss.str();
  return all;
}

void Clothing::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n"; 
}
