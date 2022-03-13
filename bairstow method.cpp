#include<bits/stdc++.h>
#include "linear.h"
#define SIZE 20
#define phi 1e-9

using namespace std;

int n;
double a[SIZE],b[SIZE],c[SIZE], r, s, old_r, old_s,dr,ds,root_p, root_q;


double absolute(double x)
{
    if(x<0){
        x *= -1;
    }


    return x;
}



double remove_error(double value)
{
    int integer = value;

    if(absolute(integer - value) <= phi){

        value = (double)integer;
    }

    return value;
}



void synthetic_divisor(double x, double y)
{
    x *= -1;
    y *= -1;

    double sum = 1;

    for(int i = n-1;i>0;i--){
        //cout<<a[i]<<" "<<x<<" "<<sum<<endl;
        a[i] += (x*sum);
        a[i-1] += (y*sum);

        sum = a[i];
    }



    n -= 2;     //equation reduce 2

    for(int i=0;i<=n;i++){
        a[i] = a[i+2];
    }


    //remove error
    for(int i=0;i<=n;i++){
        a[i] = remove_error(a[i]);
        //cout<<"a "<<a[i]<<endl;
    }

}



void print_root(double x,double p, double q)
{
    double determine = (p*p) - (4*x*q);
    //cout<<"In root finding "<<x<<" "<<p<<" "<<q<<"  "<<determine<<endl;

    if(determine<0){
        determine *= -1;

        determine = sqrt(determine);
        //update pure imaginary number
        //later
        // update this

        cout<<"Root: "<<((-p)/(2*x))<<" + "<<(determine/(2*x))<<"i"<<endl;
        cout<<"Root: "<<((-p)/(2*x))<<" - "<<(determine/(2*x))<<"i"<<endl;



    }
    else{
        determine = sqrt(determine);

        double first = remove_error(((-p) - determine)/(2*x));
        double second =  remove_error(((-p) + determine)/(2*x));

        cout<<"Root: "<<first<<endl;
        cout<<"Root: "<<second<<endl;


    }



}


void print_root_one(double x, double y)
{
    x *= -1;
    y *= -1;

    double root = -(y/x);

    cout<<"Root: "<<root<<endl;

}






void calculate_r_s()
{


    dr = (b[0]*c[3] - b[1]*c[2]) / (c[2]*c[2] - c[1]*c[3]);

    ds = (b[1]*c[1] - b[0]*c[2]) / (c[2]*c[2] - c[1]*c[3]);

    old_r = r ;
    old_s = s;

    r += dr;
    s += ds;

}


void calculate_column(double p[], double q[])
{
    q[n] = p[n];
    q[n-1] = p[n-1] + q[n]*r;

    for(int i=n-2;i>=0;i--){
        q[i] = p[i] + (q[i+1]*r) + (q[i+2]*s);
    }

}





void find_root()
{
    double ratio_s, ratio_r;

    while(1){
        calculate_column(a,b);
        calculate_column(b,c);

        calculate_r_s();

        ratio_s = ds/old_s;
        ratio_r = dr/old_r;

        if(((absolute(b[0]) <= phi) && (absolute(b[1]) <= phi)) || ((absolute(ratio_r) <= phi) || (absolute(ratio_s) <= phi))){
            print_root(b[n],b[n-1],b[n-2]);

            synthetic_divisor(b[n-1],b[n-2]);

            if(n == 2){
                print_root(a[n],a[n-1],a[n-2]);

                break;              //equation go to zero
            }

            if(n == 1){
                print_root_one(a[n], a[n-1]);

                break;
            }
        }

    }

    /*for(int i=0;i<=n;i++){
        cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<endl;
    }
    cout<<"\n\n\n";
*/

}

void starting_method(double pass[], int total)
{

    for(int i= total;i>=0;i--){
        a[i] = pass[i];

    }
    n = total;


    r = a[n-1]/a[n];
    s = a[n-2]/a[n];

    if(r == 0){
        r = 0.1;
    }

    if(s ==0){
        s = 0.1;
    }

    find_root();

}

