#include <bits/stdc++.h>
#include "linker.h"
using namespace std;

void linear_algebra_calculation()           //add infinite many solution
{

        cout<<"\n\n\n\t\t\t\t WELCOME TO EQUATON SOLVER\n\n\n";
        int choice;
        cout<<"\t\t1.Linear algebra\n\t\t2.Linear programming\n\t\t3.Polynomial equation\n\t\t4.Exit\n\n..........";
        cin>>choice;
        //getchar();
        if(choice == 1){
            cout<<"\n\n\n\n\t\t1. Input equation\n\t\t 2.Input coefficient of equation\n.........."<<endl;
            //getchar();
            cin>>choice;

            if(choice == 1){
                solve_linear_equation();
            }
            else if(choice == 2){
                create_solution();
            }
            else{
                cout<<"Wrong input"<<endl;
            }
        }
        else if(choice == 2){
            input_linear_programming();
        }
        else if(choice == 3){
            input_controller();
        }
        else if(choice == 4){
            return;
        }
        else{
            cout<<"Wrong input"<<endl;
        }

        return;

}



int main()
{
    //freopen("in.txt","r",stdin);

    while(1){
        linear_algebra_calculation();
    }

    //input_linear_programming();

    return 0;
}
