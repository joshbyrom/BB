#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

#include "../motion/Kinematic.hpp"

#include "../../headers/Vector2D.h"

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	using Motion::Kinematic;

	class Entity : public Messageable<MessageType, Entity> {

	
	public:
		void update(double time);

		virtual bool Entity::ReceiveMessage(const Message<MessageType, Entity>& message) {

		}

	private:
		std::vector<Entity> children;

		Kinematic<Vector2D> * kinematic;
	};
}