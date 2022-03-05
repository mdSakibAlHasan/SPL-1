#include<bits/stdc++.h>
#include "linker.h"
#define SIZE 20
using namespace std;

#define SPACE 0
#define OPERATOR 1
#define NUMBER 2
#define CHARACTER 3
#define FRACTIONAL_POINT 4

double matrix[SIZE][SIZE]={0},temp[SIZE][SIZE];
char numeric_data[]={'0','1','2','3','4','5','6','7','8','9'};
char variable[SIZE][20], store[20];
bool decimal_point,isNegative1, isNegative2,isEqual;
//int variable_number;

double determine_of_matrix(double arr[][SIZE], unsigned int number);



int make_small_matrix(double arr[][SIZE], unsigned int number, unsigned int replace_number)
{
    /*Here we calculate determine of matrix by reducing size of matrix, until matrix size will be 2.
    When its size will be 2, then it calculate and return value. This function reduce matrix size and
    make a small matrix*/

    double small_matrix[SIZE][SIZE];
    int track=0;
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


double determine_of_matrix(double arr[][SIZE], unsigned int number)
{
    /*This function calculate determine of matrix*/

    if(number == 2){
        return (arr[0][0]*arr[1][1]) - (arr[0][1]*arr[1][0]);
    }
    else{
        double summation=0;
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



bool check_infinite_solution(double result[], int number_of_variable)
{
	for(int i=1;i<=number_of_variable;i++){
		if(result[i] != 0){			//There are infinite solution if all determine are zero
			return false;
		}
	}

	return true;
}



void make_solution(int number_of_variable)
{
    //variable_number = number_of_variable;               //make it global variaable
    double result[SIZE];
    unsigned int number = (unsigned)number_of_variable;          //make signed int to unsigned int

    result[0] = determine_of_matrix(matrix,number);             // make determine for constant

    for(size_t i=0;i<number;i++){
            replace_column(i,number);
            result[i+1] = determine_of_matrix(temp,number);         //find determine for each variable
    }

    if(result[0] != 0){                                       //divide by zero is not possible

        cout<<"\n\nSolution is: "<<endl;
        for(size_t i=1;i<=number;i++){
            cout<<variable[i-1]<<" = "<<result[i]/result[0]<<endl;          //print solution
        }
    }
    else{
        if(check_infinite_solution(result, number_of_variable)){
		      cout<<"\n\n These equation has infinitely many solution"<<endl;
         }
	     else{
              cout<<"\n\n These equation has no solution"<<endl;
	     }
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
    else if(item == '+' || item == '=' || item == '\0'){
        return OPERATOR;                        //operator separate two variable
    }
    else if(item == '-'){
        isNegative2 = true;
        return OPERATOR;
    }
    else if(item == '.'){
        return FRACTIONAL_POINT;
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




void organize_variable(int variable_number)
{
    /* When we solve equation with matrix method, we need organize variable and locate constant in last*/
    int d_index;

    if(strlen(variable[variable_number-1]) != 0){

        for(int i=0;i<variable_number-1;i++){
            if(strlen(variable[i]) == 0){
                d_index = i;
            }
        }

        char vari_swap[20];
        strcpy(vari_swap, variable[d_index]);                           //swap two variable
        strcpy(variable[d_index], variable[variable_number-1]);
        strcpy(variable[variable_number-1], vari_swap);

        for(int i=0;i<variable_number-1;i++){                               //swap two matrix column
            double x = matrix[i][d_index];
            matrix[i][d_index] = matrix[i][variable_number-1];
            matrix[i][variable_number-1] = x;
        }
    }

    for(int i=0;i<variable_number-1;i++){
        matrix[i][variable_number-1] *= -1;
    }
}


int extrac_variable_number(string str[], int n)
{

    double coefficient=0;
    int number_of_variable=0,initial=0,store_index=0,power_index=1;


    for(int i=0;i<n;i++){
        isEqual = false;
        isNegative1 = false;
        isNegative2 = false;
        decimal_point = false;

        while(initial<=(int)str[i].size()){

            if(check_data_type(str[i][initial]) == SPACE){              //If found space it will skip and check next
                //continue;
            }
            else if(check_data_type(str[i][initial]) == NUMBER){
                if(decimal_point){                      //there are a floating point
                    coefficient += ((str[i][initial] - '0')/pow(10,power_index++));
                }
                else{                           //there are no floating point
                    coefficient = (coefficient * 10) + (str[i][initial] - '0');
                }
            }
            else if(check_data_type(str[i][initial]) == FRACTIONAL_POINT){
                decimal_point = true;
            }
            else if(check_data_type(str[i][initial]) == CHARACTER){
                store[store_index++] = str[i][initial];
            }
            else{

                store[store_index] = '\0';                  //variable string terminated by NULL
                store_index = 0;
                if(coefficient == 0  && (strlen(store) != 0)){                       //when there are no coefficient before variable, there are a default variable 1
                    coefficient = 1;
                }
                if((isNegative1 && !isEqual) || (!isNegative1 && isEqual)){            //there are negative value before variable
                    coefficient *= -1;
                }

                isNegative1 = isNegative2;
                isNegative2 = false;


                matrix[i][variable_match(variable, store, &number_of_variable)] += coefficient;   //add coefficient number in matrix

                if(str[i][initial] == '='){
                    isEqual = true;
                }

                coefficient = 0;
                power_index = 1;
                decimal_point = false;


            }
            initial++;
        }
        initial = 0;        //index start with zero for next line
    }


    organize_variable(number_of_variable);

    return --number_of_variable;                //variable include constant part. So it reduce by one
}





int take_input(string str[])
{
    /*This function take equation as input, then separate variable and number.
    Input format: Constant must be locate after equation(=) sign.*/
    unsigned int number;

    cout<<"Input number of line: ";
    cin>>number;
    getchar();          //for consume ENTER

    cout<<"Input equation one by one "<<endl;
    for(size_t i=0;i<number;i++){
        getline(cin,str[i]);           //Input a line with space
    }

    return number;
}



void create_matrix()
{
    /*This function use when user want to input only coefficient instate of
    input whole equation*/
    unsigned int number;
    double result[SIZE];
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

    for(size_t i=0;i<number;i++){
            replace_column(i,number);
            result[i+1] = determine_of_matrix(temp,number);         //calculate determine of matrix
    }

    if(result[0] != 0){                         //divide by is not posible



        cout<<"Solution is: "<<endl;                    //print solution
        for(size_t i=1;i<=number;i++){
            cout<<"variable"<<i<<": "<<(double)result[i]/(double)result[0]<<endl;
        }
    }
    else{
        if(check_infinite_solution(result, number)){
		      cout<<"\n\n These equation has infinitely many solution"<<endl;
         }
	     else{
              cout<<"\n\n These equation has no solution"<<endl;
	     }
    }
}



void solve_linear_equation()
{
    string str[SIZE];

    int number = take_input(str);
    int num = extrac_variable_number(str, number);      //create a matrix and return number of variable

    make_solution(num);                     //print solution
}


int solve_linear_programming(string str[], double matrix_2[SIZE][SIZE], char vari_name[][20],int number)
{
     int num = extrac_variable_number(str, number);

     for(int i=0;i<num;i++){
        strcpy(vari_name[i], variable[i]);
     }

     for(int i=0;i<=num;i++){
        for(int j=0;j<=num;j++){
            matrix_2[i][j] = matrix[i][j];
        }
     }

     return num;
}
