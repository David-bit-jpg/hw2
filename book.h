#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"
class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string Author);
    ~Book();
    std::set<std::string> keywords() const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    std::string getISBN() const;
    std::string getAuthor() const;
    void setHit(int i);
    int getHit() const;
private:
    std::string ISBN_;
    std::string Author_;
    std::set<std::string> keywords_;
};
