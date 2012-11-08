#ifndef MOVEMENT_H
#define MOVEMENT_H

template<typename T, typename K>
class Movement {
	public:
		Movement();
		~Movement();

		virtual void ApplyForce(const T& force, const K time) = 0;

		T GetPosition() const;
		bool SetPosition(const T& newPosition);
	private:
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
Movement<T, K>::GetPosition() const {
	return position;
}

template<typename T, typename K>
Movement<T, K>::SetPosition(const T& newPosition) {
	if(position == newPosition) return false;

	position = newPosition;
	return true;
}
#endif