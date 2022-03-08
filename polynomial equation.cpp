#include<bits/stdc++.h>
#include "linker.h"

using namespace std;

#define N 100
#define space 0
#define operator 1
#define numerical 2
#define character 3
#define fractional_point 4
#define power 5


double coefficient[SIZE]={0};
char number[]={'0','1','2','3','4','5','6','7','8','9'};
bool isEqual, isNegative1, isNegative2, decimal_poin, isPower,firstVriable=true;



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


int separte_variable_and_number(string str)
{

	double coefficient_store=0;
    int power_coefficient=0,initial=0,store_index=0,power_index=1,highest_coefficient;
    char store[SIZE];



        isEqual = false;        //need to change
        isNegative1 = false;
        isNegative2 = false;
        decimal_point = false;
        isPower = false;

        while(initial<=(int)str.size()){

            if(check_data_type(str[initial]) == SPACE){              //If found space it will skip and check next
                //continue;
            }
            else if(check_data_type(str[initial]) == NUMBER){
                if(isPower){
                        power_coefficient = (power_coefficient * 10) + (str[initial] - '0');

                }
                else{
                    if(decimal_point){                      //there are a floating point
                            coefficient_store += ((str[initial] - '0')/pow(10,power_index++));
                    }
                    else{                           //there are no floating point
                        coefficient_store = (coefficient_store * 10) + (str[initial] - '0');
                    }


                }

            }
            else if(check_data_type(str[initial]) == FRACTIONAL_POINT){
                decimal_point = true;
            }
            else if(check_data_type(str[initial]) == CHARACTER){
                store[store_index++] = str[initial];
            }
            else if(check_data_type(str[initial]) == POWER){            //there found a power
                isPower = true;

            }
            else{

                store[store_index] = '\0';                  //variable string terminated by NULL
                store_index = 0;
                if(coefficient_store == 0  && (strlen(store) != 0)){                       //when there are no coefficient before variable, there are a default variable 1
                    coefficient_store = 1;
                }
                if((isNegative1 && !isEqual) || (!isNegative1 && isEqual)){            //there are negative value before variable
                    coefficient_store *= -1;
                }

                if(power_coefficient == 0 && strlen(store) != 0){
                    power_coefficient = 1;
                }

                isNegative1 = isNegative2;
                isNegative2 = false;


                coefficient[power_coefficient] += coefficient_store;   //add coefficient number in matrix
                if(power_coefficient>highest_coefficient){
                    highest_coefficient = power_coefficient;
                }

                if(str[initial] == '='){
                    isEqual = true;
                }

                coefficient_store = 0;
                power_coefficient = 0;
                power_index = 1;
                decimal_point = false;
                isPower = false;


            }
            initial++;
        }




    //organize_variable(number_of_variable);

    return highest_coefficient;                //variable include constant part. So it reduce by one

}



void solver()
{

freopen("test","r",stdin);
	string str;

	cout<<"Input a polynomial equation\n";
	getline(cin,str);

	int total_power = separte_variable_and_number(str);
	cout<<"Number of variable is :"<<total_power<<endl;

	cout<<"Print here equation\n";
	for(int i=0;i<=total_power;i++){
        cout<<i<<"  "<<coefficient[i]<<endl;
	}


}

