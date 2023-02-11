#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"
class Clothing : public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string Size1, const std::string Brand);
    std::set<std::string> keywords() const;
    ~Clothing();
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    std::string getSize() const;
    std::string getBrand() const;
    void setHit(int i);
    int getHit() const;
private:
    std::string Size_;
    std::string Brand_;
    std::set<std::string> keywords_;
};
