#ifndef BOUNDS_H
#define BOUNDS_H

#include <functional>

namespace Space {
	// T is required to have
	//  function :
	//		GetWidth
	//		GetHeight
	//	members :
	//		x
	//		y

	template<typename T, typename K>
	class Bounds {
		public:
			Bounds(T& t, std::function<K()> fun);  // TODO sense changes in T to cache fun() results
			~Bounds() {}

			K GetTopLeft() { return position(); }
			double GetWidth()  { return t->GetWidth(); }
			double GetHeight() { return t->GetHeight(); }
			double GetRadius() { 
				double width = GetWidth();
				double height = GetHeight();

				return width > height ? width : height;
			}

			double Left()   { return position().x; }
			double Right()  { return position().x + GetWidth(); }
			double Top()    { return position().y; }
			double Bottom() { return position().y + GetHeight(); }

			K GetCenter() { return K(Left() + GetWidth() * 0.5, Top() + GetHeight() * 0.5); }
			T GetBoundedObject() const { return *t; }

			bool operator==(const Bounds<T, K>& rhs)const
			{
				return T == rhs.GetBoundedObject() &&
					Left() == rhs.Left() && Top() == rhs.Top();
			}

			bool operator!=(const Bounds<T, K>& rhs)const
			{
				return T != rhs.GetBoundedObject() &&
					Left() != rhs.Left() && Top() != rhs.Top();
			}
		private:
			T * t;

			std::function<K()> position;
	};

	template<typename T, typename K>
	Bounds<T, K>::Bounds(T& t, std::function<K()> fun) 
		: t(&t), position(fun) {

	}
}

#endif