#include "DenseMatrix.h"
#include "SparseMatrix.h"
DenseMatrix::DenseMatrix()
{
	rowsize = 0;
	columnsize = 0;
}

DenseMatrix::DenseMatrix(int row,int column,int** matrix)
{
	rowsize = row;
	columnsize = column;
	arr = new int* [rowsize];
	for (int i = 0; i < rowsize; i++)
	{
		arr[i] = new int[columnsize];
	}
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < columnsize; j++)
			arr[i][j] = matrix[i][j];
}

DenseMatrix::DenseMatrix(int row, int column, int key)
{
	rowsize = row;
	columnsize = column;
	arr = new int* [rowsize];
	for (int i = 0; i < rowsize; i++)
	{
		arr[i] = new int[columnsize];
	}
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < columnsize; j++)
			arr[i][j] = key;
}

DenseMatrix::DenseMatrix(Matrix& matrix)
{
	//we set rowsize and columnsize
	rowsize = matrix.rowsize;
	columnsize = matrix.columnsize;
	//then we initialize as much place as necesarry
	arr = new int* [rowsize];
	for (int i = 0; i < columnsize; i++)
	{
		arr[i] = new int[columnsize];
	}
	//and then store each value in the parameter into our matrix
	for (int i = 0; i < rowsize; i++)
	{
		for (int j = 0; j < columnsize; j++)
			arr[i][j] = matrix.GetInt(i,j);
	}
}

DenseMatrix::~DenseMatrix()
{
}

void DenseMatrix::SetInt(int row, int column, int val)
{
	//find the location and put the value in there
	arr[row][column] = val;
}

int DenseMatrix::GetInt(int row, int column)
{
	//we return the value in that location
	if (row > rowsize || column > columnsize)
		return 0;

	return arr[row][column];
}

void DenseMatrix::Resize(int row, int column)
{
	//we create a temporary 2d array 
	int** matrix;
	//we initialize it
	matrix = new int* [column];
	for (int i = 0; i < row; i++)
		matrix[i] = new int[column];
	//and then we store each data in the old matrix
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i >= this->rowsize || j >= this->columnsize)
			{
				matrix[i][j] = 0;
			}
			else
				matrix[i][j] = arr[i][j];
		}
	}
	//set them as our new values
	rowsize = row;
	columnsize = column;
	arr = matrix;
}

Matrix& DenseMatrix::Addition(Matrix& matrix)
{
	//we make a temporary m2 to store values in
	DenseMatrix* m2 = new DenseMatrix(matrix);
	for (int i = 0; i < matrix.rowsize; i++)
		for (int j = 0; j < matrix.columnsize; j++)
			//add each value to new matrix
			m2->arr[i][j] = arr[i][j] + matrix.GetInt(i,j);
	return *m2;
}

Matrix& DenseMatrix::Subtruction(Matrix& matrix)
{
	//iterate and subtract each value from the array
	DenseMatrix* m2 = new DenseMatrix(matrix);
	for (int i = 0; i < matrix.rowsize; i++)
		for (int j = 0; j < matrix.columnsize; j++)
			m2->arr[i][j] = arr[i][j] - matrix.GetInt(i, j);
	return *m2;
}

Matrix& DenseMatrix::Multiplication(Matrix& matrix)
{
	//we alocate memory as big  as first matrix rowsize and second matrix columnsize
	DenseMatrix* m1 = new DenseMatrix(this->rowsize, matrix.columnsize, 0);
	//we calculate the value for the location and store it in the temporary matrix
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < matrix.columnsize; j++)
		{
			m1->arr[i][j] = 0;
			for (int k = 0; k < columnsize; k++)
				m1->arr[i][j] = m1->GetInt(i, j) + (GetInt(i, k) * matrix.GetInt(k,j));
		}
	return *m1;
}

Matrix& DenseMatrix::Transpose()
{
	//we make a temporary matrix
	int** matrix;
	//we initialize it
	matrix = new int* [columnsize];
	for (int i = 0; i <= rowsize; i++)
	{
		matrix[i] = new int[columnsize];
	}
	//then we store each value in the matrix
	for (int i = 0; i < columnsize; i++)
		for (int j = 0; j < rowsize; j++)
			matrix[i][j] = this->arr[j][i];
	//swap columns with rows
	int temp = columnsize;
	columnsize = rowsize;
	rowsize = temp;
	//and then point to the new matrix
	arr = matrix;
	return *this;
}

bool DenseMatrix::Equal(Matrix& matrix)
{
	//we check the size if they are equal
	if ((matrix.rowsize * matrix.columnsize) != (this->rowsize * this->columnsize))
		return false;
	else
		//if they are equal we iterate and check each value
		for (int i = 0; i < rowsize; i++)
			for (int j = 0; j < columnsize; j++)
				if (this->GetInt(i, j) != matrix.GetInt(i, j))
					return false;
	return true;
}

Matrix& DenseMatrix::Multiplication(int constant)
{
	//we make a temporary value
	DenseMatrix m1(*this);
	int count = 0;
	for (int i = 0; i < rowsize; i++)
		for (int j = 0; j < columnsize; j++)
		{
			//we multiply each value with the constant
			m1.arr[i][j] = this->GetInt(i, j) * constant;
			//we count the zeros
			if (m1.arr[i][j] == 0)
				count++;
		}
	//depending on the counter we return sparse or dense matrix
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

Matrix& DenseMatrix::operator+(Matrix& matrix)
{
	return this->Addition(matrix);
}

Matrix& DenseMatrix::operator-(Matrix& matrix)
{
	return this->Subtruction(matrix);
}

Matrix& DenseMatrix::operator*(Matrix& matrix)
{
	return this->Multiplication(matrix);
}

Matrix& DenseMatrix::operator*(int constant)
{
	return this->Multiplication(constant);
}

bool DenseMatrix::operator==(Matrix& matrix)
{
	return this->Equal(matrix);
}

bool DenseMatrix::operator!=(Matrix& matrix)
{
	return !(this->Equal(matrix));
}

void DenseMatrix::printm()
{
	for (int i = 0; i < rowsize; i++)
	{
		for (int j = 0; j < columnsize; j++)
			std::cout << std::setw(5) << arr[i][j];
		std::cout << "\n";
	}
}