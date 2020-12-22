#include "Matrix.h"

Matrix::Matrix()
{
	rowsize = 0;
	columnsize = 0;
}

Matrix::~Matrix()
{
	
}

std::ostream& operator<<(std::ostream& out,Matrix& m1)
{
	for (int i = 0; i < m1.rowsize; i++)
	{
		for (int j = 0; j < m1.columnsize; j++)
			out  << m1.GetInt(i,j);
		out << "\n";
	}
	return out;
}
