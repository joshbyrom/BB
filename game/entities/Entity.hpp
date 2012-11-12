#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../messaging/Message.hpp"
#include "../messaging/Messageable.hpp"
#include "../messaging/MessageTypes.h"
#include "../messaging/MessageDispatcher.hpp"

#include "../motion/Kinematic.hpp"
#include "../space/Bounds.hpp"
#include "../Container.hpp"
#include "../flow/Updater.h"

#include "../../headers/Vector2D.h"

#include "Identifiable .h"

#include <math.h>

namespace AI {
	using GameMessaging::Messageable;
	using GameMessaging::MessageType;
	using GameMessaging::Message;

	using FlowControl::Updater;
	using Motion::Kinematic;
	using Space::Bounds;

	class Entity : public Messageable<MessageType, Entity>, 
		           public Container<Entity>,
				   public Identifiable {
		public:
			Entity();
			Entity(Entity * parent);
			~Entity();

			Vector2D GetLocalPosition() const;
			Vector2D GetGlobalPosition() const;

			virtual bool Entity::ReceiveMessage(const Message<MessageType, Entity>& message) {
				return true;
			}

			Bounds<Vector2D> GetLocalBounds() const;
			Bounds<Vector2D> GetGlobalBounds() const;

			Updater GetUpdater() const;
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
				return Identifiable::operator==(rhs) &&
					   GetKinematic() == rhs.GetKinematic() &&
					   GetLocalBounds() == rhs.GetLocalBounds() &&
					   GetGlobalBounds() == rhs.GetGlobalBounds() &&
					   Container::operator==(rhs);
			}

			void AddChild(const Entity& e) override {
				Container::AddChild(e);
				updater->AddChild(e.GetUpdater());
			}

			void RemoveChild(const Entity& e) override {
				Container::RemoveChild(e);
				updater->RemoveChild(e.GetUpdater());
			}

			Entity GetChildByID(const UINT& id) {
				Entity result = NULL;

				Map([&] (Entity entity) {
					if(entity.GetID() == id) {
						result = entity;
						return;
					}
				});

				return result;
			}
		protected:
			double width;
			double height;

			Kinematic<Vector2D> * kinematic;
			Bounds<Vector2D> * localBounds;
			Bounds<Vector2D> * globalBounds;

			Updater * updater;

			void init();
	};

	void Entity::init() {
		updater = (new Updater([this] () {
			kinematic->Update((double) updater->Elapsed());

			localBounds->Update(GetLocalPosition(), width, height);
			globalBounds->Update(GetGlobalPosition(), GetWidth(), GetHeight());
		}, 0, 0, 1))->WithInfiniteRepeats();

		localBounds = new Bounds<Vector2D>();
		globalBounds = new Bounds<Vector2D>();

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

	Bounds<Vector2D> Entity::GetLocalBounds() const {
		return *localBounds;
	}

	Bounds<Vector2D> Entity::GetGlobalBounds() const {
		return *globalBounds;
	}

	Kinematic<Vector2D> Entity::GetKinematic() const {
		return *kinematic;
	}

	Updater Entity::GetUpdater() const {
		return *updater;
	}
}

#endif