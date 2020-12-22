#include "Matrix.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include<iostream>

int main()
{
	
	int r1, c1, ** a;
	int noOfzero1 = 0, noOfzero2 = 0;

	std::cout << "Enter number of rows (between 1 and 20): ";
	std::cin >> r1;

	std::cout << "Enter number of columns (between 1 and 20): ";
	std::cin >> c1;

	std::cout << std::endl << "Enter elements of 1st matrix: " << std::endl;

	//create space for first matrix
	a = new int* [c1];
	for (int i = 0; i < r1; i++)
	{
		a[i] = new int[c1];
	}

	// Storing elements of first matrix entered by user.
	for (int i = 0; i < r1; ++i)
		for (int j = 0; j < c1; ++j)
		{
			std::cout << "Enter element a(" << i + 1 << "," << j + 1 << "): ";
			std::cin >> a[i][j];
			if (a[i][j] == 0)
			{
				noOfzero1++;
			}
		}
	int r2, c2, ** b;
	std::cout << "Enter number of rows for second matrix (between 1 and 20): ";
	std::cin >> r2;

	std::cout << "Enter number of columns for second matrix (between 1 and 20): ";
	std::cin >> c2;

	std::cout << std::endl << "Enter elements of 2nd matrix: " << std::endl;
	//create space for 2nd matrix
	b = new int* [c2];
	for (int i = 0; i < r2; i++)
	{
		b[i] = new int[c2];
	}

	// Storing elements of first matrix entered by user.
	for (int i = 0; i < r2; ++i)
		for (int j = 0; j < c2; ++j)
		{
			std::cout << "Enter element a(" << i + 1 << "," << j + 1 << "): ";
			std::cin >> b[i][j];
			if (b[i][j] == 0)
			{
				noOfzero2++;
			}
		}

	Matrix* m1, * m2;

	if (noOfzero1 <= ((r1 * c1) / 2))
	{
		m1 = new DenseMatrix(r1, c1, a);
		std::cout << "1st Matrix saved as Dense matrix!! " << std::endl;
	}
	else
	{
		m1 = new SparseMatrix(r1, c1, a);
		std::cout << "1st Matrix saved as Sparse matrix!! " << std::endl;
	}

	if (noOfzero2 <= ((r2 * c2) / 2))
	{
		m2 = new DenseMatrix(r2, c2, b);
		std::cout << "2nd Matrix saved as Dense matrix!! " << std::endl;
	}
	else
	{
		m2 = new SparseMatrix(r2, c2, b);
		std::cout << "2nd Matrix saved as Sparse matrix!! " << std::endl;
	}

	
	std::cout << std::endl;
	int choice;
	std::cout << "Which operation do you want to do ?" << std::endl;
	std::cout << "1.Addition" << std::endl;
	std::cout << "2.Subtruction" << std::endl;
	std::cout << "3.Multiplication" << std::endl;
	std::cout << "4.Multiplication with a constant" << std::endl;
	std::cout << "5.Check if they are equal" << std::endl;
	std::cout << "6.Transpose" << std::endl;
	std::cout << "7.Resize" << std::endl;
	std::cin >> choice;

	std::cout << std::endl;
	if (choice == 1)
	{
		m1 = &(*m1 + *m2);
		m1->printm();
	}
	else if (choice == 2)
	{
		m1 = &(*m1 - *m2);
		m1->printm();
	}
	else if (choice == 3)
	{
		m1 = &(*m1 * *m2);
		m1->printm();
	}
	else if (choice == 4)
	{
		int constant;
		std::cout << "Enter the constant to be muitliplied:";
		std::cin >> constant;
		m1 = &(*m1 * constant);
		m1->printm();
	}
	else if (choice == 5)
	{
		std::cout << (*m1 == *m2);
	}
	else if (choice == 6)
	{
		int ans;
		std::cout << "which matrix do you want to transpose (1/2):";
		std::cin >> ans;
		if (ans == 1)
		{
			m1->Transpose();
			m1->printm();
		}
		else if (ans == 2)
		{
			m2->Transpose();
			m2->printm();
		}
		else
		{
			std::cout << "invalid answer!!! Exiting !!";
			return 0;
		}
	}
	else if(choice == 7)
	{
		int row, column;
		std::cout << "Please write the number of rows:";
		std::cin >> row;
		std::cout << "Please write the number of column:";
		std::cin >> column;
		m1->Resize(row, column);
		m1->printm();
	}
	else
	{
		std::cout << "invalid answer!!! Exiting !!";
		return 0;
	}
	
}