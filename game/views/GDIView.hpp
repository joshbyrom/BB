#ifndef GDI_VIEW_HPP
#define GDI_VIEW_HPP

#include "../Game.hpp"
#include "../entities/Entity.hpp"
#include "../space/Cell.h"
#include "../space/Level.hpp"

#include "../../headers/Cgdi.h"
#include "../../headers/Vector2D.h"
#include "view.hpp"

#include <Windows.h>

namespace Views {
	using Space::Cell;
	using Space::Level;
	using Space::Grid;

	using AI::Entity;
	class GDIView : public View<HDC, HBITMAP, Vector2D> {
		public:
			GDIView(Game::Game& game);
			~GDIView();

			virtual void DrawImage(const HBITMAP& image, const Vector2D& vector, double alpha) const {

			}

			virtual void DrawRectangle(const Vector2D& vector, double width, double height) const {

			}

			virtual void DrawCircle(const Vector2D& vector, double radius) const {

			}

			virtual void DrawLine(const Vector2D& start, const Vector2D& end, double width) const {

			}

			virtual void Render(const HDC& surface) {
				gdi->StartDrawing(surface);
				
				Level * level = game->GetCurrentLevel();

				if(renderGrid) {
					RenderGrid(level->GetGrid());
				}

				game->GetCurrentLevel()->MapToEntities([&] (const Cell * cell, const Entity * entity) {

				});

				gdi->StopDrawing(surface);
			}

			void RenderGrid(Grid<Cell> * grid) {

			}
		private:
			Game::Game * game;
			HDC * current;
			bool renderGrid;
	};

	GDIView::GDIView(Game::Game& game) 
		: game(&game), 
		  View<HDC, HBITMAP, Vector2D>(), 
		  renderGrid(true) {

	}

	GDIView::~GDIView() {

	}
}

#endif