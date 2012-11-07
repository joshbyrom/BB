#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <time.h>
#include <math.h>
#include "../../headers/constants.h"

namespace GameMessaging {
	template<typename CONTENTS, typename T>
	class Message {
		public:
			Message(const CONTENTS& msg, const T& sender, const T& receiver, unsigned long delay);
			~Message();

			T GetReciever() { return receiver; }
			T GetSender() { return sender; }

			unsigned int GetDispatchTime() { return timestamp; }
			unsigned int GetAge() { return ((clock() - creation_clock) * 1000) / CLOCKS_PER_SEC; }
			CONTENTS GetContent() { return message; }
		private:
			CONTENTS * message;
			T * sender;
			T * receiver;

			clock_t creation_time;
			clock_t timestamp;
	};

	template<typename CONTENTS, typename T>
	Message<CONTENTS, T>::Message(const CONTENTS& message, const T& sender, const T& receiver, unsigned long delay) 
		: message(&message), 
		  sender(&sender), 
		  receiver(&receiver), 
		  creation_time(clock()), 
		  timestamp(clock() + delay) {

	}

	template<typename CONTENTS, typename T>
	inline bool operator==(const Message<CONTENTS, T>& msg1, const Message<CONTENTS, T>& msg2) {
		return fabs(msg1.GetDispatchTime() - msg2.GetDispatchTime()) < smallestDelay &&
			   msg1.GetSender() == msg2.GetSender() && msg1.GetReceiver() == msg2.GetReceiver() &&
			   msg1.GetMessageContent() == msg2.GetMessageContent();
	}

	template<typename CONTENTS, typename T>
	inline bool operator<(const Message<CONTENTS, T>& msg1, const Message<CONTENTS, T>& msg2) {
		return (msg1 != msg2) && msg1.GetDispatchTime() < msg2.GetDispatchTime();
	}
}

#endif