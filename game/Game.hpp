#ifndef GAME_H
#define GAME_H

#include "entities\NamedEntity.h"
#include <string>

namespace Game {
	using AI::NamedEntity;

	template<typename T>
	class Game : public NamedEntity {
	public:
		Game() : NamedEntity("Block Buster") {}
		~Game() {}
	private:

	};
}

#endif GAME_H