#include <sstream>
#include <iomanip>
#include <string.h>
#include <set>
#include "book.h"
#include "util.h"
//#include "product.h"

using namespace std;

Book::Book (const string category, const string name, const double price, const int qty, string ISBN, string author): Product(category, name, price, qty){
  ISBN_ = ISBN;
  author_ = author; 
}

set<string> Book::keywords() const{
  set<string> name = parseStringToWords(name_);
  set<string> author = parseStringToWords(author_);

  set<string> all; //create a set to combine everything
  all = setUnion(name, author);
  all.insert(ISBN_);
  return all;
}

string Book::displayString() const{
  string all;
  stringstream ss;

  ss << name_ << "\n" <<"Author: " << author_ << " ISBN:" << ISBN_ <<"\n" << fixed << setprecision(2) <<price_ <<"\n" <<qty_ << " left."<<"\n";
  all = ss.str();
  return all;
}

void Book::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n"<< fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << "\n"; 
}
