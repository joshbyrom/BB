#ifndef GRID_HPP
#define GRID_HPP

#include <functional>

namespace Space {
	template <typename T, int COLUMNS, int ROWS>
	class Grid {
		public:
			Grid();
			~Grid();

			T Get(int column, int row) const;

			void Init(std::function<T(int, int)> generator);

			int GetNumberOfColumns() { return COLUMNS; }
			int GetNumberOfRows() { return ROWS; }

		private:
			T * elems;

			int ToIndex(const int column, const int row) const { return column * ROWS + row; }
	};

	template <typename T, int COLUMNS, int ROWS>
	Grid<T, COLUMNS, ROWS>::Grid() 
		: elems(new T[COLUMNS * ROWS])
	{

	}

	template <typename T, int COLUMNS, int ROWS>
	Grid<T, COLUMNS, ROWS>::~Grid() 
	{
		delete [] elems;
		elems = NULL;
	}

	template <typename T, int COLUMNS, int ROWS>
	T Grid<T, COLUMNS, ROWS>::Get(int columns, int rows) const {
		int guardedColumn = columns%COLUMNS;
		int guardedRow = rows%ROWS;

		guardedColumn += guardedColumn < 0 ? COLUMNS : 0;
		guardedRow += guardedRow  < 0 ? ROWS : 0;

		int index = ToIndex(guardedColumn, guardedRow);
		return elems[index];
	}

	template <typename T, int COLUMNS, int ROWS>
	void Grid<T, COLUMNS, ROWS>::Init(std::function<T(int, int)> generator) {
		T result; int index;
		for(int c = 0; c < COLUMNS; ++c) {
			for(int r = 0; r < ROWS; ++r) {
				result = generator(c, r);

				index = ToIndex(c, r);
				elems[index] = result;
			}
		}
	}

};

#endif