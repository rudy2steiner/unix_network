//
// Created by root on 18-10-2.
//

#ifndef ANSI_C_STOCK00_H
#define ANSI_C_STOCK00_H

#include <string>
class Stock{
private:
    std::string company;
    long shares;
    double  share_val;
    double  total_val;
    void set_tot(){total_val=shares*share_val;}

public:
    Stock(){Stock("");};
    Stock(const std::string name,long n=0,double pr=0.0);
    ~Stock(){std::cout<<"bye "<<company<<"!\n";};
    void acquire(const std::string co,long n,double pr);
    void buy(long num,double price);
    void sell(long num,double price);
    void update(double price);
    void show();

    /**
     * &s alias
     **/
    const Stock & topval(const Stock & s) const;
};

#endif //ANSI_C_STOCK00_H
