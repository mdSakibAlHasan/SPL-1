#include<bits/stdc++.h>
#include "linker.h"

#define SPACE 0
#define OPERATOR 1
#define NUMBER 2
#define CHARACTER 3
#define FRACTIONAL_POINT 4
#define POWER 5

using namespace std;

char numeric_data[]={'0','1','2','3','4','5','6','7','8','9'};
bool decimal_point,isNegative1, isNegative2,isEqual;

double matrix[SIZE][SIZE]={0},temp[SIZE][SIZE];
char variable[SIZE][20], store[20];



double det_of_matrix(double arr[][SIZE], unsigned int number)
{

    for(size_t i=0;i<number;i++)
    {
        for(size_t j=number-1;j>i;j--)
        {
            if(arr[j][i] == 0){
                continue;
            }
            else{
                if(arr[j-1][i] == 0){
                    //exchange row
                    for(size_t x =0;x<number;x++){
                        double temp = arr[j][x];
                        arr[j][x] = arr[j-1][x];
                        arr[j-1][x] = temp;
                    }
                    continue;
                }

               double req_ratio = arr[j][i] / arr[j-1][i];

                for(size_t k =0;k<number;k++){
                    arr[j][k] = arr[j][k] - req_ratio * arr[j-1][k];
                }
            }
        }
    }
    //calculate determine

    double sum =1;
    for(size_t i=0;i<number;i++){
        sum *= arr[i][i];
    }
    //cout<<"result is: "<<sum<<endl;

    return sum;
}



double find_determine(double arr[][SIZE], unsigned int number)
{
    //this function make a temporary array and calculate this

    double sakib[SIZE][SIZE];

    for(size_t i=0;i<number;i++)
    {
        for(size_t j=0;j<number;j++){
            sakib[i][j] = arr[i][j];
        }
    }

    return det_of_matrix(sakib, number);
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

    //result[0] = determine_of_matrix(matrix,number);             // make determine for constant
    result[0] = find_determine(matrix,number);             // make determine for constant

    for(size_t i=0;i<number;i++){
            replace_column(i,number);
            result[i+1] = find_determine(temp,number);         //find determine for each variable
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
    else if(item == '^'){
        return POWER;
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

    result[0] = find_determine(matrix,number);

    for(size_t i=0;i<number;i++){
            replace_column(i,number);
            result[i+1] = find_determine(temp,number);         //calculate determine of matrix
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
