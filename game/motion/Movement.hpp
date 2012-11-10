#ifndef MOVEMENT_H
#define MOVEMENT_H

namespace Motion {
	template<typename T, typename K>
	class Movement {
		public:
			Movement();
			~Movement();

			virtual void ApplyForce(const T& force) = 0;
			virtual void Update(const K& time) = 0;

			T GetPosition() const;
			bool SetPosition(const T& newPosition);
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
}
#endif