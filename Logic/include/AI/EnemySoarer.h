#ifndef ENEMY_SOARER_H
#define ENEMY_SOARER_H

#include "Enemy.h"
#include "Abilities\Ability.h"

namespace Logic
{
    class EnemySoarer : public Enemy
    {
        private:
            static const int HEALTH, DAMAGE;
            static const float SPEED, AB1_SPEED, HEIGHT_OFFSET;

            float ab2Speed;
            btVector3 dir;

            Ability ab1, ab2;
            btVector3 gravity;
        public:
            EnemySoarer(btRigidBody* body, btVector3 halfExtent);
            virtual ~EnemySoarer();

            virtual void createAbilities();

            virtual void onCollision(PhysicsObject& other, btVector3 contactPoint, float dmgMultiplier);

            virtual void updateSpecific(Player &player, float deltaTime);
            virtual void updateDead(float deltaTime);

            virtual void useAbility(Player &target);
    };
}

#endif