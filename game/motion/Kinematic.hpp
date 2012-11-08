#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "Movement.hpp"

namespace Motion {
	template<typename T>
	class Kinematic : public Movement<T, double> {
		public:
			Kinematic() : velocity(new T()), acceleration(new T()) {
				// get max force from params.ini
				this->maxForce = 0;	 // TODO
			}

			~Kinematic() {
				delete velocity;
				delete acceleration;
			}

			void update(double time);

		 
			virtual void ApplyForce(const T& force) {
				*acceleration += force;
				acceleration->Truncate(maxForce);
			}

		private:
			T * velocity;
			T * acceleration;

			double maxForce;
	};

	template<typename T>
	void Kinematic<T>::update(double time) {
		position += velocity * time + 0.5 * time;
		velocity += acceleration * time;

		acceleration->Zero();
	}
}
			

#endif