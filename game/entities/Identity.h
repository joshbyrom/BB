#ifndef IDENTITY_H
#define IDENTITY_H

#include <sstream>
#include <string>
#include "Identifiable .h"

namespace AI {
	class Identity : public Identifiable {
		public:
			Identity() 
				: name("") {
					std::string s = "Entity ";
					std::stringstream out;
					out << s << GetID();
					name = out.str();
			}

			Identity(std::string name) : name(name) {

			}

			virtual ~Identity() {}
		private:
			std::string name;
	};
}

#endif