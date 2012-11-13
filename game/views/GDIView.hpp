#ifndef GDI_VIEW_HPP
#define GDI_VIEW_HPP

#include "../space/Bounds.hpp"

#include "../Game.hpp"
#include "../entities/Entity.hpp"
#include "../space/Cell.h"
#include "../space/Level.hpp"

#include "../../headers/Cgdi.h"
#include "../../headers/Vector2D.h"
#include "view.hpp"

#include <Windows.h>
#include <sstream>

namespace Views {
	using Space::Cell;
	using Space::Level;
	using Space::Grid;
	using Space::Bounds;

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
					RenderGrid(*level, *level->GetGrid(), *(level->GetBounds()));
				}

				game->GetCurrentLevel()->MapToEntities([&] (const Cell * cell, const Entity * entity) {
					RenderEntity(entity);
				});

				gdi->StopDrawing(surface);
			}

			void RenderGrid(const Level& level, const Grid<Cell>& grid, const Bounds<Vector2D>& levelBounds) {
				double x, y;
				double columns = static_cast<double>(grid.GetNumberOfColumns());
				double rows = static_cast<double>(grid.GetNumberOfRows());

				double w = levelBounds.Width() / columns;
				double h = levelBounds.Height() / rows;

				Vector2D pos = level.GetPosition();
				for(int i = 0; i < columns; ++i) {
					x = i * w;
					for(int k = 0; k < rows; ++k) {
						y = k * h;

						std::stringstream s;
						s << "Cell " << i << ", " << k << " at ";
						s << std::fixed << std::setprecision(1) << x << ", " << y;

						gdi->TransparentText();
						gdi->TextColor(Cgdi::blue);
						gdi->Fontsize(11);

						gdi->TextAtPos(x + 10, y + 10, s.str());

						gdi->BlackBrush();
						gdi->Line(x, y, x+w, y);
						gdi->Line(x+w, y, x+w, y+h);
						gdi->Line(x+w, y+h, x, y+h);
						gdi->Line(x, y+h, x, y);
					}
				}
			}

			void RenderEntity(const Entity * e) {
				Bounds<Vector2D> bounds = e->GetBounds();

				double x = bounds.Left();
				double y = bounds.Top();
				double w = bounds.Width();
				double h = bounds.Height();

				gdi->RedBrush();
				gdi->Line(x, y, x+w, y);
				gdi->Line(x+w, y, x+w, y+h);
				gdi->Line(x+w, y+h, x, y+h);
				gdi->Line(x, y+h, x, y);

				gdi->TextAtPos(x + 10, y + 10, "HERE");
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