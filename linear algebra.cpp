#include<bits/stdc++.h>
#include "linker.h"
#define SIZE 10
using namespace std;

#define SPACE 0
#define OPERATOR 1
#define NUMBER 2
#define CHARACTER 3

int matrix[SIZE][SIZE],temp[SIZE][SIZE];
int determine_of_matrix(int arr[][SIZE], unsigned int number);
char numeric_data[]={'0','1','2','3','4','5','6','7','8','9'},operator_data[]={'+','-','='};
char variable[SIZE][20], store[20];


int make_small_matrix(int arr[][SIZE], unsigned int number, unsigned int replace_number)
{
    /*Here we calculate determine of matrix by reducing size of matrix, until matrix size will be 2.
    When its size will be 2, then it calculate and return value. This function reduce matrix size and
    make a small matrix*/

    int small_matrix[SIZE][SIZE],track=0;
    for(size_t i=1;i<number;i++){
        for(size_t j=0;j<number;j++){
            if(j == replace_number){
                continue;
            }
            else{
                small_matrix[i-1][track++] = arr[i][j];
            }
        }
        track = 0;
    }

    return determine_of_matrix(small_matrix, number-1);
}


int determine_of_matrix(int arr[][SIZE], unsigned int number)
{
    /*This function calculate determine of matrix*/

    if(number == 2){
        return (arr[0][0]*arr[1][1]) - (arr[0][1]*arr[1][0]);
    }
    else{
        int summation=0;
        for(size_t i=0;i<number;i++){
            if(i%2 == 0){
                summation += arr[0][i]*make_small_matrix(arr, number, i);
            }
            else{
                summation -= arr[0][i]*make_small_matrix(arr, number, i);
            }
        }
        return summation;
    }
}


void replace_column(unsigned int x, unsigned int number)
{
    /*To find variable coefficient we need to replace column*/

    for(size_t i=0;i<number;i++){
        for(size_t j=0;j<number;j++){
            if(j == x){
                temp[i][j] = matrix[i][number];
            }
            else{
                temp[i][j] = matrix[i][j];
            }
        }
    }
}



void make_solution(int number_of_variale)
{
    int result[SIZE];
    unsigned int number = (unsigned)number_of_variale;          //make signed int to unsigned int

    result[0] = determine_of_matrix(matrix,number);             // make determine for constant

    if(result[0] != 0){                                       //divide by zero is not possible
        for(size_t i=0;i<number;i++){
            replace_column(i,number);
            result[i+1] = determine_of_matrix(temp,number);         //find determine for each variable
        }


        cout<<"\n\nSolution is: "<<endl;
        for(size_t i=1;i<=number;i++){
            cout<<variable[i-1]<<" = "<<(double)result[i]/(double)result[0]<<endl;          //print solution
        }
    }
    else{
        cout<<"\n\n These equation has no solution"<<endl;
    }
}



int check_data_type(char item)
{
    int i=-1;
    while(++i < 10){
        if(item == numeric_data[i]){
            return NUMBER;
        }
    }
    if(item == 32){
        return SPACE;           //it is an space
    }
    else if(item == operator_data[0] || item == operator_data[1] || item == operator_data[2] || item == '\0'){
        return OPERATOR;                        //operator separate two variable
    }
    else{
        return CHARACTER;
    }
}


int variable_match(char variable[][20], char store[], int *number_of_variable)
{                                                   //use pointer for increase original variable
    for(int i=0;i<*number_of_variable;i++){
        if(strcmp(variable[i],store)==0){
            return i;
        }
    }
    strcpy(variable[(*number_of_variable)],store);
    return (*number_of_variable)++;
}



int extrac_var_num(string str[], int n)
{

    int coefficient=0, number_of_variable=0,initial=0,store_index=0;

    for(int i=0;i<n;i++){
        while(initial<=(int)str[i].size()){

            if(check_data_type(str[i][initial]) == SPACE){              //If found space it will skip and check next
                //continue;
            }
            else if(check_data_type(str[i][initial]) == NUMBER){
                coefficient = (coefficient * 10) + (str[i][initial] - '0');
            }
            else if(check_data_type(str[i][initial]) == CHARACTER){
                store[store_index++] = str[i][initial];
            }
            else{
                store[store_index] = '\0';                  //variable string terminated by NULL
                store_index = 0;
                matrix[i][variable_match(variable, store, &number_of_variable)] = coefficient;          //add number in matrix
                coefficient = 0;
            }
            initial++;
        }
        initial = 0;        //index start with zero for next line
    }

    return --number_of_variable;                //variable include constant part. So it reduce by one
}





void take_input()
{
    /*This function take equation as input, then separate variable and number.
    Input format: Constant must be locate after equation(=) sign.*/
    unsigned int number;
    string str[SIZE];

    cout<<"Input number of line: ";
    cin>>number;
    getchar();          //for consume ENTER

    cout<<"Input equation one by one "<<endl;
    for(size_t i=0;i<number;i++){
        getline(cin,str[i]);           //Input a line with space
    }

    int num = extrac_var_num(str, number);      //create a matrix and return number of variable

    make_solution(num);                     //print solution

}



void create_matrix()
{
    /*This function use when user want to input only coefficient instate of
    input whole equation*/
    unsigned int number;
    int result[SIZE];
    cout<<"Input variable number: ";
    cin>>number;

    for(size_t i=1;i<=number;i++){
        cout<<"vari"<<i<<" ";
    }
        cout<<"constant"<<endl;

    for(size_t i=0;i<number;i++){           //take coefficient of variable
        for(size_t j=0;j<number+1;j++){
            cin>>matrix[i][j];
        }
    }

    result[0] = determine_of_matrix(matrix,number);

    if(result[0] != 0){                         //divide by is not posible
        for(size_t i=0;i<number;i++){
            replace_column(i,number);
            result[i+1] = determine_of_matrix(temp,number);         //calculate determine of matrix
        }


        cout<<"Solution is: "<<endl;                    //print solution
        for(size_t i=1;i<=number;i++){
            cout<<"variable"<<i<<": "<<(double)result[i]/(double)result[0]<<endl;
        }
    }
    else{
        cout<<"\n\n These equation has no solution"<<endl;
    }
}
