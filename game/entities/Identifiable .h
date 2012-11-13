#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

#include "windows.h"

namespace AI {
	class Identifiable {
	public:
		Identifiable() 
			: id(GenerateID()) {

		}

		Identifiable(const Identifiable& copy) 
			: id(copy.id) {

		}

		virtual ~Identifiable() {

		}

		long GetID() const { return id; }

		bool operator==(const Identifiable& rhs)const
		{
			// add more here
			return this->GetID() == rhs.GetID();
		}
	private:
		long GenerateID() {
			static long nextID = 1;
			return InterlockedIncrement(&nextID);
		}

		long id;
	};
}

#endif