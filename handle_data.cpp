
#include<bits/stdc++.h>
#include "linker.h"
//#define SIZE 100
using namespace std;



double det_of_matrix(double arr[][100], unsigned int number)
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


vector<double> read_from_file(int row, int column,int index)
{
    fstream myfile("sakib.txt");
    double temp;
    vector<double> line;

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            myfile>>temp;
            if(j == (index)){
                line.push_back(temp);
            }
        }

    }

    /*cout<<"\n check input ";
    for(size_t i=0;i<line.size();i++){
        cout<<line[i]<<" ";
    }
    cout<<endl;*/

    return line;
}




void write_in_file(vector<double> line)
{
    fstream myfile("sakib.txt",ios::app);

    for(int i=0;i<line.size();i++){
        myfile<<line[i]<<"\t";
    }
    myfile<<endl;

    myfile.close();
}


bool is_zero(vector<double>line, int index)
{
    for(int i=0;i<=index;i++){
        if(line[i] == 0){
            return true;
        }
    }

    return false;
}


void sample(int number)
{
    vector<double> new_line,old_line;
    old_line = read_from_file(0);

    for(int i=0;i<number;i++){
        new_line = read_from_file(i+1);
        for(int j=number-1;j>i;j--){

            double ratio_col = old_line[j]/new_line[i];

            old_line[i] -= ()

        }
    }
}


void save_transpose_file(int number, int column)
{
    cout<<"uyurytuyt"<<endl;
    ofstream file_name("transpose.txt");
    vector<double> new_line,old_line;

    old_line = read_from_file(number, column, number-1);

    for(size_t i=0;i<number;i++)
    {
        new_line = read_from_file(number, column, number-i-2);
        for(size_t j=number-1;j>i;j--)
        {
            if(old_line[i] == 0){

                for(int s=0;s<old_line.size();s++){
                    cout<<old_line[s]<<" ";
                }
                cout<<endl;
                continue;
            }
            else{
                if(new_line[i] == 0){
                    //exchange row
                    /*for(size_t x =0;x<number;x++){
                        double temp = arr[j][x];
                        arr[j][x] = arr[j-1][x];
                        arr[j-1][x] = temp;
                    }*/
                    vector<double> v1;
                    v1.insert(v1.end(), new_line.begin(), new_line.end());
                    new_line.clear();
                    new_line.insert(new_line.end(), old_line.begin(), old_line.end());
                    old_line.clear();
                    old_line.insert(old_line.end(), new_line.begin(), new_line.end());

                    for(int s=0;s<old_line.size();s++){
                    cout<<old_line[s]<<" ";
                    }
                    cout<<endl;
                    continue;
                }

               double req_ratio = old_line[i] / new_line[i];
               //cout<<"Ratio "<<req_ratio<<endl;

                for(size_t k =0;k<number;k++){
                        //cout<<old_line[k]<<" "<<new_line[k]<<endl;
                    old_line[k] = old_line[k] - req_ratio * new_line[k];
                }

                for(int s=0;s<old_line.size();s++){
                    cout<<old_line[s]<<" ";
                }
                cout<<endl;
            }
        }
    }
    //calculate determine

    /*double sum =1;
    for(size_t i=0;i<number;i++){
        //sum *= arr[i][i];
        cout<<2
    }*/
    //cout<<"result is: "<<sum<<endl;

   // return sum;

        //new_line.clear();       //for later use
}




void controller_file(int row, int column)
{
   ifstream ifile;              //delete previous file
   ifile.open("sakib.txt");
   if(ifile) {
        if(remove("sakib.txt") != 0){
            cout<<"Something went wrong. Couldn't complete this";
        }
   }
   ifile.close();


    vector<double> line;
    double temp ;
    //int row, column;

    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            cin>>temp;
            line.push_back(temp);
        }

        write_in_file(line);
        line.clear();
    }


}


/*int main()
{
    //freopen("in","r",stdin);
    //int m=3,n=3;
    //cin>>m>>n;

    //take_input(m,n);
    vector<double> line;
    line= read_from_file(3,3,1);

    for(int i=0;i<line.size();i++){
        cout<<line[i]<<" ";
    }
    cout<<"Inside function";
    save_transpose_file(3, 3);
}*/
