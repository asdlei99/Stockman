#ifndef ENEMY_THREAD_HANDLER_H
#define ENEMY_THREAD_HANDLER_H

#include <thread>

namespace Logic
{
    class EntityManager;
    class Player;

    class EnemyThreadHandler
    {
    private:
        static const int NR_OF_THREADS = 8;

        std::thread *threads[NR_OF_THREADS];
        int m_indexRunning[NR_OF_THREADS];
        bool m_threadRunning[NR_OF_THREADS];

        bool m_killChildren;
    public:
        // Why locked and running? Locked means i % NR_OF_THREADS is locked
        // while running means that index i is currently being updated
        struct WorkData
        {
            EntityManager *manager;
            int index;
            Player const &player;
        };

        enum ThreadStatus
        {
            LOCKED = 0x1,
            RUNNING = 0x2,
            OPEN = 0x4
        };

        EnemyThreadHandler();
        ~EnemyThreadHandler();

        void updateEnemiesAndPath(WorkData &data);
        void threadMain(WorkData data);

        void addWork(WorkData data);

        void resetThreads();
        void deleteThreads();

        inline int getThreadId(int i)
        {
            return i % NR_OF_THREADS;
        }
        int getThreadStatus(int i);
    };
}

#endif