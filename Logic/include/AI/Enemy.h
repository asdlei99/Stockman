#ifndef ENEMY_H
#define ENEMY_H

#include <Entity\Entity.h>
#include <Player\Player.h>
#include <AI\Behavior\Behavior.h>

#pragma region Comment
/*
	CLASS: Enemy
	AUTHOR: Lukas Westling

	This class handles the Enemy and
	its flags is handled by EntityManager

	But wait? Why cant i check if an enemy is dead???
	That is because that is very slow and waste of cachelines!

	! changing this = bad performence !
*/
#pragma endregion ClassDesc

namespace Logic 
{
	class Enemy : public Entity 
	{
		private:
			float m_health, m_maxHealth, m_baseDamage, m_moveSpeed; // Base
			float m_moveSpeedMod;									// Variables for effect modifiers
			int m_enemyType;
			// Animation m_animation;
		public:	
			Enemy(btRigidBody* body, btVector3 halfExtent, float maxHealth, float baseDamage, float moveSpeed, int enemyType, int animationId);
			virtual ~Enemy();

			virtual void update(Player const &player, float deltaTime);
			virtual void updateDead(float deltaTime) = 0;
			virtual void updateSpecific(Player const &player, float deltaTime) = 0;

			virtual void affect(int stacks, Effect const &effect, float dt);
			void damage(float damage);

			float getHealth() const;
			float getMaxHealth() const;
			float getBaseDamage() const;
			float getMoveSpeed() const;
			int getEnemyType() const;
		protected: //for testing
			Logic::Behavior *m_behavior;
	};
}

#endif