#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "util.h"
#include <map>
#include <vector>
#include "datastore.h"
#include <set>

class myDataStore: public DataStore{
  public:
    myDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addCart(std::string username, Product* p);
    void viewCart(std::string username);
    void buyCart(std::string username);

  private:
    std::vector <Product*> products;
    std::vector <User*> users;
    std::map <std::string, std::set<Product*>> productKeywords; //a map to store products and their keywords
    std::map <std::string, User*> userProfile; 
    std::map <std::string, std::vector<Product*>> carts; //for cart , username, and cart
};

#endif 