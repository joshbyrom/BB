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

		~Identifiable() {

		}

		long GetID() const { return id; }

		bool operator==(const Identifiable& rhs)const
		{
			// add more here
			return this->GetID() == rhs.GetID();
		}
	protected:
		long GenerateID() {
			static long nextID = 1;
			return InterlockedIncrement(&nextID);
		}

	private:
		long id;
	};
}

#endif