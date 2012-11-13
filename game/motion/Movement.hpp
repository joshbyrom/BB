#ifndef MOVEMENT_H
#define MOVEMENT_H

namespace Motion {
	template<typename T, typename K>
	class Movement {
		public:
			Movement();
			virtual ~Movement();

			virtual void ApplyForce(const T& force) = 0;
			virtual void Update(const K& time) = 0;

			T GetPosition() const;
			bool SetPosition(const T& newPosition);
			bool SetPosition(const double& x, const double& y);
		protected:
			T * position;
	};

	template<typename T, typename K>
	Movement<T, K>::Movement()
		: position(new T()) {

	}

	template<typename T, typename K>
	Movement<T, K>::~Movement() {
		delete position;
	}

	template<typename T, typename K>
	T Movement<T, K>::GetPosition() const {
		return *position;
	}

	template<typename T, typename K>
	bool Movement<T, K>::SetPosition(const T& newPosition) {
		if(position == newPosition) return false;

		position = newPosition;
		return true;
	}

	template<typename T, typename K>
	bool Movement<T, K>::SetPosition(const double& x, const double& y) {
		if(position->x == x && position->y == y) return false;

		position->x = x;
		position->y = y;
		return true;
	}
}
#endif