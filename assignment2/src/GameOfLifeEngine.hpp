#ifndef GAMEOFLIFEENGINE_HPP
#define GAMEOFLIFEENGINE_HPP

#include <cstdlib>
#include <utility>

#include "Matrix.hpp"

/* declaration */
class GameOfLifeEngine
{
public:
	const static size_t DEFAULT_ROWS;
	const static size_t DEFAULT_COLS;

	GameOfLifeEngine(const size_t &rows = GameOfLifeEngine::DEFAULT_ROWS, const size_t &cols = GameOfLifeEngine::DEFAULT_COLS);
	virtual ~GameOfLifeEngine();

	void clear();
	void random();
	void resize(const size_t &rows, const size_t &cols);
	void step();

	void toggle(const size_t &row, const size_t &col);

	const size_t &rows() const;
	const size_t &cols() const;

	const Vector<bool>& operator [](const size_t &row) const;

private:
	Matrix<bool> *front;
	Matrix<bool> *back;
};

#endif