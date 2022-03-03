#include<bits/stdc++.h>
#include "linker.h"
using namespace std;

#define SIZE 20
#define LESS_THAN 1
#define GRATER_THAN 2
#define EQUAL 0


int trace[SIZE],number_of_equation, number_of_variable;
double matrix[SIZE][SIZE];
char vari_name[SIZE][20];


void remove_less_grater_sign(string &str, int index)
{
	while(str[index]){
		str[index] = str[index-1];
		index++;
	}
}


void convert_to_equation(string &str, int equation_index_number)
{
	int i=0;

	while(str[i]){
		if(str[i] == '<'){
			trace[equation_index_number] = LESS_THAN;
			remove_less_grater_sign(str, i);
			return;
		}
		else if(str[i] == '>'){
			trace[equation_index_number] = GRATER_THAN;
			remove_less_grater_sign(str, i);
			return;
		}
		i++;
	}

	trace[equation_index_number] = EQUAL;

}


void write_equation_in_file(string str[])
{
    ofstream myfile;
    myfile.open("new.txt");
    myfile<<number_of_equation<<endl;

    for(int i=0;i<number_of_equation;i++){
        myfile<<str[i]<<endl;
    }

    myfile.close();
}


void input_linear_programming()
{
    string str[SIZE];

    cout<<"Input number of line: ";
    cin>>number_of_equation;

    cout<<"Input line one by one\n ";
    for(int i=0;i<number_of_equation;i++){
        getline(cin,str[i]);

        convert_to_equation(str[i], i);
    }


    write_equation_in_file(str);

    solve_linear_programming();

    for(int i=0;i<=number_of_variable;i++){
        for(int j=0;j<number_of_variable;j++){
            cout<<matrix[i][j]<<"  ";
        }

        cout<<endl;
    }

    for(int i=0;i<=number_of_variable;i++){
        cout<<"vari = "<<vari_name<<endl;
    }

}

