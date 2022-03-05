#include <bits/stdc++.h>
#include "linker.h"

using namespace std;

void linear_algebra_calculation()           //add infinite many solution
{
    int choice;

    cout<<"1. Input equation\n 2.Input coefficient of equation"<<endl;
    cout<<"Input your choice: ";
    cin>>choice;

    if(choice == 1){
        solve_linear_equation();
    }
    else if(choice == 2){
        create_matrix();
    }
    else{
        cout<<"Wrong input"<<endl;
        linear_algebra_calculation();
    }
}



int main()
{
    freopen("input_file.txt","r",stdin);
    input_linear_programming();

    //freopen("C:\\Users\\HP\\Desktop\\input_SPL.txt","r",stdin);
    //linear_algebra_calculation();
    return 0;
}
