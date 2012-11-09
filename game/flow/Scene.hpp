#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "../entities/NamedEntity.h"

namespace FlowControl {
	using std::string;

	template<typename T>
	class Scene : public NamedEntity {
		public:
			Scene(string name) : NamedEntity(name) {}
	};
}


#endif