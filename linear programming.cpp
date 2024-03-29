#include<bits/stdc++.h>
#include "linker.h"
using namespace std;

#define SIZE 20
#define LESS_THAN 1
#define GRATER_THAN 2
#define EQUAL 0


int trace[SIZE],number_of_equation, number_of_variable;
double matrix_2[SIZE][SIZE]={0},CB_value[SIZE]={0},ratio_value[SIZE],final_value[SIZE];
char vari_name[SIZE][20],basic_variable[SIZE][20];
bool isMax;
string line[SIZE];

void print_table()
{
    cout<<"\n\nHere are table: \n\n";
    cout<<"Objective: ";
    for(int i=0;i<number_of_equation+number_of_variable;i++){
        cout<<matrix_2[number_of_equation][i]<<"\t";
    }
    cout<<"const\t"<<"min ratio\t"<<endl;

    cout<<"CB\tco_Basis\t";
    for(int i=0;i<number_of_equation+number_of_variable;i++){
        cout<<vari_name[i]<<"\t";
    }
    cout<<endl;

    for(int i=0;i<number_of_equation;i++){
            cout<<CB_value[i]<<"\t"<<basic_variable[i]<<"\t";
        for(int j=0;j<=number_of_equation+number_of_variable;j++){
            cout<<matrix_2[i][j]<<"\t";
        }
        cout<<ratio_value[i]<<endl;
    }

    cout<<"Zj - Cj :\t";
    for(int j=0;j<=number_of_equation+number_of_variable;j++){
            cout<<final_value[j]<<"\t";
    }

    cout<<"\n\n\n";
}


bool isAllSame()
{

    for(int i=0;i<=number_of_equation+number_of_equation;i++){
        if(isMax){
            if(final_value[i]<0){
                return false;
            }
        }
        else{
            if(final_value[i]>0){
                return false;
            }
        }

    }

    return true;
}


void calculate_table()
{
    //print_table();
    for(int i=0;i<=number_of_equation+number_of_variable;i++){
        final_value[i] = 0;
        for(int j=0;j<number_of_equation;j++){
            final_value[i] += (CB_value[j]*matrix_2[j][i]);
        }

        final_value[i] = ( final_value[i] - matrix_2[number_of_equation][i]);
    }
    //print_table();
}



void organize_table()
{
    double row[SIZE], column[SIZE];         //FOR SAVE KEY ROW AND KEY COLUMN

    int key_row=0, key_col=0;
    double key= final_value[0];

    for(int i=1;i<=number_of_equation+number_of_equation;i++){
            if(final_value[i]<key && isMax){
                key = final_value[i];
                key_col = i;
            }
            else if(final_value[i]>key && !isMax){
                key = final_value[i];
                key_col = i;
            }
    }

    key = INT_MAX;

    for(int i=0;i<number_of_equation;i++){
        ratio_value[i] = matrix_2[i][number_of_equation+number_of_variable]/matrix_2[i][key_col];
        if(key>ratio_value[i]){
            key = ratio_value[i];
            key_row = i;
        }
    }

    //cout<<"key row: "<<key_row<<" "<<key_col<<endl;

    strcpy(basic_variable[key_row],vari_name[key_col]);
    CB_value[key_row] = matrix_2[number_of_equation][key_col];


    key = matrix_2[key_row][key_col];               //save key value
    //cout<<"key: "<<key<<endl;

    for(int i=0;i<=number_of_equation+number_of_variable;i++){
        row[i] = matrix_2[key_row][i];
        //cout<<row[i]<<"\t";
    }


    for(int i=0;i<=number_of_equation+number_of_variable;i++){
        column[i] = matrix_2[i][key_col];
        //cout<<column[i]<<"\t";
    }

    for(int i=0;i<=number_of_equation+number_of_variable;i++){
        matrix_2[key_row][i] = matrix_2[key_row][i]/key;
    }

    //save key and col key for further calculation
    for(int j=0;j<number_of_equation;j++){
        for(int i=0;i<=number_of_equation+number_of_variable;i++){
            if(j == key_row){
                continue;
            }

            matrix_2[j][i] -= ((row[i] * column[j])/key);
        }
    }


   calculate_table();

}





void print_value()
{
    cout<<"\n\n\n";
    int j;
    for(int i=0;i<number_of_variable;i++){
        for(j=0;j<number_of_equation;j++){
            if(strcmp(basic_variable[j],vari_name[i]) == 0){
                cout<<vari_name[i]<<": "<<matrix_2[j][number_of_equation+number_of_variable]<<endl;
                break;
            }
        }
        if(j == number_of_equation){
            cout<<vari_name[i]<<": 0"<<endl;
        }
    }

    if(isMax){
        cout<<"\nMaximum value is "<<final_value[number_of_equation+number_of_variable]<<endl;
    }
    else{
        cout<<"\nMinimum value is "<<abs(final_value[number_of_equation+number_of_variable])<<endl;
    }


}



void check_critical_value()
{
    calculate_table();

    if(isAllSame()){
        print_value();
    }
    else{
            int i=0;
        do{
            organize_table();
    i++;
        }while(!isAllSame() && i<15);

        print_value();
    }
}


void make_standard_form()
{
    for(int i=0;i<number_of_equation;i++){
        if(trace[i] == GRATER_THAN){
            for(int k=0;k<=number_of_equation+number_of_variable;k++){
                matrix_2[i][k] *= -1;
            }
        }
    }

    if(!isMax){
        for(int i=0;i<number_of_equation;i++){
            matrix_2[number_of_equation][i] *= -1;
        }
    }
}


void add_slug_variable()
{
    for(int i=0;i<number_of_equation;i++){
        double temp = matrix_2[i][number_of_variable];
        for(int j=0;j<number_of_equation;j++){
                if(i==j){
                    if(trace[i] == LESS_THAN){

                        matrix_2[i][number_of_variable+j] = 1;
                    }
                    else if(trace[i] == GRATER_THAN){
                        matrix_2[i][number_of_variable+j] = -1;
                    }
                }
                else{
                    matrix_2[i][number_of_variable+j] = 0;
                }

        }

        temp *= -1;
        matrix_2[i][number_of_equation+number_of_variable] = temp;
    }

    make_standard_form();
}



void create_table()
{
    char temp[SIZE];
    add_slug_variable();


    for(int i=number_of_variable;i<number_of_equation+number_of_variable;i++){
        temp[0] = 's';
        temp[1] = (i-number_of_variable) + '0';
        temp[2] = '\0';

        strcpy(vari_name[i],temp);
        strcpy(basic_variable[i-number_of_variable],temp);

    }

    for(int i=0;i<number_of_equation;i++){
        matrix_2[i][number_of_equation+number_of_variable] *= -1;
    }

    check_critical_value();
}





//from above simplex method added

void remove_less_grater_sign(string &str, int index)
{

    if(str[index+1] != '=' )
    {
        str[index] = '=';
        return;
    }

	while(str[index]){
		str[index] = str[index+1];
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
    cout<<"\n\n\t\t WELLCOME TO LINEAR PROGRAMMING SOLVER\n\n\n\n\n";



    string str[SIZE];
    int choice;

    cout<<"1. max value\n 2.min value"<<endl;
    cin>>choice;
    getchar();
    if(choice == 1){
        isMax = true;
    }
    else{
        isMax = false;
    }

    cout<<"Input number of line: ";
    cin>>number_of_equation;
    getchar();

    cout<<"Input line one by one\n ";
    for(int i=0;i<number_of_equation;i++){
        getline(cin,str[i]);

        convert_to_equation(str[i], i);
    }

    cout<<"Enter objective equation: ";
    getline(cin,str[number_of_equation]);

    convert_to_equation(str[number_of_equation], number_of_equation);

    number_of_variable = solve_linear_programming(str,matrix_2,vari_name, number_of_equation+1);

    create_table();

}
