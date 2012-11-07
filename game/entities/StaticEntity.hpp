#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	class StaticEntity : public Messageable<MessageType, StaticEntity> {

	
	public:
		virtual bool StaticEntity::ReceiveMessage(const Message<MessageType, StaticEntity>& message) {

		}
	};
}