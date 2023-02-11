#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"
#include "user.h"
#include "product_parser.h"
using namespace std;
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type);
    ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    vector<Product*> ToGouwuche();
    void add_cart(Product* i);
    void dump(std::ostream& os);
    void removeGowuche(int cnt);
private:
    std::string name_;
    double balance_;
    int type_;
    vector<Product*> gouwuche;
};
#endif
