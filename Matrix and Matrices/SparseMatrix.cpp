#include "SparseMatrix.h"
#include "DenseMatrix.h"

SparseMatrix::SparseMatrix()
{
	rowsize = 0;
	columnsize = 0;
}

SparseMatrix::SparseMatrix(int row, int column, int** matrix)
{
	//we set the rowsize and column size
	rowsize = row;
	columnsize = column;
	//we iterate the 2d array to find each value that is not 0
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < columnsize; j++)
			if (matrix[i][j] != 0)
			{
				//when we find it we use pushback function to add it into the vector
				Cell temp(i, j, matrix[i][j]);
				cells.push_back(temp);
			}
}

SparseMatrix::SparseMatrix(Matrix& matrix)
{
	//we do the exact same stuff 
	rowsize = matrix.rowsize;
	columnsize = matrix.columnsize;
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < columnsize; j++)
			//but now we use GetInt because we dont know what type of matrix it is
			if (matrix.GetInt(i,j) != 0)
			{
				Cell temp(i, j, matrix.arr[i][j]);
				cells.push_back(temp);
			}
}

SparseMatrix::~SparseMatrix()
{
}

void SparseMatrix::SetInt(int row, int column, int val)
{
	for (int i = 0; i < cells.size(); i++)
		if (cells[i].x == row && cells[i].y == column)
		{
			cells[i].value = val;
			return;
		}
	cells.push_back(*new Cell(row, column, val));
}

int SparseMatrix::GetInt(int row, int column)
{
	//we iterate and find the location of the value then return it
	for (int i = 0; i < cells.size(); i++)
		if (cells[i].x == row && cells[i].y == column)
			return cells[i].value;
	//if not found that means it is empty so we return 0
	return 0;
}

void SparseMatrix::Resize(int row, int column)
{
	int** matrix;
	matrix = new int* [row];
	for (int i = 0; i < column; i++)
		matrix[i] = new int[row];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i >= rowsize || j >= columnsize)
				matrix[i][j] = 0;
			else
				matrix[i][j] = GetInt(i,j);
		}
	}
	SparseMatrix m1(row, column, matrix);
	*this = m1;
}

Matrix& SparseMatrix::Addition(Matrix& matrix)
{
	//we create a densematrix to storevalues in its easier
	DenseMatrix m1(matrix);
	//count for number of zeros
	int count=0;

	for (int i = 0; i < matrix.rowsize; i++)
		for (int j = 0; j < matrix.columnsize; j++)
		{
			//we create 2 loops for matrix to go through all values
			//we add them then store it in m1
			m1.arr[i][j] = matrix.GetInt(i,j) + this->GetInt(i,j);
			//count number of zeros
			if (m1.arr[i][j] == 0)
				count++;
		}
	//we create a matrix pointer to change the matrix into dense or sparse depending on number of zeros
	Matrix* m2;
	if (count <= ((m1.rowsize * m1.columnsize) / 2))
	{
		m2 = new DenseMatrix(m1);
		return *m2;
	}
	else
	{
		m2 = new SparseMatrix(m1);
		return *m2;
	}
}

Matrix& SparseMatrix::Subtruction(Matrix& matrix)
{
	//we make a temporary matrix
	DenseMatrix m1(matrix);
	int count = 0;
	//we iterate each value and subtract the other value and then store it back in there
	for (int i = 0; i < matrix.rowsize; i++)
		for (int j = 0; j < matrix.columnsize; j++)
		{
			m1.arr[i][j] = GetInt(i,j) - matrix.GetInt(i,j);
			//count each zero
			if (m1.arr[i][j] == 0)
				count++;
		}

	//return as either dense or sparse
	Matrix* m2;
	if (count <= ((m1.rowsize * m1.columnsize) / 2))
	{
		m2 = new DenseMatrix(m1);
		return *m2;
	}
	else
	{
		m2 = new SparseMatrix(m1);
		return *m2;
	}
}

Matrix& SparseMatrix::Multiplication(Matrix& matrix)
{
	//we alocate memory as big  as first matrix rowsize and second matrix columnsize
	DenseMatrix* m1 = new DenseMatrix(this->rowsize, matrix.columnsize, 0);
	//we calculate the value for the location and store it in the temporary matrix
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < matrix.columnsize; j++)
		{
			m1->arr[i][j] = 0;
			for (int k = 0; k < columnsize; k++)
				m1->arr[i][j] = m1->GetInt(i, j) + (GetInt(i, k) * matrix.GetInt(k, j));
		}
	return *m1;
}

Matrix& SparseMatrix::Transpose()
{
	//we make a temporary value to swap values
	int temp;
	for (int i = 0; i < cells.size(); i++)
	{
		//then we swap each x and y value
		temp = cells[i].x;
		cells[i].x = cells[i].y;
		cells[i].y = temp;
	}
	return *this;
}

bool SparseMatrix::Equal(Matrix& matrix)
{
	// we check if their size are equal so we can say early on its not
	if ((matrix.rowsize * matrix.columnsize) != (this->rowsize * this->columnsize))
		return false;
	else
		//then we iterate and check each number if any difference we return false
		for (int i = 0; i < rowsize; i++)
			for (int j = 0; j < columnsize; j++)
				if (GetInt(i, j) != matrix.GetInt(i, j))
					return false;
	//if no difference found we return true
	return true;
}

void SparseMatrix::printm()
{

	for (int i = 0; i < rowsize; i++)
	{
		for (int j = 0; j < columnsize; j++)
		{
			std::cout << std::setw(5) << GetInt(i, j);
		}
		std::cout << "\n";
	}
}

Matrix& SparseMatrix::Multiplication(int constant)
{
	//create a temporary matrix
	DenseMatrix m1(*this);
	int count = 0;
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < columnsize; j++)
		{
			//multiply each value with the constant
			m1.arr[i][j] = this->GetInt(i, j) * constant;
			//count the zeros
			if (m1.arr[i][j] == 0)
				count++;
		}

	//return a dense or sparse matrix depending on the number of zeros
	Matrix* m2;
	if (count <= ((m1.rowsize * m1.columnsize) / 2))
	{
		m2 = new DenseMatrix(m1);
		return *m2;
	}
	else
	{
		m2 = new SparseMatrix(m1);
		return *m2;
	}
}

Matrix& SparseMatrix::operator+(Matrix& matrix)
{
	return Addition(matrix);
}

Matrix& SparseMatrix::operator-(Matrix& matrix)
{
	return this->Subtruction(matrix);
}

Matrix& SparseMatrix::operator*(Matrix& matrix)
{
	return this->Multiplication(matrix);
}

Matrix& SparseMatrix::operator*(int constant)
{
	return this->Multiplication(constant);
}

bool SparseMatrix::operator==(Matrix& matrix)
{
	return this->Equal(matrix);
}

bool SparseMatrix::operator!=(Matrix& matrix)
{
	return !(this->Equal(matrix));
}