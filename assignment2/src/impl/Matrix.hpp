#include "../Matrix.hpp"

template <class T>
Matrix<T>::Matrix(const size_t &rows, const size_t &cols)
{
	this->resize(rows, cols);
}

template <class T>
const size_t& Matrix<T>::rows() const
{
	return this->data.length();
}

template <class T>
const size_t& Matrix<T>::cols() const
{
	return this->data[0].length();
}

template <class T>
void Matrix<T>::resize(const size_t &rows, const size_t &cols)
{
	this->data.resize(rows);
	for (size_t i = 0; i < rows; i++)
		this->data[i].resize(cols);

}

template <class T>
Vector<T>& Matrix<T>::operator [](const size_t &row)
{
	assert(row < this->rows());
	return this->data[row];
}

template <class T>
const Vector<T>& Matrix<T>::operator [](const size_t &row) const
{
	assert(row < this->rows());
	return this->data[row];
}

template<class U>
std::ostream& operator << (std::ostream& out, const Matrix<U>& m)
{
	if (m.rows() > 0)
	{
		out << m.data[0];

		for (size_t i = 1; i < m.rows(); i++)
			out << "\n" << m.data[i];

	}

	return out;
}