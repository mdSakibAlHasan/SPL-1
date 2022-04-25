using namespace std;


#define SIZE 20


void input_controller();


//void take_input();
void solve_linear_equation();
void create_matrix();
int solve_linear_programming(string str[] , double matrix_2[SIZE][SIZE], char vari_name[][20],int number);
void input_linear_programming();
int check_data_type(char item);
//void save_transpose_file(int number, int column);
//void find_det_of_matrix(int row, int column);
bool check_infinite_solution(double result[], int number_of_variable);
void create_solution();
int large_size_matrix();
