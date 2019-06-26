#ifndef _FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_
#define _FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_

#include <global.hh>
#include <workStealingQueue.hh>
#include <threadSafeQueue.hh>
#include <joinThreads.hh>
#include <atomic>
#include <vector>
#include <future>

namespace Flaner
{
    namespace Runtime
    {
        namespace Concurrency
        {
            namespace detail
            {
                class ThreadPool
                {
					using TaskType = FunctionWrapper;
					
					std::atomic_bool done;
					ThreadSafeQueue<TaskType> pollWorkQueue;
					std::vector<std::unique_ptr<WorkStealingQueue>> queues;
					std::vector<std::thread> threads;
					JoinThreads joiner;

					static thread_local std::shared_ptr<WorkStealingQueue> localWorkQueue;
					static thread_local unsigned int myIndex;

					void workThread(unsigned int myIndex);
					bool popTaskFromLocalQueue(TaskType& task);
					bool popTaskFromPoolQueue(TaskType& task);
					bool popTaskFromOtherThreadQueue(TaskType& task);
					
				public:
					ThreadPool() :
						done(false), joiner(threads)
					{
						unsigned int const threadCount = std::thread::hardware_concurrency();

						try
						{
							for (unsigned int i = 0; i < threadCount; i++)
							{
								queues.push_back(std::make_unique<WorkStealingQueue>());
								threads.push_back(std::thread(&ThreadPool::workThread, this, i));
							}
						}
						catch (...)
						{
							done = true;
							throw;
						}
					}

					~ThreadPool()
					{
						done = true;
					}

					template <typename FunctionType>
					std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f);
					void runPendingTask();
                };

				void ThreadPool::workThread(unsigned int _myIndex)
				{
					myIndex = _myIndex;
					localWorkQueue = std::make_shared<WorkStealingQueue>(queues[myIndex].get());
					while (!done)
					{
						runPendingTask();
					}
				}
            }
        }
    }
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_
