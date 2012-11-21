#include "../GameOfLifeEngine.hpp"

const size_t GameOfLifeEngine::DEFAULT_ROWS = 50;
const size_t GameOfLifeEngine::DEFAULT_COLS = 50;

GameOfLifeEngine::GameOfLifeEngine(const size_t &rows, const size_t &cols)
{
	this->front = new Matrix<bool>(rows, cols);
	this->back = new Matrix<bool>(rows, cols);

	this->clear();
}

GameOfLifeEngine::~GameOfLifeEngine()
{
	delete this->front;
	delete this->back;
}

void GameOfLifeEngine::clear()
{
	for (size_t i = 0; i < this->front->rows(); i++)
		for (size_t j = 0; j < this->front->cols(); j++)
			(*this->front)[i][j] = false;

}

void GameOfLifeEngine::random()
{
	for (size_t i = 0; i < this->front->rows(); i++)
		for (size_t j = 0; j < this->front->cols(); j++)
			(*this->front)[i][j] = rand() & 1;

}

void GameOfLifeEngine::resize(const size_t &rows, const size_t &cols)
{
	this->front->resize(rows, cols);
	this->back->resize(rows, cols);

	this->clear();
}

void GameOfLifeEngine::step()
{
	for (size_t i = 0; i < this->rows(); i++)
	{
		for (size_t j = 0; j < this->cols(); j++)
		{
			unsigned int neighbours = 0;

			if (i > 0)
			{
				if (j > 0)
					neighbours += (unsigned int) (*this)[i - 1][j - 1];

				neighbours += (unsigned int) (*this)[i - 1][j];

				if (j < this->cols() - 1)
					neighbours += (unsigned int) (*this)[i - 1][j + 1];

			}

			if (j > 0)
				neighbours += (unsigned int) (*this)[i][j - 1];

			if (j < this->cols() - 1)
				neighbours += (unsigned int) (*this)[i][j + 1];

			if (i < this->rows() - 1)
			{
				if (j > 0)
					neighbours += (unsigned int) (*this)[i + 1][j - 1];

				neighbours += (unsigned int) (*this)[i + 1][j];

				if (j < this->cols() - 1)
					neighbours += (unsigned int) (*this)[i + 1][j + 1];

			}

			if (neighbours == 2)
				(*this->back)[i][j] = (*this)[i][j];

			else if (neighbours == 3)
				(*this->back)[i][j] = true;

			else
				(*this->back)[i][j] = false;

		}
	}

	std::swap(this->front, this->back);
}

void GameOfLifeEngine::toggle(const size_t &row, const size_t &col)
{
	(*this->front)[row][col] = !(*this->front)[row][col];
}

const size_t& GameOfLifeEngine::rows() const
{
	return this->front->rows();
}

const size_t& GameOfLifeEngine::cols() const
{
	return this->front->cols();
}

const Vector<bool>& GameOfLifeEngine::operator [](const size_t &row) const
{
	return (*this->front)[row];
}
