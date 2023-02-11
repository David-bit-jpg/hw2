#include <sstream>
#include <iomanip>
#include "movie.h"
#include "product.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string Genre, const std::string Rating):Product(category, name, price, qty)
{
  Genre_ = Genre;
  Rating_ = Rating;
  keywords_ = parseStringToWords(name_);
  std::set<std::string> genreWords = parseStringToWords(Genre_);
  keywords_.insert(Rating_);
  for(string it: genreWords)
  keywords_.insert(it);
}
Movie::~Movie()
{
}
set<std::string> Movie::keywords() const
{
  return keywords_;
}
bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
   return false;
}
std::string Movie::displayString() const
{
  return name_+"\n"+"Genre: "+Genre_+" Rating: "+Rating_+"\n"+to_string(price_)+" "+to_string(qty_)+" left.";
}
void Movie::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" <<Genre_<<"\n" <<Rating_<< endl;
}
std::string Movie::getGenre() const
{
  return Genre_;
}
std::string Movie::getRating() const
{
  return Rating_;
}
void Movie::setHit(int i)
{
  hit_number = i;
}
int Movie::getHit() const
{
  return hit_number;
}