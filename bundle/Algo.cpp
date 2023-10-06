//-----Algo.cpp-----
#include "Algo.h"

Algo::Algo(int mW){

  maxWeight = mW;
  numOfItems = 0;

  isListSorted = false;
}

void Algo::sort(std::vector<Item> &v){

  //Insertion sort because simplicity and lists are small
  Item temp;
  for(int i = v.size()-1; i >= 1; i--)
    for(int n = i; n < v.size()-1; n++){
      if(v.at(n).vpw > v.at(n-1).vpw){
        //swap
        temp = v.at(n);
        v.at(n) = v.at(n-1);
        v.at(n-1) = temp;
      }
      else
        break;
    }
    isListSorted = true;
}

void Algo::add(Item i){

  numOfItems++;
  itemlist.push_back(i);
  isListSorted = false;

}

void Algo::printItems(std::vector<Item> v){

  for(int i = 0; i < v.size(); i++){
    std::cout << "id: " <<v.at(i).id << " vpw: " <<v.at(i).vpw << "\n";
  }
}

void Algo::greedy(){//Bassed on p/w ratio


  std::cout<< "-----Greedy-----\n";

  int totalValue = 0;
  std::vector<Item> solutionList;
  int currentWeight = 0;

  //avoid redundent sorting
  if(!isListSorted){
    sort(itemlist);
    isListSorted = true;
  }
  //add all items(in order of greatest v/p first), that do not cause weight to exceed
  for(int i = 0; i<itemlist.size(); i++){
    if((currentWeight+itemlist.at(i).weight) <= maxWeight){
      solutionList.push_back(itemlist.at(i));
      currentWeight+=itemlist.at(i).weight;
      totalValue += itemlist.at(i).value;
    }
  }
  printItems(solutionList);

  std::cout << "Total value: " << totalValue << std::endl;
}

int Algo::fractionalGreedy(){

  std::vector<Item> solutionList;
  int i = 0;
  int totalValue = 0;
  int currentWeight = 0;

  //avoid redundent sorting
  if(!isListSorted){
    sort(itemlist);
    isListSorted = true;
  }
    // find items until the item that will exceed weight
    while((currentWeight+itemlist.at(i).weight) <= maxWeight){
      solutionList.push_back(itemlist.at(i));
      currentWeight+=itemlist.at(i).weight;
      totalValue += solutionList.at(i).value;
      i++;
    }
    int remainingW = maxWeight-currentWeight;

    //I use fractional greedy to compute bound for aother algorithms, so I dont print here

    //Add fraction of item whos weight is to large
    totalValue += remainingW * itemlist.at(i).vpw;

    return totalValue;
}

void Algo::zeroOneDynamic(){
std::cout<< "-----Zero-One-DP-----\n";
  //Create dynamic 2d array to store DP values
  int ** dpArray = new int*[numOfItems+1];
  for(int i = 0; i<= numOfItems+1; i++){
    dpArray[i] = new int[maxWeight];
  }
  std::cout << "Best possible value: "<< zeroOneDPHelper(numOfItems,maxWeight,dpArray) << std::endl;

  delete [] dpArray;
}
int Algo::zeroOneDPHelper(int n, int w, int **&dpArr){

  if(n == 0 || w == 0)
    return 0;
  else if(n < 0  || w < 0)
    return -1;
  else if( dpArr[n][w] == '\0'){//Not yet defined, so define it
    int firstHalf = zeroOneDPHelper(n-1,w,dpArr);//First part DP max funtion
    int secondHalf;

    if(firstHalf < 0)
      std::cout << "warning, first half < 0\n";//Not acounted for

      if((w-(itemlist.at(n-1).weight))<0)//Undefined, always let max pick other value
        secondHalf = -1;
      else
        secondHalf = (itemlist.at(n-1).value)+zeroOneDPHelper(n-1,w-(itemlist.at(n-1).weight),dpArr);

    dpArr[n][w] = std::max(firstHalf,secondHalf);

  }
  else{//Value has already been calculated and is in dpArray

    return dpArr[n][w];
  }
return 0;
}

void Algo::zeroOneBacktrack(){

  std::cout <<"-----Backtrack-Knapsack-----\n";

  int bound = fractionalGreedy();
  Node root(0,0,0,bound);
  Node maxN(0,0,0,0);

  traverse(root,maxN);

  maxN.print();

}

bool Algo::traverse(Node node, Node &maxNode){//is bool from earlier technique of printing solution

  if(node.profit >= maxNode.profit){
    maxNode = node;
  }

  if(node.level <= numOfItems-1){

    int promisingLeftBound = promising(node, true);
    if(promisingLeftBound != -1){
    Node leftNode(node.level+1, node.profit+itemlist.at(node.level).value, node.weight+itemlist.at(node.level).weight,promisingLeftBound,true,node.solution);
    traverse(leftNode, maxNode);
    }
    int promisingRightBound = promising(node, false);
    if(promisingRightBound != -1){
    Node rightNode(node.level+1, node.profit,node.weight,promisingRightBound,false,node.solution);// level is always one ahead of itemlist index
    traverse(rightNode,maxNode);
    }
  }
  return true;//again from earlier solution print, not used
}

int Algo::promising(Node node, bool isLeft){//returns bound if promising, else returns null

  int bound;

  if(isLeft){
    //bound will be same as parrents
    if(node.bound >= node.maxProfit && (node.weight + itemlist.at(node.level).weight) <= maxWeight)
      return node.bound;
    else
      return -1;
  }
  else{//Right Node
    int remaningProfit = 0;
    int remainingWeight;
    int currentWeight = node.weight;
    int i = node.level+2-1;//+2 is grandchild -1 for index
    //bound calc
    while(i < itemlist.size() && currentWeight+itemlist.at(i).weight <= maxWeight){
      currentWeight+=itemlist.at(i).weight;               //this node but since we are right child
      remaningProfit+=itemlist.at(i).value;
      i++;
      }
      if(currentWeight < maxWeight && i != itemlist.size()){
        remainingWeight = maxWeight-currentWeight;
        remaningProfit += remainingWeight*itemlist.at(i).vpw;
      }
    bound = node.profit + remaningProfit;

  if(bound > node.maxProfit)
    return bound;
  else
    return -1;
    }
}

void Algo::knapsackBestFirst(){

  std::cout << "-----Branch-&-Bound-Best-First-Knapsack-----\n";
  Node maxP;

  knapsackBestFirstHelper(maxP);

  maxP.print();

}

void Algo::knapsackBestFirstHelper(Node &maxP){
  int bound = fractionalGreedy();
  Node root(0,0,0,bound);
  Node parent;
  pQadd(root);

  while(pQue.size() != 0){
  parent = pQremove();

    if(parent.bound > maxP.profit){//Check again if bound is still good

      //FindLeft
      int promisingLeftBound = promising(parent, true);
      if(promisingLeftBound != -1){
        Node leftNode(parent.level+1, parent.profit+itemlist.at(parent.level).value, parent.weight+itemlist.at(parent.level).weight,promisingLeftBound,true,parent.solution);
        if(leftNode.profit > maxP.profit){//Probably could move to beginig of loop but just to keep updated
          maxP = leftNode;
          maxP.maxProfit = leftNode.profit;//Yes its redundant but, but wrote promising with satic maxprofit
        }
        pQadd(leftNode);
      }
      //FindRight
      int promisingRightBound = promising(parent, false);
      if(promisingRightBound != -1){
        Node rightNode(parent.level+1, parent.profit,parent.weight,promisingRightBound,false,parent.solution);
        if(rightNode.profit > maxP.profit){
          maxP = rightNode;
          maxP.maxProfit = rightNode.profit;
        }
        pQadd(rightNode);
      }
    }

  }

}

void Algo::pQadd(Node node){

  int track = 0;
  if(pQue.size()== 0)
    pQue.insert(pQue.begin(), node);
  else{
    while(track < pQue.size()&&pQue.at(track).bound < node.bound)//count until the next value is smallerthan current
      track++;
    if(track != pQue.size())
      pQue.insert(pQue.begin() + track, node);
    else
      pQue.push_back(node);
    }
}
Node Algo::pQremove(){

  Node node = pQue.at(0);
  pQue.erase(pQue.begin());
  return node;
}
