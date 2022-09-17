#ifndef BOOK_H
#define BOOK_H
#include <product.h>

class Book: public Product{
  public:

    Book(const std::string category, const std::string name, double price, int qty, string ISBN, string author);
    void dump(std::ostrem& os) const;
    std::set<std::string> keyword const; 
    std::string displayString() const;
  
  private:
    string ISBN;
    string author; 
}


#endif