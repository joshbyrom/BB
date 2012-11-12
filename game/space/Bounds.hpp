#ifndef BOUNDS_H
#define BOUNDS_H

#include <functional>

namespace Space {
	template<typename T>
	class Bounds {
		public:
			Bounds();
			Bounds(Bounds<T>& copy);
			~Bounds() {}

			void Update(const double& x, const double& y, const double& width, const double& height);
			void Update(const T& xy, const double& width, const double& height);

			T TopLeft() const { return T(x, y); }
			double Width() const  { return width; }
			double Height() const { return height; }
			double Radius() const { 
				return width > height ? width : height;
			}

			double Left() const   { return x; }
			double Right() const  { return x + Width(); }
			double Top() const    { return y; }
			double Bottom() const { y + Height(); }

			T GetCenter() { return T(Left() + Width() * 0.5, Top() + Height() * 0.5); }

			bool operator==(const Bounds<T>& rhs)const
			{
				return Left() == rhs.Left() && Top() == rhs.Top() &&
					   Width() == rhs.Width() && Height() == rhs.Height();
			}

			bool operator!=(const Bounds<T>& rhs)const
			{
				return Left() != rhs.Left() && Top() != rhs.Top() &&
					   Width() != rhs.Width() && Height() != rhs.Height();
			}
		private:
			double x, y, width, height;
	};

	template<typename T>
	Bounds<T>::Bounds() 
		: x(0), y(0), width(0), height(0) {

	}

	template<typename T>
	Bounds<T>::Bounds(Bounds<T>& copy) 
		: x(copy.Left()), 
		  y(copy.Top()), 
		  width(copy.Width()), 
		  height(copy.Height()) {

	}

	template<typename T>
	void Bounds<T>::Update(const double& x, 
		                   const double& y, 
						   const double& width, 
						   const double& height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	template<typename T>
	void Bounds<T>::Update(const T& xy, 
						   const double& width, 
						   const double& height) {
		this->x = xy.x;
		this->y = xy.y;
		this->width = width;
		this->height = height;
	}
}

#endif