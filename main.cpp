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
        take_input();
    }
    else if(choice == 2){
        create_matrix();
    }
    else{
        cout<<"Wrong input"<<endl;
        linear_algebra_calculation();
    }
}

/*void etline(string str)
{
    cout<<"start:";
    char single_character;
int i=0;
    while(single_character != 13){
        cin>>single_character;
        cout<<(int)single_character<<" "<<single_character<<" ";

        if(single_character == 13){
                cout<<"in enter ";
            str[i] = '\n';
            break;
        }
        else{
            cout<<"in not";
            str[i] = single_character;
        }
        cout<<"sakkib"<<endl;
        i++;
    }
}*/

int main()
{
    freopen("input_file.txt","r",stdin);
    //freopen("C:\\Users\\HP\\Desktop\\input_SPL.txt","r",stdin);
    linear_algebra_calculation();
    return 0;
}
