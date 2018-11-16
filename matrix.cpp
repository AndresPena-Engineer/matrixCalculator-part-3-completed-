// ANDRES PENA	
// 11.5.2018
// Lab 6

#include <algorithm> // provides min()
using namespace std;

#include "matrix.h"

Matrix::Matrix()
{
	width = 0;
	height = 0;
	values = nullptr;
}

Matrix::Matrix(int size) : Matrix(size, size)
{
	for (int s = 0; s < size; s++)
	{
		values[s][s] = 1;
	}
}

Matrix::Matrix(int height, int width) : Matrix()
{
	resize(height, width);
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : Matrix(other.height, other.width)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			values[h][w] = other(h, w);
		}
	}
}

// Move constructor
Matrix::Matrix(Matrix&& rhs)
{
	width = rhs.width;
	height = rhs.height;
	values = rhs.values;

	rhs.width = 0;
	rhs.height = 0;
	rhs.values = nullptr;
}

Matrix::~Matrix()
{
	if (values != nullptr)
	{
		for (int r = 0; r < height; r++)
		{
			delete[] values[r];
		}
		delete[] values;
	}
}

int Matrix::getWidth() const
{
	return width;
}

int Matrix::getHeight() const
{
	return height;
}

void Matrix::resize(int hei, int wid)
{
	double** tmpValues = values;

	values = new double*[hei];
	for (int h = 0; h < hei; h++)
	{
		values[h] = new double[wid];
		for (int w = 0; w < wid; w++)
		{
			values[h][w] = 0.0;
		}
	}

	for (int h = 0; h < min(hei, height); h++)
	{
		for (int w = 0; w < min(wid, width); w++)
		{
			values[h][w] = tmpValues[h][w];
		}
	}

	for (int h = 0; h < height; h++)
	{
		delete[] tmpValues[h];
	}
	delete[] tmpValues;

	width = wid;
	height = hei;

}

void Matrix::transpose()
{
	double** tmpValues = values;

	values = new double*[width];
	for (int w = 0; w < width; w++)
	{
		values[w] = new double[height];
		for (int h = 0; h < height; h++)
		{
			values[w][h] = tmpValues[h][w];
		}
	}

	for (int h = 0; h < height; h++)
	{
		delete[] tmpValues[h];
	}
	delete[] tmpValues;

	int tmp = height;
	height = width;
	width = tmp;

}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& rhs)
{
	resize(rhs.height, rhs.width);

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			values[h][w] = rhs(h, w);
		}
	}

	return *this;
}

// Move assignment
Matrix& Matrix::operator=(Matrix&& rhs)
{
	if (values != nullptr)
	{
		for (int r = 0; r < height; r++)
		{
			delete[] values[r];
		}

		delete[] values;
	}

	width = rhs.width;
	height = rhs.height;
	values = rhs.values;

	rhs.width = 0;
	rhs.height = 0;
	rhs.values = nullptr;

	return *this;
}

double& Matrix::operator()(int row, int col)
{
	return values[row][col];
}

double Matrix::operator()(int row, int col) const
{
	return values[row][col];
}

//---------------------------------------TEST------------------------------------------//

/****************************************************
Creates a new matrix which is the sum of this and another given matrix.
This does not change the current matrix.If the size ob both matrices is not matching,
the resulting matrix has the dimensions of the largest intersection of both given matrices.
******************************************************/
Matrix Matrix::operator+(const Matrix& M) const
{
	int minHeight = min(this->height, M.getHeight());

	int minWidth = min(this->width, M.getWidth());

	Matrix newMatrix = Matrix(minHeight, minWidth);
	
	for (int i = 0; i < minHeight; i++)
		{
			for (int j = 0; j < minWidth; j++)
			{
				newMatrix.values[i][j] = this->values[i][j] + M.values[i][j];
			}
		}
		return newMatrix;
}

//---------------------------------------TEST------------------------------------------//

/****************************************************
Adds a given matrix to the current. Note that it changes the matrix and does not create a copy.
If the size ob both matrices is not matching, it changes the dimensions of the current matrix
to the largest intersection of both matrices.
******************************************************/
Matrix& Matrix::operator+=(const Matrix& M)
{
	
	int minHeight = min(this->height, M.getHeight());

	int minWidth = min(this->width, M.getWidth());

	Matrix tmp (minHeight, minWidth);


	for (int i = 0; i < minHeight; i++)
	{
		for (int j = 0; j < minWidth; j++)
		{
			this->values[i][j] += M.values[i][j];
		}
	}
	return *this;

}

//---------------------------------------TEST------------------------------------------//

/****************************************************
Creates a new matrix which is the product of this and another given matrix.
This does not change the current matrix. If the size ob both matrices is not matching,
it uses the largest sub-matrices which work (the top left element is always included).
Note that matrix multiplication is not a symmetric operation, i. e., in general for two matrices A and B,
AB ̸= BA. When multiplying two matrices, the *-operator of the left matrix is called.
******************************************************/
Matrix Matrix::operator*(const Matrix& M) const
{	
	double resultOfMatrix = 0.0; 

		Matrix anwserForMatrix(M.height, this->width);
			anwserForMatrix.height = M.height;
			anwserForMatrix.width = this->width;


				for (int i = 0; i < M.height; i++)
				{

					for (int j = 0; j < M.width; j++)
					{
						for (int k = 0; k < this->width; k++)
						{
							for (int l = 0; l < this->height; l++) 
							{

								double Matrix1 = values[l][k];
								double Matrix2 = M.values[i][j];
								resultOfMatrix += Matrix1 * Matrix2;
							}

							anwserForMatrix.values[i][k] = resultOfMatrix;
							resultOfMatrix = 0.0;
						}
					}
					return anwserForMatrix;
			}
		
}

//---------------------------------------TEST------------------------------------------//

/****************************************************
Multiplies a given matrix with the current. Note that it changes the matrix
and does not create a copy. If the size ob both matrices is not matching, it uses the largest sub-matrices which
work (the top left element is always included).
Note that matrix multiplication is not a symmetric operation, i. e., in general for two matrices A and B,
AB ̸= BA. When multiplying two matrices, the *-operator of the left matrix is called.
******************************************************/
Matrix& Matrix::operator*=(const Matrix& M)
{
	*this = *this * M;
	return *this;

}

/****************************************************
Creates a new matrix which is the product of this matrix and a given number.
This does not change the current matrix.
*********************WRONG*********************************/
Matrix Matrix::operator*(double scalar) const
{
	
		Matrix temp(height, width);
		for (int i = 0; i < height; i++) {
	
			for (int j = 0; j < width; j++	){
				temp.values[i][j] = values[i][j] * scalar; 
			}
		}
	return temp;
}

/****************************************************
Multiplies the current with a given number. Note that it changes the matrix
and does not create a copy.
***********************WRONG*******************************/
Matrix& Matrix::operator*=(double num)
{
	for (int i = 0; i < height; i++) 
		for (int j = 0; j < width; j++) 
			this->values[i][j] *= num;
	return (*this);
}



bool Matrix::operator==(const Matrix& matrix) const
{
	if (width != matrix.width) return false;
	if (height != matrix.height) return false;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (values[h][w] != matrix.values[h][w]) return false;
		}
	}
	return true;
}
