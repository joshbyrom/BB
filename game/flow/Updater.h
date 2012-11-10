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

			void Update();

			void UpdateChildren() {
				Map([&] (Updater e) -> void {
					e.Update();
				});
			}

			void RemoveFinishedChildren() {
				RemoveIf([] (Updater up) -> bool {
					return up.IsFinished();
				});
			}

			Updater WithOnStarted(std::function<void()> onStart) {
				if(!running) 
					onStarted = &onStart;
				return *this;
			}

			Updater WithOnFinished(std::function<void()> onFinish) {
				if(!running)
					onFinished = &onFinish;
				return *this;
			}

			Updater WithInfiniteRepeats() {
				infinite = true;
				return *this;
			}

			void Pause() {
				if(paused) return;

				paused = true;
				Map([&] (Updater e) -> void {
					e.Pause();
				});

				QueryPerformanceCounter((LARGE_INTEGER *)&pausedTime);
			}

			void Resume() {
				if(!paused) return;

				paused = false;
				Map([&] (Updater e) -> void {
					e.Resume();
				});
				
				QueryPerformanceCounter((LARGE_INTEGER *)&now);
				uint64_t nextDelay = max(delay - (pausedTime - lastUpdate), 0);
				SetNextStartTime(now, nextDelay);
			}

			bool IsFinished() { return finished; }
		private:
			bool running;
			bool paused;
			bool finished;

			uint64_t pausedTime;

			uint64_t startTime;
			uint64_t finishTime;

			uint64_t delay;
			uint64_t duration;
			uint64_t repeats;

			uint64_t now;
			uint64_t lastUpdate;

			bool infinite;

			inline void SetNextStartTime(const uint64_t& now, const uint64_t& delay) {
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

		
		QueryPerformanceCounter((LARGE_INTEGER *)&now);
		SetNextStartTime(now, delay);
	}

	Updater::~Updater() {

	}

	void Updater::Update() {
		if(paused) return;

		if(!infinite && repeats <= 0) {
			if(running) {
				if(onFinished) (*onFinished)();
				running = false;
				finished = true;
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

			UpdateChildren();
			RemoveFinishedChildren();

			SetNextStartTime(now, delay);
			repeats--;
		}

		lastUpdate = now;
	}
}

#endif