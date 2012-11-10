#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

#include "../motion/Kinematic.hpp"
#include "../space/Bounds.hpp"
#include "../Container.hpp"
#include "../flow/Updater.h"

#include "../../headers/Vector2D.h"

#include <math.h>

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	using FlowControl::Updater;
	using Motion::Kinematic;
	using Space::Bounds;

	class Entity : public Messageable<MessageType, Entity>, 
		           public Container<Entity> {
		public:
			Entity();
			Entity(Entity * parent);
			~Entity();

			Vector2D GetLocalPosition() const;
			Vector2D GetGlobalPosition() const;

			virtual bool Entity::ReceiveMessage(const Message<MessageType, Entity>& message) {
				return true;
			}

			Bounds<Entity, Vector2D> GetLocalBounds();
			Bounds<Entity, Vector2D> GetGlobalBounds();

			Kinematic<Vector2D> GetKinematic() const;

			double GetWidth();
			double GetHeight();

			double GetAngleToEntity(Entity other) {
				Vector2D diff = GetGlobalPosition() - other.GetGlobalPosition();
				double result = atan2(diff.y, diff.x);
				return result < 0 ? result + TwoPi : result;
			}

			double GetDistanceToEntity(Entity other) {
				return GetGlobalPosition().Distance(other.GetGlobalPosition());
			}


			bool Family(const Entity& other) { return GetParent() == other.GetParent(); }

			bool operator==(const Entity& rhs)const
			{
				return GetKinematic() == rhs.GetKinematic() &&
					   Container::operator==(rhs);
			}
		protected:
			double width;
			double height;

			Kinematic<Vector2D> * kinematic;
			Bounds<Entity, Vector2D> * localBounds;
			Bounds<Entity, Vector2D> * globalBounds;

			Updater * updater;

			void init();
	};

	void Entity::init() {


		if(parent) {
			parent->AddChild(*this);
		}
	}

	Entity::Entity() : kinematic(new Kinematic<Vector2D>()),
					   Messageable(), Container(),
					   localBounds(NULL), globalBounds(NULL),
	                   width(0), height(0), updater(NULL) {
		init();
	}

	Entity::Entity(Entity * parent) 
		: kinematic(new Kinematic<Vector2D>()),
		  Messageable(), Container(parent),
		  localBounds(NULL), globalBounds(NULL),
	      width(0), height(0) {
		init();
	}

	Entity::~Entity() {
		delete kinematic;
		delete localBounds;
		delete globalBounds;
	}

	Vector2D Entity::GetLocalPosition() const {
		return kinematic->GetPosition();
	}

	Vector2D Entity::GetGlobalPosition() const {
		Vector2D result = GetLocalPosition();

		Entity * ancestor = GetParent();
		while(ancestor) {
			result += ancestor->GetLocalPosition();
			ancestor = ancestor->GetParent();
		}

		return result;
	}

	double Entity::GetWidth() {
		return Sum ([] (Entity e) -> double {
			return e.GetWidth();
		});
	}

	double Entity::GetHeight() {
		return Sum ([] (Entity e) -> double {
			return e.GetHeight();
		});
	}

	Bounds<Entity, Vector2D> Entity::GetLocalBounds() {
		if(localBounds) return *localBounds;

		localBounds = new Bounds<Entity, Vector2D>(*this, [this] () -> Vector2D {
			return this->GetLocalPosition();
		});

		return GetLocalBounds();
	}

	Bounds<Entity, Vector2D> Entity::GetGlobalBounds() {
		if(globalBounds) return *globalBounds;

		globalBounds = new Bounds<Entity, Vector2D>(*this, [this] () -> Vector2D {
			return this->GetGlobalPosition();
		});

		return GetLocalBounds();
	}

	Kinematic<Vector2D> Entity::GetKinematic() const {
		return *kinematic;
	}
}