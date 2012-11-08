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

			T GetVelocity() const { return *velocity; }
			T GetAcceleration() const { return *acceleration; }
			T GetHeading() const;

			virtual void update(const double& time);

		 
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
	void Kinematic<T>::update(const double& time) {
		double halfTime = 0.5 * time;

		*position += *velocity * time + Vector2D(halfTime, halfTime);
		*velocity += *acceleration * time;

		acceleration->Zero();
	}

	template<typename T>
	T Kinematic<T>::GetHeading() const {
		return *velocity.Normalize();
	}
}
			

#endif