#include "matrix.h"
#include <iostream>
#include <utility>
#include <assert.h>

using namespace std;

Matrix::Matrix(int nRows, int nCols, int dflt)
    : d_numRows(nRows), 
      d_numCols(nCols)
{
	
	// Allocate memory to hold matrix entries
	d_m = (int**)malloc(d_numRows * sizeof(int*));
	if(d_m == NULL){
		std::cout << "Not enough memory" << std::endl;
	}

	for(int i=0; i<d_numRows; ++i){
		d_m[i] = (int*)malloc(d_numCols * sizeof(int));
		if(d_m[i] == NULL){
			std::cout << "Not enough memory" << std::endl;
		}
	}

	for(int i=0; i<d_numRows; ++i){
		for(int j=0; j<d_numCols; ++j){
			d_m[i][j] = dflt;
		}
	}

}


Matrix::~Matrix()
{
	for(int i=0; i<d_numRows; ++i){
		free(d_m[i]);
	}

	free(d_m);
}

void Matrix::print() const
{
	cout << "in print" << endl;

	for(int i=0; i<d_numRows; ++i){
		for(int j=0; j<d_numCols; ++j){
			cout << d_m[i][j] << ", ";
		}
		cout << endl;
	}
}

pair<int, int> Matrix::shape() const
{
	pair<int, int> s = make_pair(d_numRows, d_numCols);
	return s;
}

int * Matrix::operator[](int row)
{
	return d_m[row];
}

const int* Matrix::operator[](const int& row) const
{
	return d_m[row];
}

void Matrix::mult(Matrix* pt_res, 
	              const Matrix& ma, 
	              const Matrix& mb, 
	              const pair<int, int>& id)
{
	assert(pt_res != NULL);
	Matrix& res = *pt_res;

	pair<int, int> shape_a = ma.shape();
	pair<int, int> shape_b = mb.shape();
	assert(shape_a.second == shape_b.first);

	int mul_res = 0;
	for(int i=0; i<shape_a.second; ++i){
		mul_res += ma[id.first][i] * mb[i][id.second];
	}

	res[id.first][id.second] = mul_res;

	return;
}