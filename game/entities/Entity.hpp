#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

#include "../motion/Kinematic.hpp"
#include "../space/Bounds.hpp"
#include "../flow/Updater.h"

#include "../../headers/Vector2D.h"

#include "Identity.h"

#include <math.h>

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	using FlowControl::Updater;
	using Motion::Kinematic;

	using Space::Bounds;

	class Entity : public Messageable<MessageType, Entity>, 
				   public Identity {
		public:
			Entity();
			~Entity();
			
			Vector2D GetPosition() const;

			virtual bool ReceiveMessage(const Message<MessageType, Entity>& message) {
				return true;
			}

			Bounds<Vector2D> GetBounds() const;

			Updater GetUpdater() const;
			Kinematic<Vector2D> GetKinematic() const;

			double GetAngleToEntity(Entity other) {
				Vector2D diff = GetPosition() - other.GetPosition();
				double result = atan2(diff.y, diff.x);
				return result < 0 ? result + TwoPi : result;
			}

			double GetDistanceToEntity(Entity other) {
				return GetPosition().Distance(other.GetPosition());
			}


			bool operator==(const Entity& rhs)const
			{
				return Identifiable::operator==(rhs) &&
					   GetKinematic() == rhs.GetKinematic() &&
					   GetBounds() == rhs.GetBounds();
			}
		protected:
			double width;
			double height;

			Kinematic<Vector2D> * kinematic;
			Bounds<Vector2D> * bounds;

			Updater * updater;

			void init();
	};

	void Entity::init() {
		updater = (new Updater([this] () {
			kinematic->Update((double) updater->Elapsed());

			bounds->Update(GetPosition(), width, height);
		}, 0, 0, 1))->WithInfiniteRepeats();
	}
	
	Entity::Entity() : kinematic(new Kinematic<Vector2D>()),
					   Messageable(), 
					   bounds(new Bounds<Vector2D>()), 
	                   width(0), height(0), updater(NULL) {
		init();
	}
	
	Entity::~Entity() {
		delete kinematic;
		delete bounds;
	}
	
	Vector2D Entity::GetPosition() const {
		return kinematic->GetPosition();
	}
	
	Bounds<Vector2D> Entity::GetBounds() const {
		return *bounds;
	}
	
	Kinematic<Vector2D> Entity::GetKinematic() const {
		return *kinematic;
	}
	
	Updater Entity::GetUpdater() const {
		return *updater;
	}
}

#endif