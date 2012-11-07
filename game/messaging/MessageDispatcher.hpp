#ifndef MESSAGE_DISPATCHER_HPP
#define MESSAGE_DISPATCHER_HPP

#include <set>
#include "Message.hpp"
#include "Messageable.hpp"

namespace Messaging {
	template<typename T>
	class MessageDispatcher {
	public:
		MessageDispatcher();
		~MessageDispatcher();

		void SendMessage(const Message<unsigned int, T> message);
		void ProcessMessages();
	private:
		std::set<Message<unsigned int, T>> que;

		void HandleMessage(Messageable<T> * receiver, const Message<unsigned int, T> msg);
	};

	template<typename T>
	MessageDispatcher<T>::MessageDispatcher() {

	}

	template<typename T>
	MessageDispatcher<T>::~MessageDispatcher() {

	}

	template<typename T>
	void MessageDispatcher<T>::HandleMessage(Messageable<T> * receiver, 
											 const Message<unsigned int, T> msg) {
		bool handled = receiver->ReceiveMessage(msg);
	}

	template<typename T>
	void MessageDispatcher<T>::SendMessage(const Message<unsigned int, T> message) {
		T receiver = message.GetReceiver();
	}
}
#endif