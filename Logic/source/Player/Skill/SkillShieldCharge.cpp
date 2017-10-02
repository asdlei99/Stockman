#include "Player/Skill/SkillShieldCharge.h"

using namespace Logic;

SkillShieldCharge::SkillShieldCharge(ProjectileManager * projectileManager, ProjectileData projectileData)
: Skill(SHIELD_CHARGE_CD, SHIELD_CHARGE_DURATION)
{
	m_projectileManager = projectileManager;
	m_projectileData = projectileData;
}

SkillShieldCharge::~SkillShieldCharge()
{
	m_projectileManager = nullptr;
}

void SkillShieldCharge::onUse(btVector3 forward, Entity& shooter)
{
	printf("Used Shield Charge.\n");
}

void SkillShieldCharge::onRelease() { }

void SkillShieldCharge::onUpdate(float deltaTime)
{

}

void SkillShieldCharge::render(Graphics::Renderer& renderer)
{

}