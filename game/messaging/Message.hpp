#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <time.h>
#include <math.h>
#include "../../headers/constants.h"

namespace GameMessaging {
	template<typename MESSAGE, typename T>
	class Message {
		public:
			Message(const MESSAGE& msg, const T& sender, const T& receiver, unsigned long delay);
			~Message();

			T GetReciever() { return receiver; }
			T GetSender() { return sender; }

			unsigned int GetDispatchTime() { return timestamp; }
			unsigned int GetAge() { return ((clock() - creation_clock) * 1000) / CLOCKS_PER_SEC; }
			MESSAGE GetMessageContent() { return message; }
		private:
			MESSAGE * message;
			T * sender;
			T * receiver;

			clock_t creation_time;
			clock_t timestamp;
	};

	template<typename MESSAGE, typename T>
	Message<MESSAGE, T>::Message(const MESSAGE& message, const T& sender, const T& receiver, unsigned long delay) 
		: message(&message), 
		  sender(&sender), 
		  receiver(&receiver), 
		  creation_time(clock()), 
		  timestamp(clock() + delay) {

	}

	template<typename MESSAGE, typename T>
	inline bool operator==(const Message<MESSAGE, T>& msg1, const Message<MESSAGE, T>& msg2) {
		return fabs(msg1.GetDispatchTime() - msg2.GetDispatchTime()) < smallestDelay &&
			   msg1.GetSender() == msg2.GetSender() && msg1.GetReceiver() == msg2.GetReceiver() &&
			   msg1.GetMessageContent() == msg2.GetMessageContent();
	}

	template<typename MESSAGE, typename T>
	inline bool operator<(const Message<MESSAGE, T>& msg1, const Message<MESSAGE, T>& msg2) {
		return (msg1 != msg2) && msg1.GetDispatchTime() < msg2.GetDispatchTime();
	}
}

#endif