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
			GDIView(Game::Game game);
			~GDIView();

			virtual void DrawImage(const HBITMAP& image, Vector2D vector, double alpha) override;
			virtual void DrawRectangle(Vector2D vector, double width, double height) override;
			virtual void DrawCircle(Vector2D vector, double radius) override;
			virtual void DrawLine(Vector2D start, Vector2D end, double width) override;

			virtual void Render(const HDC& surface);
		private:
			Game::Game * game;
	};

	GDIView::GDIView(Game::Game game) 
		: game(&game) {

	}

	GDIView::~GDIView() {

	}

	void GDIView::DrawImage(const HBITMAP& image, Vector2D vector, double alpha) override {

	}

	void GDIView::DrawRectangle(Vector2D vector, double width, double height) override {

	}

	void GDIView::DrawCircle(Vector2D vector, double radius) override {

	}

	void GDIView::DrawLine(Vector2D start, Vector2D end, double width) override {

	}

	void Render(const HDC& surface) {

	}
}

#endif