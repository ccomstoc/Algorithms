//-----driver.cpp-----
#include <iostream>
#include "Item.h"
#include "Algo.h"


int main(){

//-----Creates Algo objects which contains items and alogrithms, constuctor takes W
Algo a(16);
Algo b(30);
Algo c(16);

Algo d(13);
Algo e(9);


//-----Create items for algo object to use
Item a1(2,40);
Item a2(5,30);
Item a3(10,50);
Item a4(5,10);

Item b1(5,50);
Item b2(20,140);
Item b3(10,60);

Item c1(3,45);
Item c2(5,30);
Item c3(9,45);
Item c4(5,10);


//Excercise 5 Branch and bound
Item d1(2,20);
Item d2(5,30);
Item d3(7,35);
Item d4(3,12);
Item d5(1,3);

//Excercise 5 Backtracking
Item e1(2,20);
Item e2(5,30);
Item e3(7,35);
Item e4(3,12);
Item e5(1,3);

//Add items to algo obj
a.add(a1);
a.add(a2);
a.add(a3);
a.add(a4);

b.add(b1);
b.add(b2);
b.add(b3);

c.add(c1);
c.add(c2);
c.add(c3);
c.add(c4);

d.add(d1);
d.add(d2);
d.add(d3);
d.add(d4);
d.add(d5);

e.add(e1);
e.add(e2);
e.add(e3);
e.add(e4);
e.add(e5);

//---Run alogrithms

a.greedy();
std::cout<< "-----FractionalGreedy-----\n";
std::cout << "Total value: " << a.fractionalGreedy() << std::endl;


e.zeroOneDynamic();
e.zeroOneBacktrack();
e.knapsackBestFirst();

d.zeroOneDynamic();
d.zeroOneBacktrack();
d.knapsackBestFirst();


  return 0;
}
