#include<iostream>
#include<string>
#include<cassert>
using namespace std;
class CMatrix
{
private:
	double** _A;
	int _row, _column;
public://构造函数
	CMatrix(void) :_A(NULL), _row(-1), _column(-1) {}
	CMatrix(int row, int column);
	CMatrix(const CMatrix& m);
	~CMatrix();
public://运算符
	CMatrix& operator =(const CMatrix& m);
	bool operator==(const CMatrix& m);
	bool operator!=(const CMatrix& m);
	CMatrix operator+(const CMatrix& m);
	CMatrix operator-(const CMatrix& m);
	CMatrix operator+=(const CMatrix& m);
	CMatrix operator-=(const CMatrix& m);
	double*& operator[](int row)
	{
		assert(row < _row);
		return _A[row];
	}
	CMatrix operator-();//取负数
	CMatrix operator*(const CMatrix& m);
	CMatrix operator*(const double& s);
	friend std::ostream& operator<<(std::ostream& os, CMatrix& m);
public://属性变量
	void setValue(int row, int column, double value) { _A[row][column] = value; }
	double getValue(int row, int column)const { return _A[row][column]; }
	void setRow(const int row) { _row = row; }
	int getRow()const { return _row; }
	void setColumn(const int column) { _column = column; }
	int getColumn()const { return _column; }
	bool setUnitMartix();//设置单位矩阵
public:
	CMatrix transpose();//矩阵转置
	CMatrix inverse();//列主元素法矩阵求逆
};
std::ostream& operator<<(std::ostream& os, CMatrix& m)
{
	for (int i = 0; i < m.getRow(); ++i)
	{
		for (int j = 0; j < m.getColumn(); ++j)
		{
			if (j == 0)
				os << m.getValue(i, j);
			else
				os << " " << m.getValue(i, j);
		}
		os << endl;
	}
	return os;
}
CMatrix::CMatrix(int row, int column)
{
	_row = row;
	_column = column;
	_A = new double* [row];
	for (int i = 0; i < row; i++)
		_A[i] = new double[column];
	//全部置零
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			_A[i][j] = 0.0f;
}
CMatrix::CMatrix(const CMatrix& m)
{
	_row = m._row;
	_column = m._column;
	_A = new double* [_row];
	for (int i = 0; i < _row; i++)
		_A[i] = new double[_column];
	
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
			_A[i][j] = m._A[i][j];
}
CMatrix::~CMatrix()
{
	if (_A != NULL)
	{
		for (int i = 0; i < _row; i++)
			delete[]_A[i];
	}
	if (_A != NULL)
		delete[]_A;
}
CMatrix& CMatrix::operator=(const CMatrix& m)
{
	if (&m == this)
		return*this;
	if (NULL != _A)
	{
		for (int i = 0; i < _row; i++)
			delete[]_A[i];
		delete[]_A;
	}
	_row = m._row;
	_column = m._column;
	_A = new double* [_row];
	for (int i = 0; i < _row; i++)
		_A[i] = new double[_column];

	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
			_A[i][j] = m._A[i][j];
	return *this;
}
bool CMatrix::setUnitMartix()//设置单位矩阵
{
	if (_row != _column)
		return false;
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
		{
			if (i == j)_A[i][j] = 1;
			else _A[i][j] = 0;
		}
	return true;
}
bool CMatrix::operator==(const CMatrix& m)
{
	if ((_row != m.getRow()) || (_column != m.getColumn()))return false;
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
		{
			if (fabs(_A[i][j] - m.getValue(i, j)) > 10e-6)return false;
		}
	return true;
}
bool CMatrix::operator!=(const CMatrix& m)
{
	if ((_row != m.getRow()) || (_column != m.getColumn()))return true;
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
		{
			if (fabs(_A[i][j] - m.getValue(i, j)) > 10e-6)continue;
			else return true;
		}
	return false;
}
CMatrix CMatrix:: operator+(const CMatrix& m)
{
	assert(_row == m.getRow() && _column == m.getColumn());
	CMatrix result(_row, _column);
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
			result.setValue(i, j, _A[i][j] + m.getValue(i, j));
	return result;
}
CMatrix CMatrix:: operator-(const CMatrix& m)
{
	assert(_row == m.getRow() && _column == m.getColumn());
	CMatrix result(_row, _column);
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
			result.setValue(i, j, _A[i][j] - m.getValue(i, j));
	return result;
}
CMatrix CMatrix:: operator+=(const CMatrix& m)
{
	assert(_row == m.getRow() && _column == m.getColumn());
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
			 _A[i][j] += m.getValue(i, j);
	return *this;
}
CMatrix CMatrix:: operator-=(const CMatrix& m)
{
	assert(_row == m.getRow() && _column == m.getColumn());
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
			_A[i][j] -= m.getValue(i, j);
	return *this;
}
CMatrix CMatrix:: operator*(const CMatrix& m)
{
	assert(_row == m.getColumn());
	CMatrix result(_row, m.getColumn());
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < m.getColumn(); j++)
		{
			double value = -0.0f;
			for (int k = 0; k < m.getColumn(); k++)
			{
				double kksk = m.getValue(k, j);
				kksk = kksk * _A[i][k];
				value = value + kksk;
			}
			result.setValue(i, j, value);
		}
	return *this;
}
CMatrix CMatrix:: operator*(const double& s)
{
	CMatrix result(_row, _column);
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
		{
			result.setValue(i, j, getValue(i,j)*s);
		}
	return result;
}
CMatrix CMatrix:: operator-()
{
	CMatrix result(_row, _column);
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
		{
			result.setValue(i, j, -_A[i][j]);
		}
	return result;
}
CMatrix CMatrix::transpose()
{
	CMatrix result(_row, _column);
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _column; j++)
		{
			result.setValue(i,j, getValue(j, i));
		}
	return result;
}
CMatrix CMatrix::inverse()
{
	assert(_row == _column);
	CMatrix NXW(_row, _row * 2);
	for (int i = 0; i < _row; i++)
		for (int j = 0; j < _row * 2; j++)
		{
			if (j < _row)NXW.setValue(j, i, getValue(i, j));
			else
			{
				if (i == (j - _row))NXW.setValue(i, j, 1.0f);
				else NXW.setValue(i, j, 0.0f);
			}
		}
	long kindex;//存储列主元所在的位置（行）
	double mk;//列主元值
	double aiitem;//临时储存的最大值
	for (int i = 0; i < _row; i++)
	{
		//选取列主元
		mk = NXW.getValue(i, i);
		kindex = -1;
		for (int j = i + 1; j < _row; j++)
		{
			if (fabs(NXW.getValue(j, i)) > fabs(mk))
			{
				mk = NXW.getValue(j, i);
				kindex = j;
			}
		}
		//列主元选取完成，交换行
		if (kindex != -1)
			for (int k = 0; k < _row * 2; k++)
			{
				aiitem = NXW.getValue(i, k);
				NXW.setValue(i, k, NXW.getValue(kindex, k));
				NXW.setValue(kindex, k, aiitem);
			}
		//交换完成，消去
		for (int k = 0; k < _row * 2; k++)
			NXW.setValue(i, k, NXW.getValue(i, k) / mk);//先置当前行的列主元为1.0
		for (int k = 0; k < _row; k++)
		{
			if (k == i)continue;
			double tem = NXW.getValue(k, i);
			for (int l = 0; l < _row * 2; l++)
				NXW.setValue(k, l, NXW.getValue(k, l) - tem * NXW.getValue(i, l));
		}
	}
		CMatrix result(_row, _row);
		for (int i = 0; i < _row; i++)
			for (int j = 0; j < _row; j++)
			{
				result.setValue(i, j, NXW.getValue(i,j+_row));
			}
	return result;
}

