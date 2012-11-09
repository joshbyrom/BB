#ifndef TRANSITION_H
#define TRANSITION_H

#include <functional>
#include <stdint.h>

namespace FlowControl {
	class Transition {
		public:
		private:
			uint64_t delay;
			uint64_t duration;

			uint64_t lastUpdate;
			std::function<void(double)> fun;
	};
}

#endif