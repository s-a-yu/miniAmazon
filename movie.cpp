#include <sstream>
#include <iomanip>
#include <string.h>
#include <set>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating): Product(category, name, price, qty){
  genre_ = genre;
  rating_ = rating;
}

set<string> Movie::keywords() const{
  set<string> name = parseStringToWords(name_);
  set<string> genre = parseStringToWords(genre_);
  set<string> rating = parseStringToWords(rating_);
  set<string> temp = setUnion(name,genre);
  set<string> all; //create a set to combine everything
  all = setUnion(temp, rating);
  return all;
}

string Movie::displayString() const{
  string all;
  stringstream ss;

  ss << name_ << "\n" <<"Genre: " << genre_ << " Rating: " << rating_ <<"\n" << fixed << setprecision(2) <<price_ <<" " <<qty_ << " left."<< "\n";
  all = ss.str();
  return all;
}

void Movie::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n"; 
}
