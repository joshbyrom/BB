#ifndef BOUNDS_H
#define BOUNDS_H


namespace Space {
	template<typename T>
	class Bounds {
		Bounds(T t);
		~Bounds();

		double GetWidth()  { return t->GetWidth(); }
		double GetHeight() { return t->GetHeight(); }
		double GetRadius() { 
			double width = GetWidth();
			double height = GetHeight();

			return width > height ? width : height;
		}

		T GetBoundedObject() const { return *t; }
		private:
			T * t;
	};

	template<typename T>
	Bounds<T>::Bounds(T t) 
		: t(t) {

	}
}

#endif