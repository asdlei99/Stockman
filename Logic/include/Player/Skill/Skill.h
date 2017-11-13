#ifndef SKILL_H
#define SKILL_H
#pragma region ClassDesc
		/*
			CLASS: Skill
			AUTHOR:

			DESCRIPTION: This class defines a skill of the system
		*/
#pragma endregion
#include <Graphics\include\RenderQueue.h>

#include <btBulletCollisionCommon.h>
#include <Entity/StatusManager.h>

namespace Graphics
{
    class Renderer;
}

namespace Logic
{
    class Entity;

	class Skill
	{
	public:
		Skill(float cooldown, float duration = 0.f);
		virtual ~Skill();

		void use(btVector3 forward, Entity& shooter);
		virtual bool onUse(btVector3 forward, Entity& shooter) = 0;

		void release();
		virtual void onRelease() = 0;
		
		void update(float deltaTime);
        void affect(Effect const & effect);
		virtual void onUpdate(float deltaTime) = 0;
        virtual void onAffect(Effect const & effect) = 0;

		float	getCooldown() const;
		float	getCooldownMax() const;
		float	getDuration() const;
		float	getDurationMax() const;
		bool	getCanUse() const;

		void setCooldown(float cooldown);
        void setCooldownMax(float cooldownMax);
		void setCanUse(bool canUse);

        virtual void render() const = 0;

	private:
		// StatusManager statusManager;
		float	m_cooldown;
		float	m_cooldownMax;
        float   m_cooldownModifer;
		float	m_duration;
		float	m_durationMax;
		bool	m_canUse;
        bool    m_active;
	};
}
#endif
