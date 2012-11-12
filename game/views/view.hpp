#ifndef VIEW_HPP
#define VIEW_HPP

namespace Views {
	template<typename SURFACE, 
		     typename IMAGE_TYPE, 
			 typename VECTOR_TYPE>
	class View {
		public:
			View() {}
			~View() {}

			virtual void DrawImage(const IMAGE_TYPE& image, const VECTOR_TYPE& vector, double alpha) const = 0;
			virtual void DrawRectangle(const VECTOR_TYPE& vector, double width, double height) const = 0;
			virtual void DrawCircle(const VECTOR_TYPE& vector, double radius) const = 0;
			virtual void DrawLine(const VECTOR_TYPE& start, const VECTOR_TYPE& end, double width) const = 0;

			virtual void Render(const SURFACE& surface) = 0;
	};
}

#endif