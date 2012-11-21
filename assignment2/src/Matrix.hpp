#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>

#include "Vector.hpp"

template<class T>
class Matrix
{
	template<class U>
	friend std::ostream& operator<<(std::ostream&, const Matrix<U>&);

protected:
	Vector<Vector<T> > data;

public:
	const static size_t DEFAULT_ROWS = 10;
	const static size_t DEFAULT_COLS = 10;

	Matrix(const size_t &rows = Matrix<T>::DEFAULT_ROWS, const size_t &cols = Matrix<T>::DEFAULT_COLS);

	const size_t& rows() const;
	const size_t& cols() const;

	void resize(const size_t &rows, const size_t &cols);

	Vector<T>& operator [](const size_t &row);
	const Vector<T>& operator [](const size_t &row) const;
};

#endif
