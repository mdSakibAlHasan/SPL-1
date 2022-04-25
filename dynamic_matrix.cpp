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

  /*cout << "Enter " << (row * col) << " numbers to the Array\n";
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      cout << "Enter the elements at Row " << i + 1 << " Column " << j + 1 << endl;
      cin >> arry[i][j];
    }
  }

  cout << "Here is your 2D Array:" << endl;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      cout << arry[i][j] << ' ';
    }
    cout << endl;
  }
  //Free the memory after the use of array
  for (i = 0; i < row; i++) {
    delete[] arry[i];
  }
  delete[] arry;*/

  cout<<"Enter row and column :";
  cin>>a>>b;

  cin>>arry[a][b];

  cout<<"Array here: ";
  cout<<arry[a][b]<<endl;

  return 0;

}
