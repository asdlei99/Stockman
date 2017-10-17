#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicsObject.h"
#include "StatusManager.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <Misc/Sound/NoiseMachine.h>

namespace Logic
{
	class Entity : public PhysicsObject
	{
	public:
		Entity(btRigidBody* body, btVector3 halfExtent, Graphics::ModelID modelID = Graphics::ModelID::CUBE);
		Entity(const Entity& other) = delete;
		Entity* operator=(const Entity& other) = delete;
		virtual ~Entity();

		virtual void clear();
		virtual void update(float deltaTime);

		virtual void affect(int stacks, Effect const &effect, float deltaTime) = 0;
		virtual void upgrade(Upgrade const &upgrade);

		StatusManager& getStatusManager();
		void setStatusManager(StatusManager& statusManager);

		SoundSource* getSoundSource();

	private:
		SoundSource m_soundSource;
		StatusManager m_statusManager;
	};

	class Speaker : public Entity
	{
	public :
		Speaker(btRigidBody* body, btVector3 halfExtent, Graphics::ModelID modelID = Graphics::ModelID::CUBE)
			: Entity(body, halfExtent, modelID) { }
		void affect(int stacks, Effect const &effect, float deltaTime) { }
		void onCollision(PhysicsObject & other, btVector3 contactPoint, float multiplier) { }

	};
}

#endif // !ENTITY_H
