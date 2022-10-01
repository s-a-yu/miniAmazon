#include <sstream>
#include <iomanip>
#include <string.h>
#include <set>
#include "movies.h"
#include "util.h"

using namespace std;

Movies::Movies(const string category, const string name, double price, int qty, string genre, string rating): Product(category, name, price, qty){
  genre_ = genre;
  rating_ = rating;
}

set<string> Movies::keywords() const{
  set<string> name = parseStringToWords(name_);
  set<string> genre = parseStringToWords(genre_);
  set<string> rating = parseStringToWords(rating_);
  set<string> temp = setUnion(name,genre);
  set<string> all; //create a set to combine everything
  all = setUnion(temp, rating);
  return all;
}

string Movies::displayString() const{
  string all;
  stringstream ss;
  //all = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + price + + "\n" + to_string(qty_) + " left.";

  ss << name_ << "\n" <<"Genre: " << genre_ << " Rating:" << rating_ <<"\n" << fixed << setprecision(2) <<price_ <<"\n" <<qty_ << " left."<< "\n";
  all = ss.str();
  return all;
}

void Movies::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n"; 
}
