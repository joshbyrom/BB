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

			virtual void DrawImage(const IMAGE_TYPE& image, VECTOR_TYPE vector, double alpha);
			virtual void DrawRectangle(VECTOR_TYPE vector, double width, double height);
			virtual void DrawCircle(VECTOR_TYPE vector, double radius);
			virtual void DrawLine(VECTOR_TYPE start, VECTOR_TYPE end, double width);

			virtual void Render(const SURFACE& surface);
	};
}

#endif