#include <bits/stdc++.h>
#include "linker.h"


using namespace std;

void linear_algebra_calculation()           //add infinite many solution
{
    cout<<"\n\n\n WELCOME TO EQUATON SOLVER\n\n\n";
    int choice;
    cout<<"\t\t1.Linear algebra\n\t\t2.Linear programming\n\n..........";
    cin>>choice;

    if(choice == 1){
        cout<<"\n\n\n\n\t\t1. Input equation\n\t\t 2.Input coefficient of equation\n.........."<<endl;

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
    else if(choice == 2){
        input_linear_programming();
    }


}



int main()
{
    freopen("input.txt","r",stdin);


    //freopen("C:\\Users\\HP\\Desktop\\input_SPL.txt","r",stdin);
    //linear_algebra_calculation();

    input_controller();
    return 0;
}
