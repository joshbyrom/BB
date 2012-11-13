#ifndef LEVEL_H
#define LEVEL_H


#include "../../headers/Vector2D.h"
#include "../space/Bounds.hpp"
#include "../entities/Entity.hpp"
#include "Grid.hpp"
#include "Cell.h"

#include "../../headers/constants.h"

#include <functional>
#include <algorithm>
#include <string>

namespace Space {
	using Space::Grid;
	using Space::Cell;
	using Space::Bounds;

	class Level {
	public:
		Level(std::string name, double width, double height)
			: width(width), height(height), 
			  grid(new Grid<Cell> (GRID_COLUMNS, GRID_ROWS)),
		      position(Vector2D()), bounds(new Bounds<Vector2D>()){
				cellWidth = width / grid->GetNumberOfColumns();
				cellHeight = height / grid->GetNumberOfRows();
				grid->Init([&] (int column, int row) -> Cell {
					Cell cell(column, row, cellWidth, cellHeight);
					cells.push_back(cell);
					return cell;
				});
		}

		Level(std::string name, double x, double y, double width, double height)
			: width(width), height(height), 
			  grid(new Grid<Cell> (GRID_COLUMNS, GRID_ROWS)),
		      position(Vector2D(x, y)), bounds(new Bounds<Vector2D>()){
				cellWidth = width / grid->GetNumberOfColumns();
				cellHeight = height / grid->GetNumberOfRows();
				grid->Init([&] (int column, int row) -> Cell {
					Cell cell(column, row, cellWidth, cellHeight);
					cells.push_back(cell);
					return cell;
				});
		}
		~Level() {
			delete grid;
			delete bounds;
		}

		void AddEntityToLevel(AI::Entity& e) {
			Cell cell = CellAtXY(e);
			cell.Add(e);
		}

		void RemoveEntity(AI::Entity& e) {
			Cell cell = CellAtXY(e);
			cell.Remove(e);
		}

		void Update() {
			bounds->Update(position, width, height);

			MapToEntities([&] (Cell * cell, AI::Entity * e) -> void {
				Cell old = CellAtXY(*e);
				e->GetUpdater().Update();
				Cell current = CellAtXY(*e);

				if(old != current) {
					old.Remove(*e);
					current.Add(*e);
				}
			});
		}

		void Pause() {
			MapToEntities([&] (Cell * cell, AI::Entity * e) -> void {
				e->GetUpdater().Pause();
			});
		}

		void Resume() {
			MapToEntities([&] (Cell * cell, AI::Entity * e) -> void {
				e->GetUpdater().Resume();
			});
		}

		void MapToEntities(std::function<void(Cell * cell, AI::Entity * e)> fun) {
			std::vector<AI::Entity> entities;
			for_each(cells.begin(), cells.end(), [&] (Cell& cell) -> void {
				entities = cell.GetEntities();
				for_each(entities.begin(), entities.end(),
					[&] (AI::Entity& e) ->void {
						fun(&cell, &e);
				});
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

		Grid<Cell> * GetGrid() { return grid; }
		Vector2D GetPosition() const { return position; }

		Bounds<Vector2D> * GetBounds() { return bounds; }
	private:
		Vector2D position;

		double width;
		double height;

		double cellWidth, cellHeight;

		std::string name;

		std::vector<Cell> cells;

		Grid<Cell>  * grid;
		Bounds<Vector2D>  * bounds;
	};
}

#endif
