#include "mydatastore.h"
#include "datastore.h"
#include <map>
#include <vector>
#include <set>
#include "product.h"
#include "user.h"
#include <string>
using namespace std;

myDataStore::myDataStore(){
}
//adds a product to the data store
void myDataStore::addProduct(Product* p){
  products.push_back(p); //add p to vector storing pointers to products
  
  //check keywords associated with p
  set<string> pKeywords = p -> keywords();
  
  for(set<string>::iterator it = pKeywords.begin(); it != pKeywords.end(); ++it){
    if(productKeywords.find(*it) != productKeywords.end()){
      //it is in map already
      productKeywords.find(*it)->second.insert(p);
    }
    else{
      //it is not in map already 
      set<Product*> buff;
      buff.insert(p);
      productKeywords.insert(make_pair(*it, buff));

    }
  }
}
//adds a user to the data store
void myDataStore::addUser(User* u){
  users.push_back(u);
  userProfile.insert(make_pair(u->getName(), u));
}

/* Performs a search of products whose keywords match the given "terms"
  type 0 = AND search (intersection of resutls for each term) while
  type 1 = OR search (union of results for each term)
*/
vector<Product*> myDataStore::search(vector<string>& terms, int type){
 set<Product*> s1 = productKeywords[terms[0]];
 //set<Product*> s1;

  for(unsigned int i=0; i<terms.size(); i++){
    //productKeywords[terms[i]]??
    if(productKeywords.find(terms[i]) != productKeywords.end()){
      if(type == 0){
        s1 = setIntersection(productKeywords[terms[i]], s1);
      }
      else if(type == 1){
        s1 = setUnion(productKeywords[terms[i]], s1);
      }
    }

  }

  //needs to return vector 
  vector<Product*> v;
  for(set<Product*>::iterator it = s1.begin(); it != s1.end(); ++it){
    v.push_back(*it);
  }

  return v; 
}

//Reproduce the database file from the current Products and User values 
void myDataStore::dump(ostream& ofile){
  ofile << "<products>" << endl;
  for(vector<Product*>:: iterator it = products.begin(); it != products.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile<< "<users>" << endl;
  for(vector<User*>:: iterator it = users.begin(); it != users.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</users>"<< endl;
}

void myDataStore::addCart(string username, Product* p){
  for(map<string, User*>:: iterator it = userProfile.begin(); it != userProfile.end(); ++it){
    if(userProfile.find(it->first) != userProfile.end()){
      //username exists
      carts[username].push_back(p);
      break;
    }
    else{
      cout << "Invalid request" << endl;
    }
  }
  
}

void myDataStore::viewCart(string username){
  int count = 1;
  for(map<string, vector<Product*>> ::iterator it = carts.begin(); it!= carts.end(); ++it){
    if(carts.find(username) != carts.end()){
    //username exists
      map<string, vector<Product*>> :: iterator it = carts.find(username);
      for(vector<Product*>::iterator It2 = it->second.begin(); It2 != it->second.end(); ++It2){
        cout << count << endl;
        cout <<(*It2)->displayString()<<endl;
        //it++;
        count ++;
      }
      //return;
    }
    else{
      cout<< "Invalid username" <<endl;
    }
  }

   
}

void myDataStore::buyCart(string username){
 
  if (userProfile.find(username) == userProfile.end()) {
    // NOT A VALID USER!!!
    cout<< "Invalid username" << endl;
  }

  User* currUser = userProfile[username];
  double funds = currUser->getBalance();
  vector<Product *> currUserCart = carts[username];

  vector<Product *> newUserCart;

  for(unsigned int i = 0; i < currUserCart.size(); i++){
    Product *p = currUserCart[i];

    if (!(p->getQty())) {
      newUserCart.push_back(p);
      continue;
    }
    if (funds < p->getPrice()) {
      newUserCart.push_back(p);
      continue;
    }

    p->subtractQty(1);
    currUser->deductAmount(p->getPrice());
    funds = currUser->getBalance();
  }  

  carts[username] = newUserCart;
}

