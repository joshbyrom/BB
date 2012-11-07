#ifndef MESSAGEABLE_HPP
#define MESSAGEABLE_HPP

#include "Message.hpp"

namespace GameMessaging {
	template<typename T>
	class Messageable {
	public:
		virtual bool ReceiveMessage(const Message<unsigned int, T>& message) = 0;
	private:
	};
}


#endif