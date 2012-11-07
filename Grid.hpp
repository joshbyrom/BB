#include <functional>

namespace AI {
	template <typename T, int COLUMNS, int ROWS>
	class Grid {
		public:
			Grid();
			~Grid();

			T get(int column, int row) const;

			void init(std::function<T(int, int)> generator);

			int get_number_of_columns() { return COLUMNS; }
			int get_number_of_rows() { return ROWS; }

		private:
			T * elems;

			int to_index(const int column, const int row) const { return column * ROWS + row; }
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
	T Grid<T, COLUMNS, ROWS>::get(int columns, int rows) const {
		int guarded_column = columns%COLUMNS;
		int guarded_row = rows%ROWS;

		guarded_column += guarded_column < 0 ? COLUMNS : 0;
		guarded_row += guarded_row  < 0 ? ROWS : 0;

		int index = to_index(guarded_column, guarded_row);
		return elems[index];
	}

	template <typename T, int COLUMNS, int ROWS>
	void Grid<T, COLUMNS, ROWS>::init(std::function<T(int, int)> generator) {
		T result; int index;
		for(int c = 0; c < COLUMNS; ++c) {
			for(int r = 0; r < ROWS; ++r) {
				result = generator(c, r);

				index = to_index(c, r);
				elems[index] = result;
			}
		}
	}

};