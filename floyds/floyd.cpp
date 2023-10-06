//Connor Comstock
#include <iostream>

using namespace std;

class Floyd{

public:
  void printArray(int arr[8][7][7], int dNum);

};

int main()
{

Floyd f;

int master[8][7][7] = {{{0,4,-1,-1,-1,10,-1},{3,0,-1,18,-1,-1,-1},{-1,6,0,-1,-1,-1,-1},{-1,5,15,0,2,19,5},{-1,-1,12,1,0,-1,-1},{-1,-1,-1,-1,-1,0,10},{-1,-1,-1,8,-1,-1,0}},{0},{0},{0},{0},{0},{0},{0}};

int p[7][7] = {0};

//key[d#][row][col]

cout << "-------D" << 0 << "-------\n";
f.printArray(master, 0);

for(int dNum = 1; dNum <= 7; dNum++){


  for(int c = 0; c < 7; c++)//set row to prevoious dim
    master[dNum][dNum-1][c] = master[dNum-1][dNum-1][c];//first dNum indicates which array, second is -1 bc of indexing
  for(int r = 0; r < 7; r++)//set colum to prevoious dim
    master[dNum][r][dNum-1] = master[dNum-1][r][dNum-1];

    for(int r = 0; r < 7; r++)
      for(int c = 0; c < 7; c++){
        if(r != (dNum-1) && c != (dNum-1) && r != c){ // acount for diagonal = 0 and dNum row/col  unchanged

          //-----Set a&b-----
          int a = master[dNum-1][r][c];

          int b;
          int b1 = master[dNum-1][r][dNum-1];
          int b2 = master[dNum-1][dNum-1][c];

          if( b1 == -1 || b2 == -1) //Simulating -1 as infinity
            b = -1;
          else
            b = b1+b2;


          //----Compare-----
          if(a == -1){//simulating infinity
            master[dNum][r][c] = b;
            p[r][c] = dNum;
          }
          else if(b == -1)//simulating infinity
            master[dNum][r][c] = a;
          else if( a < b)
            master[dNum][r][c] = a;
          else{
            master[dNum][r][c] = b;
            p[r][c] = dNum;
          }

        }
      }

      cout << "-------D" << dNum << "-------\n";
      f.printArray(master, dNum);
}
  // Print P
  cout << "-------P-------\n";
  for(int i = 0; i < 7; i ++){
    for(int j = 0; j < 7; j++)
      cout << p[i][j]<< ", ";
    cout << "\n";
  }

}
void Floyd::printArray(int arr[8][7][7], int dNum)
{
  int num;
  for(int i = 0; i < 7; i ++){
    for(int j = 0; j < 7; j++){
      num = arr[dNum][i][j];//num to print
      if(num < 10 && num != -1)//Formating
        cout << " " << num;
      else
        cout << num;
      cout << " ";
      }
    cout << "\n";
  }

}
