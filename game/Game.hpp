#ifndef GAME_H
#define GAME_H


#include "../headers/constants.h"

#include "space\Level.hpp"


namespace Game {
	using Space::Level;

	class Game  {
	public:
		Game() {
			double levelWidth = static_cast<double>(WINDOW_WIDTH);
			double levelHeight = static_cast<double>(WINDOW_HEIGHT);

			level = new Level("Test Level", levelWidth, levelHeight);
		}

		~Game() {
			delete level;
		}

		void Update() {
			level->Update();
		}

		const Level& GetCurrentLevel() {  return *level; }
	private:
		Level * level;
	};
}

#endif GAME_H