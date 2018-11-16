#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

using namespace std;

void printSize(const Matrix &m)
{
	cout << "width: " << m.getWidth()
		<< "  |  height: " << m.getHeight()
		<< endl;
}

void printMatrix(const Matrix &m)
{
	for (int h = 0; h < m.getHeight(); h++)
	{
		for (int w = 0; w < m.getWidth(); w++)
		{
			cout << m(h, w) << " ";
		}
		cout << endl;
	}
}

Matrix getRndMatrix()
{
	int height = rand() % 5 + 1;
	int width = rand() % 5 + 1;
	Matrix m(height, width);
	for (int h = 0; h < m.getHeight(); h++)
	{
		for (int w = 0; w < m.getWidth(); w++)
		{
			m(h, w) = rand() % 5;
		}
	}

	return m;
}

int main()
{
	srand(time(NULL));

	{
		cout << "---------------\n";
		cout << "Addition\n";

		Matrix m1 = getRndMatrix();
		Matrix m2 = getRndMatrix();

		Matrix sum = m1 + m2;

		printMatrix(m1);
		cout << "- - - -\n";
		printMatrix(m2);

		cout << "- - - -\n";
		cout << "+: \n";
		printMatrix(sum);

		cout << "- - - -\n";
		cout << "+=: \n";
		m1 += m2;
		printMatrix(m1); 
	}

	{
		cout << "---------------\n";
		cout << "Multiplication (Matrix)\n";

		Matrix m1 = getRndMatrix();
		Matrix m2 = getRndMatrix();

		Matrix prod = m1 * m2;

		printMatrix(m1);
		cout << "- - - -\n";
		printMatrix(m2);

		cout << "- - - -\n";
		cout << "*: \n";
		printMatrix(prod);

		cout << "- - - -\n";
		cout << "*=: \n";
		m1 *= m2;
		printMatrix(m1);
	}

	{
		cout << "---------------\n";
		cout << "Multiplication (double)\n";

		Matrix m1 = getRndMatrix();
		double d1 = (double)(rand() % 5);
		double d2 = (double)(rand() % 5);

		Matrix prod = m1 * d1;

		printMatrix(m1);
		cout << "- - - -\n";
		cout << "* " << d1 << ":\n";
		printMatrix(prod);

		cout << "- - - -\n";
		cout << "*= " << d2 << ":\n";
		m1 *= d2;
		printMatrix(m1);
	}
	system("pause");
	return 0;
}
