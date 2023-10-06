//-----Node.h-----
#include <iostream>
#include <vector>

#ifndef NODE_H
#define NODE_H

class Node{

  public:

    static int maxProfit;
    std::vector<bool> solution;


    int bound;
    int profit;
    int weight;
    int level;

    Node();
    Node(int l,int p, int w, int b);
    Node(int l,int p, int w, int b, bool isLeft, std::vector<bool> s );
    void print();





};

#endif
