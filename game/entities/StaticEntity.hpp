#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

namespace AI {
	class StaticEntity : GameMessaging::Messageable<GameMessaging::MessageType, StaticEntity> {

	};

	bool StaticEntity::ReceiveMessage(const GameMessaging::Message<GameMessaging::MessageType, StaticEntity>& message) {

	}
}