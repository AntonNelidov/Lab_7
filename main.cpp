#include <iostream>

using namespace std;

class Matrix
{
	// ??????????
	// ????????????
	// ????????????? ??? ??????
public:
	// ???????????
	Matrix(int n, int m)
	{
		/*cout << "Constructor" << endl;*/
		m_n = n;
		m_m = m;
		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];
	}

	// ??????????? ???????????
	Matrix(const Matrix& mat)
	{
		/*cout << "Copy constructor" << endl;*/
		m_n = mat.m_n;
		m_m = mat.m_m;

		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];
	}

	// ??????????
	~Matrix()
	{
		/*cout << "Destructor" << endl;*/
		for (int i = 0; i < m_n; i++)
			delete[] m_mat[i];
		delete m_mat;
	}

	// ????????????
	Matrix& operator=(const Matrix& mat)
	{
		cout << "Operator =" << endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];

		return *this;
	}

	// ???????? ????????
	Matrix operator+(const Matrix& mat)
	{
		cout << "operator+" << endl;
		Matrix tmp(2, 3);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	// ???????? ????????  C += A <=> C = C + A
	Matrix operator+=(const Matrix& mat)
	{
		cout << "operator+=" << endl;
		Matrix tmp(2, 3);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	// ???????? ?????????
	Matrix operator-(const Matrix& mat)
	{
		cout << "operator-" << endl;
		Matrix tmp(2, 3);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}

	// ???????? ?????????
	Matrix operator*(const Matrix& mat)
	{
		cout << "operator*" << endl;
		Matrix tmp(m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = 0;
				for (int k = 0; k < m_m; k++)
				{
					tmp.m_mat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
				}
			}
		}
		return tmp;
	}
	

	int Determin()
	{

		if ((m_n == 2) && (m_m == 2))
		{
			return (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]);
		}
		else if ((m_n == 3) && (m_m == 3))
		{
			return (m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) - (m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2])) + (m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0])));
		}
		else
			cout <<endl<< "This operation doesn't work for this size!"<<endl;
	}

	Matrix Transposit()
	{
		
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = m_mat[j][i];
			}
		}
		return tmp;
	}

	Matrix Inverse()	
	{
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = 0;
			}
		}
		if ((m_n == 2 && m_m == 2) || (m_n == 3 && m_m == 3))
		{
			int det = Determin(); // ???????? ?? ??????????? ???????
			if (det == 0) {
				cout << endl << "Inverse matrix doesn't exist because of Det = 0" << endl;
				return tmp;
			}

			if (m_n == 2) {
				tmp.m_mat[0][0] = m_mat[1][1] / det;
				tmp.m_mat[0][1] = -m_mat[0][1] / det;
				tmp.m_mat[1][0] = -m_mat[1][0] / det;
				tmp.m_mat[1][1] = m_mat[0][0] / det;
				return tmp;
			}
			if (m_n == 3) {
				tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det;
				tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det;
				tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det;
				tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det;
				tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det;
				tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det;
				tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det;
				tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det;
				tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det;
				return tmp;
			}
		}
		else
			cout << endl << "This operation doesn't work for this size!" << endl;
	}

	// friend - ????????? ??????? ????? ?????? ? private ?????/??????? ??????
	friend istream& operator>>(istream& os, Matrix& mat);
	friend ostream& operator<<(ostream& os, const Matrix& mat);

	// ????????????? ?????? ??????
private:
	int m_n, m_m;		// ????
	//int n;
	int** m_mat; // Matrix
};

// ?????????? ????????? ?????
istream& operator>>(istream& in, Matrix& mat)
{
	for (int i = 0; i < mat.m_n; i++)
		for (int j = 0; j < mat.m_m; j++)
			in >> mat.m_mat[i][j];
	return in;
}

// ?????????? ????????? ??????
ostream& operator<<(ostream& out, const Matrix& mat)
{
	out << "Matrix " << mat.m_n << "x" << mat.m_m << endl;
	for (int i = 0; i < mat.m_n; i++) {
		for (int j = 0; j < mat.m_m; j++)
			out << mat.m_mat[i][j] << " ";
		out << endl;
	}
	return out;
}



int main()
{
	const int n_2 = 2; const int m_2 = 2;
	const int n_3 = 3; const int m_3 = 3;

	// // // // // // // // // // // // // // //

	Matrix A(n_2, m_2);

	cout << "Enter the A (2x2) matrix: " << endl;
	cin >> A;

	cout << A << endl;

	cout << endl << "Matrix determinant: " << endl;
	cout << A.Determin() << endl;

	cout << endl << "Matrix transposition: " << endl;
	cout << A.Transposit() << endl;

	cout << endl << "Inverse matrix: " << endl;
	cout << A.Inverse() << endl;

	// // // // // // // // // // // // // // //

	Matrix B(n_3, m_3);

	cout << "Enter the B (3x3) matrix: " << endl;
	cin >> B;

	cout << B << endl;

	cout << endl << "Matrix determinant: " << endl;
	cout << B.Determin() << endl;

	cout << endl << "Matrix transposition: " << endl;
	cout << B.Transposit() << endl;

	cout << endl << "Inverse matrix: " << endl;
	cout << B.Inverse() << endl;

	// // // // // // // // // // // // // // //

	return 0;
}