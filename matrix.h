#pragma once
using namespace std;
#define N 10

class matrix {

public:

	//to display any matrix
	void display(double[N][N], int, int);

	//to get ingredient to calculate inverse matrix
	void getCfactor(double[N][N], double[N][N], int, int, int);//used in DETfunction 
	double DET(double [N][N], int );//to find determinant  //used in bool INV
	void ADJ(double[N][N], double[N][N], int);//to find adjoint matrix //used in bool INV

	//to calculate inverse matrix
	bool INV(double[N][N], double[N][N], int);//check inverse existance, calculate inverse matrix

	//multiplication of matrix n*n and n*1
	void multiply(double [N][N], double [N][N], double [N][N], int , int );
	
};


void matrix::display(double mat[N][N], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << "  " << mat[i][j];
		cout << "\n";
	}
}

//get t[N][N], cofactor matrix obtained by eliminating row p and column q
void matrix::getCfactor(double M[N][N], double t[N][N], int p, int q, int n) {
	int i = 0, j = 0;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) //Copy only those elements which are not in given row r and column c: {
			if (r != p && c != q) {
				t[i][j++] = M[r][c]; //If row is filled increase r index and reset c index
				if (j == n - 1) {
					j = 0; i++;
				}
			}
	}
}


double matrix::DET(double M[N][N], int n) {
	double D = 0;
	if (n == 1)
		return M[0][0];
	double t[N][N]; //store cofactors
	int s = 1; //store sign multiplier 
	//To Iterate each element of first row
	for (int f = 0; f < n; f++) {
		//For Getting Cofactor of M[0][f] do 
		getCfactor(M, t, 0, f, n);
		D += s * M[0][f] * DET(t, n - 1);
		s = -s;
	}
	return D;
}


void matrix::ADJ(double M[N][N], double adj[N][N], int n) {
	double t[N][N];

	if (n == 1) {
		adj[0][0] = 1;
		return;
	}
	int s = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//To get cofactor of M[i][j]

			getCfactor(M, t, i, j, n);
			s = ((i + j) % 2 == 0) ? 1 : -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
			adj[j][i] = (s) * (DET(t, n - 1)); //Interchange rows and columns to get the transpose of the cofactor matrix
		}
	}
}


bool matrix::INV(double M[N][N], double inv[N][N], int n) {
	double det = DET(M, n);
	if (det == 0) {
		cout << "Cannot find its inverse\n";
		return false;
	}
	double adj[N][N]; 
	ADJ(M, adj, n);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) inv[i][j] = adj[i][j] / det;
	return true;
}


//S=first matrix or square matrix or inverse matrix, L=second matrix or column matrix, R=result matrix(to be filled)
void matrix::multiply(double S[N][N], double L[N][N], double R[N][N], int n , int col) {

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < col; j++)
		{
			R[i][j] = 0;//total before addition or result of 1 elemet
			for (int k = 0; k < n; k++)
			{
				R[i][j] += S[i][k] * L[k][j];
			}
		}
	}

}



