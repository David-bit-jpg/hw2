#include <sstream>
#include <iomanip>
#include "book.h"
#include "product.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string Author):Product(category, name, price, qty)
{
  ISBN_ = ISBN;
  Author_ = Author;
  keywords_ = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(Author_);
  keywords_.insert(ISBN_);
  for(string it: authorWords)
  keywords_.insert(it);
}
Book::~Book()
{
  
}
set<std::string> Book::keywords() const
{
  return keywords_;
}
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
   return false;
}
std::string Book::displayString() const
{
  return name_+"\n"+"Author: "+Author_+" ISBN: "+ISBN_+"\n"+to_string(price_)+" "+to_string(qty_)+" left.";
}
void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<ISBN_<<"\n" <<Author_<< endl;
}
std::string Book::getISBN() const
{
  return ISBN_;
}
std::string Book::getAuthor() const
{
  return Author_;
}
void Book::setHit(int i)
{
  hit_number = i;
}
int Book::getHit() const
{
  return hit_number;
}