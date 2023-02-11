#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "product.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string Size1, const std::string Brand):Product(category, name, price, qty)
{
  Size_ = Size1;
  Brand_ = Brand;
  keywords_ = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(Brand_);
  keywords_.insert(Size_);
  for(string it: brandWords)
  keywords_.insert(it);
}
Clothing::~Clothing()
{
}
set<std::string> Clothing::keywords() const
{
  return keywords_;
}
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
   return false;
}
std::string Clothing::displayString() const
{
  return name_+"\n"+"Size: "+Size_+" Brand: "+Brand_+"\n"+to_string(price_)+" "+to_string(qty_)+" left.";
}
void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<Size_<<"\n" <<Brand_<< endl;
}
std::string Clothing::getSize() const
{
  return Size_;
}
std::string Clothing::getBrand() const
{
  return Brand_;
}
void Clothing::setHit(int i)
{
  hit_number = i;
}
int Clothing::getHit() const
{
  return hit_number;
}