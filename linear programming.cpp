#include<bits/stdc++.h>
#include "linker.h"
using namespace std;

#define SIZE 20
#define LESS_THAN 1
#define GRATER_THAN 2
#define EQUAL 0


int trace[SIZE],number_of_equation;
double matrix[SIZE][SIZE];


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


void input_linear_programming()
{
    string str[SIZE];

    cout<<"Input number of line: ";
    cin>>number_of_equation;

    cout<<"Input line one by one\n ";
    for(int i=0;i<number_of_equation;i++){
        getline(cin,str[i]);
        convert_to_equation(str[i], i);
	//CALL TO EXTRACT VARIABLE AND MODIFY THIS FUNCTION
    }

}
