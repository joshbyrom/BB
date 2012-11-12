#ifndef TRANSITION_H
#define TRANSITION_H

#include "Updater.h"

#include <functional>
#include <stdint.h>

namespace FlowControl {
	template<typename T>
	class Transition : public Updater {
		public:
			Transition(const T& t);
			~Transition();

			virtual void OnStart();
			virtual void Update();
			virtual void OnFinished();
		private:
			uint64_t defaultDuration;
			T * t;
	};

	template<typename T>
	Transition<T>::Transition(const T& t) 
		: t(t), Updater(this->Update(), 0, defaultDuration, 1) {
			this->WithOnFinished(OnFinished)->WithOnStarted(OnStart);
	}

	template<typename T>
	Transition<T>::Transition() {

	}
}

#endif