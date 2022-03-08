using namespace std;
#define SIZE 20
#define SPACE 0
#define OPERATOR 1
#define NUMBER 2
#define CHARACTER 3
#define FRACTIONAL_POINT 4


char numeric_data[]={'0','1','2','3','4','5','6','7','8','9'};
bool decimal_point,isNegative1, isNegative2,isEqual;

//void take_input();
void solve_linear_equation();
void create_matrix();
int solve_linear_programming(string str[] , double matrix_2[SIZE][SIZE], char vari_name[][20],int number);
void input_linear_programming();
