#ifndef MESSAGEABLE_HPP
#define MESSAGEABLE_HPP

#include "Message.hpp"

namespace Messaging {
	template<typename T>
	class Messageable {
	public:
		virtual bool ReceiveMessage(Message<unsigned int, T> message) = 0;
	private:
	};
}


#endif