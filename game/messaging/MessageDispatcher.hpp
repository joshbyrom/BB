#ifndef MESSAGE_DISPATCHER_HPP
#define MESSAGE_DISPATCHER_HPP

#include <set>
#include <time.h>

#include "Message.hpp"
#include "MessageTypes.h"
#include "Messageable.hpp"

namespace GameMessaging {
	template<typename T>
	class MessageDispatcher {
	public:
		MessageDispatcher();
		~MessageDispatcher();

		void SendMessageToReceiver(const Message<MessageType, T>& message);
		void ProcessMessages();
	private:
		std::set<Message<unsigned int, T>> que;

		void HandleMessage(Messageable<MessageType, T> * receiver, const Message<MessageType, T>& msg);
	};

	template<typename T>
	MessageDispatcher<T>::MessageDispatcher() {

	}

	template<typename T>
	MessageDispatcher<T>::~MessageDispatcher() {

	}

	template<typename T>
	void MessageDispatcher<T>::HandleMessage(Messageable<MessageType, T> * receiver, 
											 const Message<MessageType, T>& msg) {
		bool handled = receiver->ReceiveMessage(msg);
	}

	template<typename T>
	void MessageDispatcher<T>::SendMessageToReceiver(const Message<MessageType, T>& message) {
		T receiver = message.GetReceiver();

		if(message.GetAge() > message.GetDispatchTime()) {

		}
	}
}
#endif