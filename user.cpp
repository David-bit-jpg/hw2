#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{
  // for(int i=0;i<int(gouwuche.size());i++)
  // delete gouwuche[i];
}

vector<Product*> User::ToGouwuche ()
{
    return gouwuche;
}
std::string User::getName() const
{
    return name_;
}
void User::add_cart(Product* i)
{
   gouwuche.push_back(i);
}
double User::getBalance() const
{
    return balance_;
}
void User::removeGowuche(int cnt)
{
  gouwuche.erase(gouwuche.begin()+cnt);
}
void User::deductAmount(double amt)
{
    balance_ -= amt;
}
void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}
