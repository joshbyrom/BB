#ifndef MESSAGEABLE_HPP
#define MESSAGEABLE_HPP

#include "Message.hpp"

namespace GameMessaging {
	template<typename M, typename T>
	class Messageable {
	public:
		virtual bool ReceiveMessage(const Message<M, T>& message) = 0;
	private:
	};
}


#endif