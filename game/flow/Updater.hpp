#ifndef UPDATEABLE_HPP
#define UPDATEABLE_HPP

#include "../Container.hpp"

#include <functional>
#include <stdint.h>

namespace FlowControl {
	using AI::Container;

	class Updater : public Container<Updater> {
		public:
			Updater(std::function<void()> fun, uint64_t delay, uint64_t duration, uint16_t repeats);
			~Updater();

			void update();

			Updater withOnStarted(std::function<void()> onStart) {
				if(!running) 
					onStarted = &onStart;
				return *this;
			}

			Updater withOnFinished(std::function<void()> onFinish) {
				if(!running)
					onFinished = &onFinish;
				return *this;
			}
		private:
			bool running;

			uint64_t startTime;
			uint64_t finishTime;

			uint64_t delay;
			uint64_t duration;
			uint64_t repeats;

			uint64_t now;
			uint64_t lastUpdate;

			bool infinite;

			inline void setNextStartTime(const uint64_t& now) {
				startTime = now + delay;
				finishTime = startTime + duration;
			};
		protected:
			std::function<void()> * onStarted;
			std::function<void()> * onFinished;
			std::function<void()> * onUpdate;
	};

	Updater::Updater(std::function<void()> fun, 
		                      uint64_t delay, 
							  uint64_t duration, 
							  uint16_t repeats)
		: delay(delay), duration(duration), repeats(repeats), running(false),
	      onStarted(NULL), onFinished(NULL), onUpdate(&fun), infinite(false) {
			
	}

	Updater::~Updater() {

	}

	void Updater::update() {
		if(!infinite && repeats <= 0) {
			if(running) {
				if(onFinished) (*onFinished)();
				running = false;
			}
			return;
		}

		QueryPerformanceCounter((LARGE_INTEGER *)&now);

		if(now >= startTime && now <= finishTime) {
			if(!running) {
				if(onStarted) (*onStarted)();
				running = true;
			}

			if(onUpdate) (*onUpdate)();

			// update children
			map([&] (Updater e) -> void {
				e.update();
			});

			repeats--;
		}

		lastUpdate = now;
	}
}

#endif