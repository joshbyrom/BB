#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "Movement.hpp"

namespace Motion {
	template<typename T>
	class Kinematic : public Movement<T, double> {
		public:
			Kinematic();
			~Kinematic();

			void update(double time);

		 
			virtual void ApplyForce(const T& force) {
				acceleration += force;

				if(acceleration.Length() > maxForce) {
					acceleration.Normalize();
					acceleration *= maxForce;
				}
			}

		private:
			T * velocity;
			T * acceleration;

			double maxForce;
	};

	template<typename T>
	Kinematic<T>::update(double time) {
		position += velocity * time + 0.5 * time;
		velocity += acceleration * time;

		acceleration *= 0;
	}
}
			

#endif