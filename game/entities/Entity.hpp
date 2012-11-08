#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

#include "../motion/Kinematic.hpp"

#include "../Container.hpp"

#include "../../headers/Vector2D.h"

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	using Motion::Kinematic;

	class Entity : public Messageable<MessageType, Entity>, 
		           public Container<Entity> {

	
	public:
		void update(double time);

		Vector2D GetLocalPosition() const;
		Vector2D GetGlobalPosition() const;

		virtual bool Entity::ReceiveMessage(const Message<MessageType, Entity>& message) {

		}

	private:
		Kinematic<Vector2D> * kinematic;
	};

	Vector2D Entity::GetLocalPosition() const {
		return kinematic->GetPosition();
	}

	Vector2D Entity::GetGlobalPosition() const {
		if(GetParent()) return GetLocalPosition() + GetParent()->GetGlobalPosition();
		else return GetLocalPosition();
	}
}