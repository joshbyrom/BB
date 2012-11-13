#ifndef CELL_H
#define CELL_H

#include "../entities/Entity.hpp"
#include "../../headers/Vector2D.h"

#include <algorithm>

namespace Space {
	class Cell {
		public:
			Cell() 
				: column(0), row(0), width(0.), height(0.) {}
			Cell(int column, int row, double width, double height) 
				: column(column), row(row), width(width), height(height) {}
			Cell(const Cell& copy) {
				column = copy.column;
				row = copy.row;
				width = copy.width;
				height = copy.height;

				std::copy(copy.ents.begin(), copy.ents.end(), ents.begin());
			}

			~Cell() {}

			std::vector<AI::Entity> GetEntities() const { return ents; }

			void Add(const AI::Entity& e) { 
				ents.push_back(e); 
			}

			void Remove(const AI::Entity& e) {
				std::vector<AI::Entity> copy;
				for(UINT i = 0; i < ents.size(); ++i) {
					if(ents[i] == e) {
					} else {
						copy.push_back(ents[i]);
					}
				}

				ents = copy;
			}

			bool operator==(const Cell& rhs)const
			{
				return column == rhs.column &&
					   row == rhs.row &&
					   width == rhs.width &&
					   height == rhs.height;
			}

			bool operator!=(const Cell& rhs)const
			{
				return column != rhs.column &&
					   row != rhs.row &&
					   width != rhs.width &&
					   height != rhs.height;
			}
		private:
			std::vector<AI::Entity> ents;

			int column, row;
			double width, height;

	};
}

#endif
