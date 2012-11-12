#ifndef GAME_H
#define GAME_H


#include "space\Level.hpp"


namespace Game {
	using Space::Level;

	class Game  {
	public:
		Game() {
		}

		~Game() {
			delete level;
		}

		void Update() {

		}
	private:
		Level * level;
	};
}

#endif GAME_H