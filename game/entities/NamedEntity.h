#ifndef NAMED_ENTITY_H
#define NAMED_ENTITY_H

#include "Entity.hpp"
#include <string>

namespace AI {
	class NamedEntity : public Entity {
	public:
		NamedEntity(std::string name) : Entity(), name(name) {}
		~NamedEntity() {}

		std::string GetName() { return name; }
		NamedEntity GetChildByName(std::string name) {
			NamedEntity result = NULL;


			return result;
		}
	private:
		std::string name;
	};
}

#endif