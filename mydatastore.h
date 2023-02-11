#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"
#include "datastore.h"
#include "user.h"
#include "product_parser.h"
using namespace std;
class MyDataStore : public DataStore{
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    vector<User*> getUsers();
    vector<Product*> getProducts();
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
private:
    vector<Product*> gouwuche;
    vector<User*> yonghu;
};
MyDataStore::MyDataStore()
{
}
MyDataStore::~MyDataStore()
{
  for(int i=0;i<int(gouwuche.size());i++)
  {
    delete gouwuche[i];
  }
  for(int i=0;i<int(yonghu.size());i++)
  {
    delete yonghu[i];
  }
}
void MyDataStore::addProduct(Product* p)
{
  gouwuche.push_back(p);
}

void MyDataStore::addUser(User* u)
{
  yonghu.push_back(u);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  vector<Product*> result;
  std::set<Product*> GenResults;
  //cout<<"进入search  "<<type<<endl;
  for(std::string it:terms)
  {
    std::set<Product*> results;//每一个term的result
    for(Product* it2:gouwuche)//每一个product
    {
      for(std::string it3:it2->keywords())//每一个product的每一个关键词
      {
        if(it3==it)//如果有关键词
        {
          results.insert(it2);//保存在results里面
        }
      }
    }
    if(type == 0)
    {
      if(it==terms[0])
      GenResults = results;
      GenResults = setIntersection(GenResults,results);
    }
    if(type == 1)
    {
      GenResults = setUnion(GenResults,results);
    }
  }
  for(Product* it4:GenResults)
  {
    result.push_back(it4);
  }
  return result;
}
vector<User*> MyDataStore::getUsers()
{
  return yonghu;
}
vector<Product*> MyDataStore::getProducts()
{
  return gouwuche;
}
void MyDataStore::dump(std::ostream& ofile)
{
  ofile<<"<products>"<<endl;
  for(Product* itr:gouwuche)
  {
    itr->dump(ofile);
  }
  ofile<<"</products>"<<endl;
  ofile<<"<users>"<<endl;
  for(User* itr2:yonghu)
  {
    itr2->dump(ofile);
  }
  ofile<<"</users>"<<endl;
}

