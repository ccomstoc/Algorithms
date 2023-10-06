//-----Node.cpp-----
#include "Node.h"

int Node::maxProfit = 0;

Node::Node(){

  level = 0;
  profit = 0;
  weight = 0;
  bound = 0;

}

Node::Node(int l,int p, int w, int b){

  level = l;
  profit = p;
  weight = w;
  bound = b;

  if(profit>maxProfit)
    maxProfit = profit;

}
Node::Node(int l,int p, int w, int b, bool isLeft, std::vector<bool> s){

  level = l;
  profit = p;
  weight = w;
  bound = b;

  if(profit>maxProfit)
    maxProfit = profit;

  //This feels terrible but its happening
  solution = s;
  solution.push_back(isLeft);


}

void Node::print(){

  std::cout << "-Node-\nProfit: " << profit << "\nWeight: " << weight << "\nBound: " << bound << std::endl;
  if(solution.size() != 0){
  std::cout << "Solution: [";
  for(int i = 0; i < solution.size(); i++){
      std::cout << solution.at(i);
      if(i != solution.size()-1)
        std::cout << ",";
  }
  std::cout << "]"<<std::endl;
}


}
