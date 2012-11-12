#ifndef GDI_VIEW_HPP
#define GDI_VIEW_HPP

#include "../Game.hpp"

#include "../../headers/Cgdi.h"
#include "../../headers/Vector2D.h"
#include "view.hpp"

#include <Windows.h>

namespace Views {
	class GDIView : public View<HDC, HBITMAP, Vector2D> {
		public:
			GDIView(const Game::Game& game);
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
         

				gdi->StopDrawing(surface);
			}
		private:
			const Game::Game * game;
			HDC * current;
	};

	GDIView::GDIView(const Game::Game& game) 
		: game(&game), View<HDC, HBITMAP, Vector2D>() {

	}

	GDIView::~GDIView() {

	}
}

#endif