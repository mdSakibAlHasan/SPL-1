#include<bits/stdc++.h>
#include "linker.h"
#include "linear.h"
#define N 10000
using namespace std;

vector<double>last_line;
//row reduction method for find determine of matrix

void extract_last_line(int number)
{
    ifstream file_read("save_file.txt");
    double temp;

    for(int i=0;i<number;i++){
        for(int j=0;j<=number;j++){
            file_read>>temp;
            if(j == number){
                last_line.push_back(temp);
            }
        }
    }

}


void transfer_file(int number)
{
    /*transfer data one file to another file*/

    double temp;

    ifstream read_file("transpose.txt");
    ofstream write_file("sakib.txt");

    for(int i=0;i<number-1;i++)
    {
        for(int j=0;j<number-1;j++)
        {
            read_file>>temp;
            write_file<<temp<<"\t";
        }
        write_file<<endl;
    }
}


double save_in_file(int number,int column)
{

    ofstream file_name("transpose.txt");
    ifstream myfile("sakib.txt");


    double temp;
    vector<double> first_line;


    for(int j=0;j<number-column;j++){      //read first line and saved in file
        myfile>>temp;
        first_line.push_back(temp);
    }



    for(int i=1;i<number-column;i++)            //make upper triangular and saved in file
    {
        myfile>>temp;
        double rto = temp/first_line[0];
        for(int j=1;j<(number-column);j++){
            myfile>>temp;
            temp -= (rto * first_line[j]);
            file_name<<temp<<"\t";
        }
        file_name<<endl;

    }

    myfile.close();         //closing file
    file_name.close();

    transfer_file(number-column);


    return first_line[0];
}



double find_det_of_matrix(int row)
{
    double result = 1,temp;

    for(int i=0;i<row-1;i++){
        temp = save_in_file(row,i);
        result *= temp;
    }

    //last value need to calculate
    ifstream read_file("sakib.txt");
    read_file>>temp;

    result *= temp;

    //cout<<"Determine of matrix is "<<result<<endl;
    return result;
}


double create_temp_file(int number, int index)
{
    ofstream file_write("sakib.txt");
    ifstream file_read("save_file.txt");

    double temp;

    for(int i=0;i<number;i++){
        for(int j=0;j<number;j++){
            file_read>>temp;

            if(index == j){
                file_write<<last_line[i]<<"\t";
            }
            else{
                file_write<<temp<<"\t";
            }
        }
        file_read>>temp;
        file_write<<endl;
    }

    file_read.close();
    file_write.close();

    return find_det_of_matrix(number);
}


void create_solution()
{
    /*This function use when user want to input only coefficient instate of
    input whole equation*/
    int number;
    double result[N],temp_input;
    cout<<"Input variable number: ";
    cin>>number;

    for(int i=1;i<=number;i++){
        cout<<"vari"<<i<<" ";
    }
    cout<<"constant"<<endl;

    ofstream save_file("save_file.txt");

    for(int i=0;i<number;i++){           //take coefficient of variable
        for(int j=0;j<number+1;j++){
            cin>>temp_input;
            save_file<<temp_input<<"\t";
        }
    }

    save_file.close();
    extract_last_line(number);

    result[0] = create_temp_file(number,number);

    //cout<<"Result "<<result[0]<<endl;

    for(int i=0;i<number;i++){
            //replace_column(number);
            result[i+1] = create_temp_file(number,number-i-1);         //calculate determine of matrix
    }


    if(result[0] != 0){                         //divide by is not posible

        cout<<"Solution is: "<<endl;                    //print solution
        for(int i=1;i<=number;i++){
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
