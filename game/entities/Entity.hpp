#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

#include "../motion/Kinematic.hpp"
#include "../space/Bounds.hpp"
#include "../Container.hpp"

#include "../../headers/Vector2D.h"

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	using Motion::Kinematic;
	using Space::Bounds;

	class Entity : public Messageable<MessageType, Entity>, 
		           public Container<Entity> {
	public:
		Entity();
		Entity(Entity * parent);
		~Entity();

		void update(double time);

		Vector2D GetLocalPosition() const;
		Vector2D GetGlobalPosition() const;

		virtual bool Entity::ReceiveMessage(const Message<MessageType, Entity>& message) {
			return true;
		}


		double GetWidth();
		double GetHeight();
	private:
		double width;
		double height;

		Kinematic<Vector2D> * kinematic;
	};

	Entity::Entity() : kinematic(new Kinematic<Vector2D>()),
					   Messageable(), Container(),
	                   width(0), height(0) {

	}

	Entity::Entity(Entity * parent) 
		: kinematic(new Kinematic<Vector2D>()),
		  Messageable(), Container(parent),
	      width(0), height(0) {
	}

	Entity::~Entity() {
		delete kinematic;
	}

	Vector2D Entity::GetLocalPosition() const {
		return kinematic->GetPosition();
	}

	Vector2D Entity::GetGlobalPosition() const {
		if(GetParent()) return GetLocalPosition() + GetParent()->GetGlobalPosition();
		else return GetLocalPosition();
	}
}