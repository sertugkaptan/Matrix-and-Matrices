#pragma once

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
class Matrix
{
public:
	Matrix();
	virtual ~Matrix()=0;
	virtual void SetInt(int, int, int)=0;
	virtual int GetInt(int, int)=0;
	virtual void Resize(int,int)=0;
	virtual Matrix& Addition(Matrix&) = 0;
	virtual Matrix& Subtruction(Matrix&) = 0;
	virtual Matrix& Multiplication(Matrix&) = 0;
	virtual Matrix& Multiplication(int) = 0;
	virtual Matrix& Transpose() = 0;
	virtual bool Equal(Matrix&) = 0;
	virtual void printm()= 0;
	virtual Matrix& operator+(Matrix&) = 0;
	virtual Matrix& operator-(Matrix&) = 0;
	virtual Matrix& operator*(Matrix&) = 0;
	virtual Matrix& operator*(int) = 0;
	virtual bool operator==(Matrix&) = 0;
	virtual bool operator!=(Matrix&) = 0;
	friend std::ostream& operator<<(std::ostream&, Matrix&);
public:
	int rowsize;
	int	columnsize;
	int** arr;
};


#endif //!MATRIX_H,