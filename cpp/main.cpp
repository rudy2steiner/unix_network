//
// Created by root on 18-10-2.
//

#include <iostream>
#include "stock00.h"

/**
 *  g++ -std=c++11 main.cpp Stock00.cpp -o main
 *
 **/

void string_init(std::string *v);

void change(Stock stock);
int main(){

  using std::cout;
  using  std::endl;
    // c++ init way
  int a(10);
  double  d(0.4);
  float  f(0.66);
  std::string value("sgfsdf ws");
  std::string empty;
  char s='s';
    int len(5);
    char ss[6]{"xxxxx"};
  std::string *v=&value;

    cout<<"v pointer:"<<*v<<endl;
  cout<<ss<<endl;
  std::cout<<"hello c++!"<<endl;
  string_init(&empty);
  std::cout<<empty<<endl;
  std::cout<<value<<endl;
  std::cout<<s<<endl;
  cout<<a<<","<<d<<","<<f<<endl;

 Stock fluffy_the_cat;
       fluffy_the_cat.acquire("NanoSmart",20,12.50);
       fluffy_the_cat.show();
       fluffy_the_cat.buy(15,18.125);
       fluffy_the_cat.show();

 Stock food=Stock("World Cabbage",50,2.5);
       food.show();
    change(food);
       food.show();
// Stock st=new Stock("a stock",45,90.06);
//       st.show();

    Stock *sto=new Stock("a stock two",45,90.06);
    (*sto).show();
    Stock bigger=fluffy_the_cat.topval(food);
    cout<<"bigger:";
    bigger.show();
}

void change(Stock stock){
    std::cout<<"change\n";
    stock.sell(10,10.5);
}

void string_init(std::string *value){
    *value={"absed"};

}