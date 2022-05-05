#include<bits/stdc++.h>
using namespace std;
#include "linker.h"

int large_size_matrix()
{

     int ** arry;
  int row, col, i, j,a,b;
  cout << "Number of Rows:" << endl;
  cin >> row;
  cout << "Number of Columns:" << endl;
  cin >> col;

  arry = new int * [row];

  for (i = 0; i < row; i++) {
    arry[i] = new int[col];
  }


  cout<<"Enter row and column :";
  cin>>a>>b;

  cin>>arry[a][b];

  cout<<"Array here: ";
  cout<<arry[a][b]<<endl;

  return 0;

}
