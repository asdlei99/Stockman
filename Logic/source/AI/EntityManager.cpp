#include <AI/EntityManager.h>
using namespace Logic;

#define ENEMIES_PATH_UPDATE_PER_FRAME 25
#define ENEMIES_TEST_UPDATE_PER_FRAME 25 
#define FILE_ABOUT_WHALES "Enemies/Wave"

#include <AI\Behavior\EnemyThreadHandler.h>
#include <AI\Behavior\AStar.h>
#include <AI\EnemyTest.h>
#include <AI\EnemyNecromancer.h>
#include <AI\EnemyChaser.h>
#include <Misc\ComboMachine.h>

#include <Player\Player.h>
#include <Projectile\ProjectileManager.h>

#include <Graphics\include\Renderer.h>
#include <Graphics\include\Structs.h>
#include <Physics\Physics.h>

#include <DebugDefines.h>
#include <Engine\Profiler.h>
#include <Misc\RandomGenerator.h>

#include <ctime>
#include <stdio.h>

const int EntityManager::NR_OF_THREADS = 4;

EntityManager::EntityManager()
{
    m_frame = 0;

    allocateData();

    m_waveManager.setName(FILE_ABOUT_WHALES);
    m_waveManager.loadFile();
}

EntityManager::~EntityManager()
{
    delete m_threadHandler;
    deleteData();
}

void EntityManager::allocateData()
{
    m_enemies.resize(AStar::singleton().getNrOfPolygons());
    m_threadHandler = newd EnemyThreadHandler();
}

void EntityManager::deleteData()
{
    for (std::vector<Enemy*> list : m_enemies)
        for (Enemy *enemy : list)
            delete enemy;
    for (Enemy *enemy : m_deadEnemies)
        delete enemy;
}

void EntityManager::update(Player const &player, float deltaTime)
{
	m_frame++;
	m_deltaTime = deltaTime;
	
	PROFILE_BEGIN("EntityManager::update()");
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i].size() > 0)
		{
			updateEnemies(i, player, deltaTime);
            if ((i + m_frame) % ENEMIES_PATH_UPDATE_PER_FRAME == 0) 
            {
                PROFILE_BEGIN("ThreadHandler::addWork");
                m_threadHandler->addWork({ this, static_cast<int> (i), player });
                PROFILE_END();
            }
		}
	}
	PROFILE_END();

	for (int i = 0; i < m_deadEnemies.size(); ++i)
	{
		m_deadEnemies[i]->updateDead(deltaTime);
	}


	m_triggerManager.update(deltaTime);
}
void EntityManager::updateEnemies(int index, Player const &player, float deltaTime)
{
	bool goalNodeChanged = false;
    bool swapOnNewIndex = !(m_threadHandler->getThreadStatus(index) & EnemyThreadHandler::RUNNING);
	Enemy *enemy;
    std::vector<Enemy*> &enemies = m_enemies[index];
	
	for (size_t i = 0; i < enemies.size(); ++i)
	{
        updateEnemy(enemies[i], enemies, i, index, player, deltaTime, swapOnNewIndex);
	}
}

void EntityManager::updateEnemy(Enemy *enemy, std::vector<Enemy*> &flock, 
    int enemyIndex, int flockIndex, Player const &player, float deltaTime, bool swapOnNewIndex)
{
    enemy->update(player, deltaTime, flock);

    if (swapOnNewIndex && !AStar::singleton().isEntityOnIndex(*enemy, flockIndex))
    {
        int newIndex = AStar::singleton().getIndex(*enemy);
        std::swap(
            flock[enemyIndex],
            flock[flock.size() - 1]
        );
        flock.pop_back();

        m_enemies[newIndex == -1 ? 0 : newIndex].push_back(enemy);
    }
    else if (enemy->getHealth() <= 0)
    {
        std::swap(
            flock[enemyIndex],
            flock[flock.size() - 1]
        );

        m_deadEnemies.push_back(enemy);
        flock.pop_back();
    }
}

void EntityManager::spawnWave(int waveId)
{
    if (m_enemies.empty())
    {
        printf("This will crash, data is not allocated, call allocateData() before spawning");
        return;
    }

    WaveManager::EntitiesInWave entities = m_waveManager.getEntities(waveId);
    m_frame = 0;

    btVector3 pos;
    RandomGenerator &generator = RandomGenerator::singleton();

    for (int entity : entities.enemies)
    {
        // just temp test values as of now, better with no random spawns?
        // should atleast check if spawn area is a walkable area
        // using nav mesh that would be easy but not trivial
        pos = { generator.getRandomFloat(-85, 85), generator.getRandomFloat(10, 25),
            generator.getRandomFloat(-85, 85) };

        SpawnEnemy(static_cast<ENEMY_TYPE> (entity), pos, {});
    }

    for (WaveManager::Entity e : entities.triggers)
        SpawnTrigger(e.id, { e.x, e.y, e.z }, e.effects);

    for (WaveManager::Entity e : entities.bosses)
        SpawnEnemy(static_cast<ENEMY_TYPE> (e.id), btVector3{ e.x, e.y, e.z }, e.effects);
}

Enemy* EntityManager::spawnEnemy(ENEMY_TYPE id, btVector3 const &pos,
    std::vector<int> const &effects, Physics &physics, ProjectileManager *projectiles)
{
    Enemy *enemy;
    int index;
    btRigidBody *testBody = physics.createBody(Sphere({ pos }, { 0, 0, 0 }, 1.f), 100, false);

    switch (id)
    {
    case ENEMY_TYPE::NECROMANCER:
        enemy = newd EnemyNecromancer(testBody, { 0.5f, 0.5f, 0.5f });
        break;
    case ENEMY_TYPE::NECROMANCER_MINION:
        enemy = newd EnemyChaser(testBody);
        break;
    default:
        enemy = newd EnemyTest(testBody, { 0.5f, 0.5f, 0.5f });
		break;
    }

    enemy->setEnemyType(id);
    enemy->addExtraBody(physics.createBody(Sphere({ 0, 0, 0 }, { 0, 0, 0 }, 1.f), 0.f, true, Physics::COL_ENEMY), 2.f, { 0.f, 3.f, 0.f });

    enemy->setSpawnFunctions(SpawnProjectile, SpawnEnemy, SpawnTrigger);

#ifdef DEBUG_PATH
    enemy->getBehavior()->getPath().initDebugRendering(); // todo change to enemy->initDebugPath()
#endif

    index = AStar::singleton().getIndex(*enemy);
    m_enemies[index == -1 ? 0 : index].push_back(enemy);

    return enemy;
}

Trigger* EntityManager::spawnTrigger(int id, btVector3 const &pos,
    std::vector<int> &effects, Physics &physics, ProjectileManager *projectiles)
{
    // this is unefficient, could prolly be optimized but should only be done once per wave load
    std::vector<StatusManager::EFFECT_ID> effectsIds;
    effectsIds.reserve(effects.size());
    for (auto const &effect : effects)
        effectsIds.push_back(static_cast<StatusManager::EFFECT_ID> (effect));
    Trigger *trigger;

    switch (id)
    {
    case 1: // wtf, starts at 1
        trigger = m_triggerManager.addTrigger(Resources::Models::UnitCube,
            Cube(pos, { 0, 0, 0 }, { 2, 0.1f, 2 }),
            500.f, physics, {},
            effectsIds,
            true);
        break;
    case 2:
        trigger = m_triggerManager.addTrigger(Resources::Models::UnitCube,
            Cube(pos, { 0, 0, 0 }, { 1, 0.5, 1 }), 0.f, physics, {},
            effectsIds,
            false);
        break;
    default:
        trigger = nullptr;
    }

    return trigger;
}

size_t EntityManager::getNrOfAliveEnemies() const
{
    return m_enemies.size();
}

void EntityManager::clear()
{
    deleteData();

    m_deadEnemies.clear();
    m_enemies.clear();
}

int EntityManager::giveEffectToAllEnemies(StatusManager::EFFECT_ID id)
{
    int i = 0;
    for (auto &vec : m_enemies)
        for (auto *enemy : vec)
        {
            enemy->getStatusManager().addStatus(id, 1, true);
            i++;
        }
    return i;
}

void EntityManager::render()
{
    for (int i = 0; i < m_enemies.size(); ++i)
    {
        for (Enemy *enemy : m_enemies[i])
        {
            enemy->render();
#ifdef DEBUG_PATH	
            enemy->debugRendering();
#endif
        }
    }

    for (int i = 0; i < m_deadEnemies.size(); ++i)
    {
#ifndef DISABLE_RENDERING_DEAD_ENEMIES
        m_deadEnemies[i]->render();
#endif
    }

    m_triggerManager.render();

#ifdef DEBUG_ASTAR
    AStar::singleton().renderNavigationMesh();
#endif
}

const std::vector<std::vector<Enemy*>>& EntityManager::getAliveEnemies() const
{
    return m_enemies;
}

const WaveManager& Logic::EntityManager::getWaveManager() const
{
    return m_waveManager;
}

void EntityManager::setSpawnFunctions(ProjectileManager &projManager, Physics &physics)
{
    SpawnEnemy = [&](ENEMY_TYPE type, btVector3 &pos, std::vector<int> effects) -> Enemy* {
        return spawnEnemy(type, pos, effects, physics, &projManager);
    };
    SpawnProjectile = [&](ProjectileData& pData, btVector3 position,
        btVector3 forward, Entity& shooter) -> Projectile* {
        return projManager.addProjectile(pData, position, forward, shooter);
    };
    SpawnTrigger = [&](int id, btVector3 const &pos, std::vector<int> &effects) -> Trigger* {
        return spawnTrigger(id, pos, effects, physics, &projManager);
    };
}
