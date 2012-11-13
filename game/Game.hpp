#ifndef GAME_H
#define GAME_H


#include "../headers/constants.h"

#include "space\Level.hpp"
#include "entities\Entity.hpp"


namespace Game {
	using Space::Level;

	using AI::Entity;

	class Game  {
	public:
		Game() {
			double levelWidth = static_cast<double>(WINDOW_WIDTH);
			double levelHeight = static_cast<double>(WINDOW_HEIGHT);

			Entity e;
			e.GetKinematic().SetPosition(levelWidth * 0.5, levelHeight * 0.5);

			level = new Level("Test Level", levelWidth, levelHeight);
			level->AddEntityToLevel(e);
		}

		~Game() {
			delete level;
		}

		void Update() {
			level->Update();
		}

		Level * GetCurrentLevel() {  return level; }
	private:
		Level * level;
	};
}

#endif GAME_H