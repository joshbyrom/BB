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

			void Update(const double& time) override;

		 
			void ApplyForce(const T& force) override {
				*acceleration += force;
				acceleration->Truncate(maxForce);
			}

			bool operator==(const Kinematic<T>& rhs)const
			{
				return GetVelocity() == rhs.GetVelocity() &&
					   GetAcceleration() == rhs.GetAcceleration();
			}

			bool operator!=(const Kinematic<T>& rhs)const
			{
				return GetVelocity() != rhs.GetVelocity() &&
					   GetAcceleration() != rhs.GetAcceleration();
			}

		private:
			T * velocity;
			T * acceleration;

			double maxForce;
	};

	template<typename T>
	void Kinematic<T>::Update(const double& time) {
		double halfTime = 0.5 * time;

		*position += *velocity * time + Vector2D(halfTime, halfTime);
		*velocity += *acceleration * time;

		acceleration->Zero();
	}

	template<typename T>
	T Kinematic<T>::GetHeading() const {
		T t = velocity->Copy();
		return t.Normalize();
	}
}
			

#endif