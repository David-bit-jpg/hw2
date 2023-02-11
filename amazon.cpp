#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "datastore.h"
#include "user.h"
using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;
    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }
    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        ss.clear();
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") 
            {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) 
            {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") 
            {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if (cmd == "ADD")
            {
              string username;
              //cout<<"进入ADD"<<endl;
              int search_hit_number;
              bool is_valid = false;
              if(ss>>username>>search_hit_number)
              {
                //cout<<"进入ADD2"<<endl;
                for(User* it : ds.getUsers())
                {
                 // cout<<"进入ADD3"<<endl;
                  if(it->getName() == username)
                  {
                   // cout<<"进入ADD4"<<endl;
                    it->add_cart(hits[search_hit_number-1]);
                  //  cout<<"到这里了"<<endl;
                    is_valid = true;
                  }
                }
                if(is_valid==false) cout<<"Invalid request"<<endl;
              }
              else
              {
                cout<<"Invalid request"<<endl;
              }

            }
            else if (cmd == "VIEWCART")
            {
              string username;
             // cout<<"进入VIEW"<<endl;
              bool is_valid = false;
              int cnt=1;
              if(ss>>username)
              {
               // cout<<"进入VIEW2"<<endl;
                for(User* it : ds.getUsers())
                {
                 // cout<<"进入VIEW3"<<endl;
                  if(it->getName()==username)
                  {
                   // cout<<"进入VIEW4"<<endl;
                    is_valid = true;
                    for(Product* it2 : it->ToGouwuche())
                    {
                      cout<<"Item "<<cnt<<endl;
                      cout<<it2->displayString()<<endl;
                      cnt++;
                    }
                  }
                }
                if(is_valid==false) cout<<"Invalid username"<<endl;
              }
              else
              {
                cout<<"Invalid username"<<endl;
              }
            }
            else if(cmd == "BUYCART")
            {
              string username;
              //cout<<"进入BUY"<<endl;
              bool is_valid = false;
              int cnt2=0;
              if(ss>>username)
              {
                //cout<<"进入BUY"<<endl;
                for(User* it : ds.getUsers())
                {
                  if(it->getName()==username)
                  {
                    is_valid = true;
                    for(Product* it2 : it->ToGouwuche())
                    {
                      if(it2->getQty()>0&&(it->getBalance())>=(it2->getPrice()))
                      {
                        it->deductAmount(it2->getPrice());
                        it2->subtractQty(1);
                        it->ToGouwuche()[cnt2]=NULL;
                        it->removeGowuche(cnt2);
                        cnt2--;
                      }
                      cnt2++;
                    }
                  }
                }
                if(is_valid==false) cout<<"Invalid username"<<endl;
              }
              else
              {
                cout<<"Invalid username"<<endl;
              }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
   // delete userSectionParser;
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        //it->setHit(resultNo);
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
