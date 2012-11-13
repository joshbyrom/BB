#ifndef UPDATEABLE_HPP
#define UPDATEABLE_HPP

#include "../Container.hpp"

#include <functional>
#include <stdint.h>
#include <map>

namespace FlowControl {
	using AI::Container;

	class Updater : public Container<Updater> {
		public:
			Updater(std::function<void()> fun, uint64_t delay, uint64_t duration, uint16_t repeats);
			Updater(const Updater& copy);
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

			void RemoveChildByFunction(std::function<void()> fun) {
				RemoveIf([&] (Updater up) -> bool {
					std::function<void()> * onUp = up.onUpdate;
					return onUp == &fun;
				});
			}

			void AddHook(std::string id, std::function<void()> fun) {
				hooks[id] = fun;
			}

			void RemoveHook(std::string id) {
				hooks.erase(id);
			}

			void UpdateHooks() {
				MapType::const_iterator end = hooks.end();
				for(MapType::const_iterator it = hooks.begin(); it != end; ++it) {
					it->second();
				}
			}

			Updater  * WithOnStarted(std::function<void()> onStart) {
				if(!running) 
					onStarted = new std::function<void()>(onStart);
				return this;
			}

			Updater * WithOnFinished(std::function<void()> onFinish) {
				if(!running)
					onFinished = new std::function<void()>(onFinish);
				return this;
			}

			Updater * WithInfiniteRepeats() {
				infinite = true;
				return this;
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

			uint64_t Elapsed() {
				uint64_t result;
				QueryPerformanceCounter((LARGE_INTEGER *)&result);

				return now - lastUpdate;
			}

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

			typedef std::map<std::string, std::function<void()>> MapType;
			std::map<std::string, std::function<void()>> hooks;
	};

	Updater::Updater(std::function<void()> fun, 
		                      uint64_t delay, 
							  uint64_t duration, 
							  uint16_t repeats)
		: delay(delay), duration(max(11,duration)), repeats(repeats), running(false),
	      onStarted(NULL), onFinished(NULL), 
		  onUpdate(new std::function<void()>(fun)), infinite(false) {

	    onStarted = new std::function<void()>([](){});
		onFinished = new std::function<void()>([](){});
		QueryPerformanceCounter((LARGE_INTEGER *)&now);
		SetNextStartTime(now, delay);
	}

	Updater::Updater(const Updater& other) 
		: running(other.running),
		  paused(other.paused),
		  finished(other.finished),
		  pausedTime(other.pausedTime),
		  startTime(other.startTime),
		  finishTime(other.finishTime),
		  delay(other.delay),
		  duration(other.duration),
		  repeats(other.repeats),
		  now(other.now),
		  lastUpdate(other.lastUpdate),
		  infinite(other.infinite)
	{
		hooks.insert(other.hooks.begin(), other.hooks.end());

		onUpdate = new std::function<void()>(*other.onUpdate);
		onStarted = new std::function<void()>(*other.onStarted);
		onFinished = new std::function<void()>(*other.onFinished);
	}

	Updater::~Updater() {
		delete onUpdate;
		delete onStarted;
		delete onFinished;
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

			UpdateHooks();

			UpdateChildren();
			RemoveFinishedChildren();

			SetNextStartTime(now, delay);
			if(repeats > 0) repeats--;
		}

		lastUpdate = now;
	}
}

#endif