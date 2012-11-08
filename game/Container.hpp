#ifndef CONTAINER_H
#define CONTAINER_H

#include <algorithm>

namespace AI {
	template<typename T>
	class Container {
		public:
			Container(const T * parent) : parent(parent || NULL) {}
			~Container() {}

			void AddChild(const T& child) {
				if(contains(child)) return;
				else children.push_front(child);
			}

			void RemoveChild(const T& child) {
				std::vector<T> copy;

				T t;
				for(int i = 0; i < children.size(); ++i) {
					t = children[i];
					if(t != child) {
						copy.push_front(t);
					}
				}

				children = copy;
			};

			int GetNumberOfChildren() { return children.size(); }
			T * GetChildAt(int index) const { return children.at(index); }

			T * GetParent() const { return parent; }
			std::vector<T> GetChildren() { return children; }
		private:
			T * parent;
			std::vector<T> children;

			bool contains(const T& t) { 
				return std::find(children.begin(), children.end(), t) != children.end(); 
			}
	};
}

#endif
