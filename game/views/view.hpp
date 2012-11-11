#ifndef VIEW_HPP
#define VIEW_HPP

namespace Views {
	template<typename T, typename K>
	class View {
		public:
			View(const T& t);
			~View();

			virtual void DrawImage(const K& k, double x, double y, double z, double alpha);
			virtual void DrawRectangle(double x, double y, double z, double width, double height);
			virtual void DrawCircle(double x, double y, double z, double radius);

		private:
			T * t;
	};

	template<typename T>
	View<T>::View(const T& t) {
		this->t = t;
	}
}

#endif