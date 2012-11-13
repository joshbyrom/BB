#ifndef GRID_HPP
#define GRID_HPP

#include <functional>

namespace Space {
	template <typename T>
	class Grid {
		public:
			Grid(UINT c, UINT r);
			Grid(const Grid& copy);

			~Grid();

			T Get(int column, int row) const;

			void Init(std::function<T(UINT, UINT)> generator);

			UINT GetNumberOfColumns() { return columns; }
			UINT GetNumberOfRows() { return rows; }

		private:
			T * elems;
			UINT columns, rows;

			UINT ToIndex(const int column, const int row) const { return column * rows + row; }
	};

	template <typename T>
	Grid<T>::Grid(UINT c, UINT r) 
		: elems(new T[c * r]), columns(c), rows(r)
	{

	}

	template <typename T>
	Grid<T>::Grid(const Grid<T>& copy)  {
		elems = new T[copy.columns * copy.rows];

		columns = copy.columns;
		rows = copy.rows;

		this->Init([&] (UINT column, UINT row) -> T {
			return copy.Get(column, row);
		});
	}

	template <typename T>
	Grid<T>::~Grid() 
	{
		delete [] elems;
		elems = NULL;
	}

	template <typename T>
	T Grid<T>::Get(int column, int row) const {
		int guardedColumn = column%columns;
		int guardedRow = row%rows;

		guardedColumn += guardedColumn < 0 ? columns : 0;
		guardedRow += guardedRow  < 0 ? rows : 0;

		UINT index = ToIndex(guardedColumn, guardedRow);
		return elems[index];
	}

	template <typename T>
	void Grid<T>::Init(std::function<T(UINT, UINT)> generator) {
		T result; UINT index;
		for(UINT c = 0; c < columns; ++c) {
			for(UINT r = 0; r < rows; ++r) {
				result = generator(c, r);

				index = ToIndex(c, r);
				elems[index] = result;
			}
		}
	}

};

#endif