#include<bits/stdc++.h>
#include "linear.h"
#define SIZE 20
#define phi 1e-12

using namespace std;

int n;
double a[SIZE],b[SIZE],c[SIZE], r, s, old_r, old_s,dr,ds,root_p, root_q;
bool last = false;          //for last rest equation


double absolute(double x)
{
    //return absolute value
    if(x<0){
        x *= -1;
    }


    return x;
}



double remove_error(double value)
{
    //floating point never goes to zero. for a particular error we need to avoid these error
    int integer = value;
    if(absolute(integer - value) <= phi){

        value = (double)integer;
    }

    return value;
}





void print_root(double x,double p, double q)
{

    if(!last){
            //for r and s , we need to change sign of r and s
        p = (-1)*remove_error(p);
        q =(-1)*remove_error(q);
    }
    else{
        // we find solution from rest of equation
        p = remove_error(p);
        q = remove_error(q);
    }

    double determine = (p*p) - (4*x*q);


    if(determine<0){
        determine *= -1;

        determine = sqrt(determine);

        if(p == 0){
                //pure imaginary number
            if((determine/(2*x)) == 1){
                    //coefficient 1 , not necessary to print
                cout<<"\tRoot: "<<"i"<<endl;
                cout<<"\tRoot: "<<"-i"<<endl;
            }
            else{
                    //there are coefficient
                cout<<"\tRoot: "<<(determine/(2*x))<<"i"<<endl;
                cout<<"\tRoot: "<<(determine/(2*x))<<"-i"<<endl;
            }

        }
        else{
                //when not a pure imaginary number
            if((determine/(2*x)) == 1){
                    //coefficient 1 , not necessary to print
                cout<<"\tRoot: "<<((-p)/(2*x))<<" + "<<"i"<<endl;
                cout<<"\tRoot: "<<((-p)/(2*x))<<" - "<<"i"<<endl;
            }
            else{
                    //there are coefficient
                cout<<"\tRoot: "<<((-p)/(2*x))<<" + "<<(determine/(2*x))<<"i"<<endl;
                cout<<"\tRoot: "<<((-p)/(2*x))<<" - "<<(determine/(2*x))<<"i"<<endl;
            }

        }
    }
    else{
        determine = sqrt(determine);

        double first = remove_error(((-p) - determine)/(2*x));
        double second =  remove_error(((-p) + determine)/(2*x));

        cout<<"\tRoot: "<<first<<endl;
        cout<<"\tRoot: "<<second<<endl;


    }

}



void print_root_one(double x, double y)
{
    // If existance equation has only one solution
    x *= -1;
    y *= -1;

    double root = -(y/x);

    cout<<"\tRoot: "<<root<<endl;

}






void calculate_r_s()
{
    //for iteration we need to find r and s. From r and s we find two solution of equation

    dr = (b[0]*c[3] - b[1]*c[2]) / (c[2]*c[2] - c[1]*c[3]);

    ds = (b[1]*c[1] - b[0]*c[2]) / (c[2]*c[2] - c[1]*c[3]);

    old_r = r ;
    old_s = s;

    r += dr;
    s += ds;

}


void calculate_column(double p[], double q[])
{
    //iteration column to find solution
    q[n] = p[n];
    q[n-1] = p[n-1] + q[n]*r;

    for(int i=n-2;i>=0;i--){
        q[i] = p[i] + (q[i+1]*r) + (q[i+2]*s);
    }

}



void reduce_equation()
{
    //After iteration we find two solution and the equations's power reduce by two.
    //Replace a[] coefficient by b[] coefficient
    for(int i=0;i<n-1;i++){
        a[i] = b[i+2];
    }

    n -= 2;
}





void find_root()
{
    //iteration until equation goes to power 1 or 2
    double ratio_s, ratio_r;


    if(n == 0){
        cout<<"No such variable.\n Wrong input\n\n";
        exit(0);
    }
    else if(n == 1){
        print_root_one(a[n], a[n-1]);
    }
    else if(n == 2){
        print_root(a[n] , a[n-1] , a[n-2]);
    }
    else{


        while(1){
            calculate_column(a,b);
            calculate_column(b,c);

            calculate_r_s();

            ratio_s = ds/old_s;
            ratio_r = dr/old_r;


            if(((absolute(b[0]) <= phi) && (absolute(b[1]) <= phi)) || ((absolute(ratio_r) <= phi) || (absolute(ratio_s) <= phi))){

                print_root(1,r,s);

                if(n == 4){
                    last = true;            //for last part there no sign change

                    print_root(b[n],b[n-1],b[n-2]);

                    break;              //equation go to zero
                }

                if(n == 3){
                    print_root_one(b[n], b[n-1]);

                    break;
                }

                reduce_equation();

            }

        }

    }


}


void starting_method(double pass[], int total)
{
    //copy array to global array
    for(int i= total;i>=0;i--){
        a[i] = pass[i];

    }
    n = total;


    r = a[n-1]/a[n];
    s = a[n-2]/a[n];

    if(r == 0){
        r = 0.1;        //default value of r
    }

    if(s ==0){
        s = 0.1;        //default value of s
    }

    find_root();

}

