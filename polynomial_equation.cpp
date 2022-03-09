#include<bits/stdc++.h>
#include "linker.h"

#define space 0
#define operator_symbol 1
#define number 2
#define character 3
#define fractional_point 4
#define power 5



using namespace std;


char decimal_number[] = {'0','1','2','3','4','5','6','7','8','9'};
bool is_equal = false,is_decimal = false, is_negative1= false, is_negative2 = false, is_power = false;

double save[SIZE]={0};


int data_type(char item)
{
    int i=-1;
    while(++i < 10){
        if(item == decimal_number[i]){
            return number;
        }
    }
    if(item == 32){
        return space;           //it is an space
    }
    else if(item == '+' || item == '=' || item == '\0'){
        return operator_symbol;                        //operator separate two variable
    }
    else if(item == '-'){
        is_negative2 = true;
        return operator_symbol;
    }
    else if(item == '.'){
        return fractional_point;
    }
    else if(item == '^'){
        return power;
    }
    else{
        return character;
    }
}



int organize_equation(string str)
{
    int highest_power=0;



    double coefficient=0;
    int power_coefficient=0,initial=0,store_index=0,power_index=1;
    char store[SIZE];


//cout<<"str size "<<str.size();
        while(initial<=(int)str.size()){

                //cout<<"\n initial  "<<initial<<" "<<str[initial]<<endl;

            if(data_type(str[initial]) == space){              //If found space it will skip and check next
                //continue;
            }
            else if(data_type(str[initial]) == number){ //cout<<" In number part ";
                if(is_power){
                      power_coefficient = (power_coefficient * 10) + (str[initial] - '0');
                     // cout<<" power "<<power_coefficient<<endl;
                }
                else{
                    if(is_decimal){                      //there are a floating point
                        coefficient += ((str[initial] - '0')/pow(10,power_index++));
                    }
                    else{                           //there are no floating point
                        coefficient = (coefficient * 10) + (str[initial] - '0');
                    }
                }
            }
            else if(data_type(str[initial]) == fractional_point){
                is_decimal = true;
            }
            else if(data_type(str[initial]) == character){
                store[store_index++] = str[initial];
            }
            else if(data_type(str[initial]) == power){
                is_power = true;
            }
            else if(data_type(str[initial]) == power){
                is_equal = true;
            }
            else{
                //cout<<" in calculation part ";
                store[store_index] = '\0';                  //variable string terminated by NULL
                store_index = 0;
                if(coefficient == 0  && (strlen(store) != 0)){                       //when there are no coefficient before variable, there are a default variable 1
                    coefficient = 1;
                }

                if(power_coefficient == 0  && (strlen(store) != 0)){                       //when there are no coefficient before variable, there are a default variable 1
                    power_coefficient = 1;
                }
                if((is_negative1 && !is_equal) || (!is_negative1 && is_equal)){            //there are negative value before variable
                    coefficient *= -1;
                }

                is_negative1 = is_negative2;
                is_negative2 = false;


                save[power_coefficient] += coefficient;   //add coefficient number in matrix
                //cout<<" iuuuuu "<<power_coefficient<<"  "<<save[power_coefficient]<<endl;

                if(power_coefficient>highest_power){
                    highest_power = power_coefficient;
                }
                power_coefficient = 0;

                if(str[initial] == '='){
                    is_equal = true;
                }

                coefficient = 0;
                power_index = 1;
                is_decimal = false;
                is_power = false;

            }
            initial++;
            //cout<<"Work";

        }







    return highest_power;

}


void input_controller()
{
    string str;

    cout<<"Input equation";
    getline(cin,str);


    int total_power = organize_equation(str);

    cout<<" Total power "<<total_power<<endl;

    for(int i=0;i<=total_power;i++){
        cout<<i<<"  "<<save[i]<<endl;
    }
}


