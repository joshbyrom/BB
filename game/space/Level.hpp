#ifndef LEVEL_H
#define LEVEL_H


#include "../entities/Entity.hpp"
#include "Grid.hpp"
#include "Cell.h"

#include <functional>
#include <algorithm>
#include <string>

namespace Space {
	using Space::Grid;
	using Space::Cell;

	class Level {
	public:
		Level(std::string name, double width, double height)
			: width(width), height(height), grid(new Grid<Cell, 5, 5>()) {
				cellWidth = width / grid->GetNumberOfColumns();
				cellHeight = height / grid->GetNumberOfRows();
				grid->Init([&] (int column, int row) -> Cell {
					Cell cell(column, row, cellWidth, cellHeight);
					cells.push_back(cell);
					return cell;
				});
		}

		~Level() {

		}

		void AddEntityToLevel(AI::Entity& e) {
			e.GetUpdater().AddHook("KeepInCorrectCell", [&] () -> void {
				Cell cell = CellAtXY(e);
				
			});
		}

		void RemoveEntity(AI::Entity& e) {
			//e.GetCell().Remove(e);
			e.GetUpdater().RemoveHook("KeepInCorrectCell");
		}

		void Update() {
			MapToEntities([&] (AI::Entity& e) -> void {
				e.GetUpdater().Update();	
			});
		}

		void MapToCells(std::function<void(Cell& cell)> fun) {
			for_each(cells.begin(), cells.end(), fun);
		}

		void MapToEntities(std::function<void(AI::Entity& e)> fun) {
			MapToCells([&] (Cell& cell) -> void {
				for_each(cell.GetEntities().begin(), cell.GetEntities().end(), fun);
			});
		}

		Cell CellAtXY(const AI::Entity& entity) {
			Vector2D position = entity.GetPosition();
			return CellAtXY(position.x, position.y);
		}

		Cell CellAtXY(double x, double y) {
			int column = floor(x / cellWidth);
			int row = floor(y / cellHeight);
			return grid->Get(column, row);
		}

	private:
		double width;
		double height;

		double cellWidth, cellHeight;

		std::string name;

		std::vector<Cell> cells;
		Grid<Cell, 5, 5>  * grid;
	};
}

#endif
