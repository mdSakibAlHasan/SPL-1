#include<bits/stdc++.h>
//#include "linker.h"
#include "linear.h"
using namespace std;


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



void find_det_of_matrix(int row, int column)
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

    cout<<"Determine of matrix is "<<result<<endl;

}
