#pragma once
#include "Matrix.h"
#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

class DenseMatrix : public Matrix
{
public:
	DenseMatrix();
	DenseMatrix(int, int, int**);
	DenseMatrix(int, int, int);
	DenseMatrix(Matrix&);
	~DenseMatrix();
	void SetInt(int, int, int)override;
	int GetInt(int, int)override;
	void Resize(int,int)override;
	Matrix& Addition(Matrix&) override;
	Matrix& Subtruction(Matrix&)override;
	Matrix& Multiplication(Matrix&) override;
	Matrix& Multiplication(int)override;
	Matrix& Transpose() override;
	bool Equal(Matrix&) override;
	void printm()override;
	Matrix& operator+(Matrix&)override;
	Matrix& operator-(Matrix&)override;
	Matrix& operator*(Matrix&)override;
	Matrix& operator*(int)override;
	bool operator==(Matrix&)override;
	bool operator!=(Matrix&)override;
	
};

#endif // !DENSEMATRIX_H