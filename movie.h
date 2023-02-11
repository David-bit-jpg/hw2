#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"
class Movie : public Product{
public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string Genre, const std::string Rating);
    ~Movie();
    std::set<std::string> keywords() const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
    std::string getGenre() const;
    std::string getRating() const;
    void setHit(int i);
    int getHit() const;
private:
    std::string Genre_;
    std::string Rating_;
    std::set<std::string> keywords_;
};
