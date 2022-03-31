
#include<bits/stdc++.h>
#define SIZE 100
using namespace std;



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


void save_transpose_file(int row, int column)
{
    ofstream file_name("transpose.txt");
    vector<double> new_line,old_line;


    for(int i=0;i<row;i++){

        new_line = read_from_file(row,column,i);
        /*if(is_zero(new_line,i)){
            for(int k=0;k<column;k++){
                double p = new_line[i];
                new_line[i] = old_line[i];
                old_line[i] = p;
            }
        }

        if(i != 0){
            for(int j=0;j<old_line.size();j++){
                file_name<<old_line[i]<<endl;
            }
        }

        for(int k=0;k<column;k++){
            old_line[i] = new_line[i];
        }*/

        for(int j=0;j<new_line.size();j++){
            file_name<<new_line[j]<<"\t";
        }
        file_name<<endl;


        cout<<"One line complete"<<endl;
        new_line.clear();

    }


}



void take_input(int row, int column)
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


int main()
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
}
