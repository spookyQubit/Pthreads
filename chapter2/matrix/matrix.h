#ifndef INCLUDED_MATRIX
#define INCLUDED_MATRIX

#include <utility>

using namespace std;

class Matrix{

private:
	int d_numRows;
	int d_numCols;

	int** d_m;

public:

	// Ctr & Dstr
	Matrix(int nRows, int nCols, int dflt=0);
    ~Matrix();

    // Accessors
	void print() const;
	std::pair<int, int> shape() const;

	// Manipulators
	static void mult(Matrix* pt_res, 
		             const Matrix& ma, 
		             const Matrix& mb, 
		             const pair<int, int>& id);
	int* operator[](int row);
	const int* operator[](const int& row) const; 


};


#endif
