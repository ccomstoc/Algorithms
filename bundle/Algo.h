//-----Algo.h----
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "Item.h"
#include "Node.h"

#ifndef ALGO_H
#define ALGO_H


class Algo{

  public:

    std::vector<Item> itemlist;
    int numOfItems;
    std::vector<Node> pQue;



    Algo(int mW);

    void add(Item i);

    void greedy();//Bassed on p/w ratio

    int fractionalGreedy();

    void zeroOneDynamic();

    void zeroOneBacktrack();

    void knapsackBestFirst();






    //
  private:
    bool isListSorted; //Keeps track if the list is sorted or not
    int maxWeight;// maximum weight for knapsack problem
    void printItems(std::vector<Item> v);
    void sort(std::vector<Item> &v);
    int zeroOneDPHelper(int n, int w, int **&dpArr);
    int promising(Node node, bool isLeft);
    bool traverse(Node node, Node &maxNode);

    float bookBound(Node node);
    void knapsackBestFirstHelper(Node &maxP);

    void pQadd(Node node);
    Node pQremove();





};

#endif
