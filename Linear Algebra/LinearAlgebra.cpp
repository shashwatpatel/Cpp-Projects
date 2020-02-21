#include <iostream>

int main() {
void transpose();
void multiply();
int choice;
//Menu
std::cout << "Welcome to Linear Algebra, this program computes transpose and multiplication of matrices" << std::endl;
std::cout << "Enter your choice of operation, 1 for transpose, and 2 for multiplication: ";
std::cin >> choice;
	//Call the functions
	if (choice == 1) { transpose(); }
	else if (choice == 2) { multiply(); }
	else { std::cout << "Choose either 1 or 2. \n"; }

return 0;
}
void transpose() {
	//Initialization (I used 100 x 100 matrix as max, could change it to any number)
   int matrix[100][100], transpose[100][100], row, col;
   //Ask the user to enter the number of rows and columns and elements of the matrix
   //****Make sure to enter elements of matrix with space in between each element example: 1 2 3...****
   std::cout << "Enter the number of rows: ";
   std::cin >> row; 
   std::cout << "Enter the number of columns: ";
   std::cin >> col;
   std::cout << "Enter the elements of the matrix: " << std::endl;
   //Loop to check transpose
  for(int i = 0; i < row; ++i) for(int j = 0; j < col; ++j) { std::cin >> matrix[i][j]; }
  for(int i = 0; i < row; ++i) for(int j = 0;j < col; ++j) { transpose[j][i] = matrix[i][j]; }
  //Display results
  std::cout<< "Transpose of Matrix: " << std::endl;
  for(int i = 0; i < col; ++i) for(int j = 0; j < row; ++j) { 
	  std::cout << transpose[i][j] << " ";      
      if(j == row - 1)
        std::cout << std::endl;
    }
}
void multiply() {
	//Initialization (I used 100 x 100 matrix as max, could change it to any number)
	//Initialize both matrices that need to be computed and also the output matrix
	int mat1[100][100], mat2[100][100], mult[100][100], rowFirst, rowSecond, colFirst, colSecond;
	//Asks the user to input his desired matrix
	std::cout << "Enter the number of rows (Matrix 1): ";
	std::cin >> rowFirst;
	std::cout << "Enter the number of columns (Matrix 1): ";
	std::cin >> colFirst;
	std::cout << "Enter the number of rows (Matrix 2): ";
	std::cin >> rowSecond;
	std::cout << "Enter the number of columns (Matrix 2): ";
	std::cin >> colSecond;
	//If the matrix multiplication rule doesn't apply then asks the user to reenter his matrix
	//Rule:  colOfMatrix1 = rowOfMatrix2 else multiplication cannot happen
	while(colFirst != rowSecond) { 
	std::cout << "Error! Column first is not equal to second row, operation invalid. \n";
	std::cout << "Re-enter rows and columns. \n";
	std::cout << "Enter the number of rows (Matrix 1): ";
	std::cin >> rowFirst;
	std::cout << "Enter the number of columns (Matrix 1): ";
	std::cin >> colFirst;
	std::cout << "Enter the number of rows (Matrix 2): ";
	std::cin >> rowSecond;
	std::cout << "Enter the number of columns (Matrix 2): ";
	std::cin >> colSecond; 
	}
	//Enter elements of both matrices
	//****Make sure to enter elements of matrix with space in between each element example: 1 2 3...****
	std::cout << "Enter the elements of first matrix: " << std::endl;
	for(int i = 0; i < rowFirst; ++i) for(int j = 0; j < colFirst; ++j) { std::cin >> mat1[i][j]; }
	std::cout << "Enter the elements of second matrix: " << std::endl;
	for(int i = 0; i < rowSecond; ++i) for(int j = 0; j < colSecond; ++j) { std::cin >> mat2[i][j]; }
	//Compute multiplication and print results
	std::cout << "Multiplication of the matrix: " << std::endl;
	for(int i = 0; i < rowFirst; ++i) for(int j = 0; j < colSecond; ++j) { 
		mult[i][j] = 0;
		for(int k = 0; k < colFirst; ++k) { mult[i][j] += mat1[i][k] * mat2[k][j]; }
		}
	for(int i = 0; i < rowFirst; ++i) {
		for(int j = 0; j < colSecond; ++j) { 
		std::cout << mult[i][j] << "  "; }
		std::cout << std::endl; 
		}
	}
