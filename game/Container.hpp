#ifndef CONTAINER_H
#define CONTAINER_H

#include <functional>
#include <algorithm>

namespace AI {
	template<typename T>
	class Container {
		public:
			Container() : parent(NULL) {}
			Container(T * parent) : parent(parent) {}
			~Container() {}

			void AddChild(const T& child) {
				if(contains(child)) return;
				else children.push_front(child);
			}

			void RemoveChild(const T& child) {
				std::vector<T> copy;

				T t;
				for(unsigned int i = 0; i < children.size(); ++i) {
					t = children[i];
					if(t != child) {
						copy.push_front(t);
					}
				}

				children = copy;
			};

			UINT RemoveIf(std::function<bool()> pred) {
				std::vector<T> copy;
				UINT numberRemoved = 0;

				T t;
				for(unsigned int i = 0; i < children.size(); ++i) {
					t = children[i];
					if(pred(t)) {
						// don't add it
					} else {
						copy.push_front(t);
					}
				}

				children = copy;
				return numberRemoved;
			}

			int GetNumberOfChildren() { return children.size(); }
			T * GetChildAt(int index) const { return children.at(index); }

			T * GetParent() const { return parent; }
			std::vector<T> GetChildren() { return children; }

			void Map(std::function<void(T)> fun);
			double Sum(std::function<double(T)> fun);
		protected:
			T * parent;

		private:
			std::vector<T> children;

			bool contains(const T& t) { 
				return std::find(children.begin(), children.end(), t) != children.end(); 
			}
	};

	template<typename T>
	void Container<T>::Map(std::function<void(T)> fun) {
		for_each(children.begin(), children.end(), fun);
	}

	template<typename T>
	double Container<T>::Sum(std::function<double(T)> fun) {
		double acc = 0;
		for(unsigned int i = 0; i < children.size(); ++i) {
			acc += fun(children[i]);
		}
		return acc;
	}
}

#endif
