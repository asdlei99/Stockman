#include <Player\Weapon\WeaponMeleeSwing.h>
#include <Projectile\Projectile.h>
#include <AI\Enemy.h>

using namespace Logic;

WeaponMeleeSwing::WeaponMeleeSwing() : m_knockbackPower(0.f) { }

WeaponMeleeSwing::WeaponMeleeSwing(ProjectileManager * projectileManager, ProjectileData & projectileData, WeaponInfo wInfo, float knockbackPower)
    : Weapon(projectileManager, projectileData, wInfo)
{
    m_knockbackPower = knockbackPower;
}

WeaponMeleeSwing::~WeaponMeleeSwing() { }

void WeaponMeleeSwing::onUse(std::vector<Projectile*>& projectiles, Entity& shooter)
{
    shooter.getSoundSource()->playSFX(Sound::SFX::WEAPON_MELEE_PRIMARY);

    static btVector3 pPosition;
    for (Projectile* p : projectiles)
    {
        pPosition = shooter.getPositionBT();
        p->addCallback(Entity::ON_COLLISION, [&](Entity::CallbackData &data) -> void {

            PhysicsObject* obj = reinterpret_cast<PhysicsObject*>(data.dataPtr);
            btVector3 knockbackDir = (obj->getPositionBT() - pPosition).normalize() + btVector3(0, 1, 0);

            if (Enemy* enemy = dynamic_cast<Enemy*>(obj))
            {
                obj->getRigidBody()->setLinearVelocity(knockbackDir * m_knockbackPower);
                enemy->getStatusManager().addStatusResetDuration(StatusManager::EFFECT_ID::STUN, 1);
            }
        });
    }
}