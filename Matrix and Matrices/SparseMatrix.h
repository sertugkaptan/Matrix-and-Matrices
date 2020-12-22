#pragma once
#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "Matrix.h"
#include <vector>

// we create a struct so we can store the location of the values
struct Cell
{
	int x, y, value;
	Cell(int x, int y, int val)
	{
		this->x = x;
		this->y = y;
		this->value = val;
	}
};

class SparseMatrix : public Matrix
{
public:
	// we create a vector so it will be easier to store cells as an array
	std::vector <Cell> cells;
	SparseMatrix();
	SparseMatrix(int, int, int**);
	SparseMatrix(Matrix&);
	~SparseMatrix();
	void SetInt(int, int, int)override;
	int GetInt(int, int)override;
	void Resize(int,int)override;
	Matrix& Addition(Matrix&)override;
	Matrix& Subtruction(Matrix&)override;
	Matrix& Multiplication(Matrix&)override;
	Matrix& Multiplication(int)override;
	Matrix& Transpose()override;
	bool Equal(Matrix&)override;
	void printm()override;
	Matrix& operator+(Matrix&)override;
	Matrix& operator-(Matrix&)override;
	Matrix& operator*(Matrix&)override;
	Matrix& operator*(int)override;
	bool operator==(Matrix&)override;
	bool operator!=(Matrix&)override;
};


#endif // !SPARSEMATRIX_H