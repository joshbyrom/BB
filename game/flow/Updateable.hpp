#ifndef UPDATEABLE_HPP
#define UPDATEABLE_HPP

#include "../Container.hpp"

#include <functional>
#include <stdint.h>

namespace FlowControl {
	template<typename T>
	class Updatable : public Container<T> {
		public:
			Updateable(uint64_t delay, uint64_t duration, uint16_t repeats);
			~Updateable();

			void update(uint64_t elapsed);
		private:
			bool running;

			uint64_t startTime;
			uint64_t delay;
			uint64_t duration;
			uint64_t repeats;

		protected:
			std::function<void()> onStarted;
			std::function<void()> onFinished;
			std::function<void()> onUpdate;
	};

	template<typename T>
	Updateable<T>::Updateable(uint64_t delay, uint64_t duration, uint16_t repeats)
		: delay(delay), duration(duration), repeats(repeats) {
			
		QueryPerformanceCounter(&startTime);
	}
}

#endif