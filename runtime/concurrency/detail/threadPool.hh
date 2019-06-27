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
					ThreadSafeQueue<TaskType> poolWorkQueue;
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

				inline bool ThreadPool::popTaskFromLocalQueue(TaskType & task)
				{
					return localWorkQueue && localWorkQueue->tryPop(task);
				}

				inline bool ThreadPool::popTaskFromPoolQueue(TaskType & task)
				{
					return poolWorkQueue.tryPop(task);
				}

				inline bool ThreadPool::popTaskFromOtherThreadQueue(TaskType & task)
				{
					for (unsigned int i = 0; i < queues.size(); i++)
					{
						const unsigned int index = (myIndex + i + 1) % queues.size();
						if (queues[index]->trySteal(task))
						{
							return true;
						}
					}
					return false;
				}

				inline void ThreadPool::runPendingTask()
				{
					TaskType task;
					if (popTaskFromLocalQueue(task) ||
						popTaskFromPoolQueue(task) ||
						popTaskFromOtherThreadQueue(task))
					{
						task();
					}
					else
					{
						std::this_thread::yield();
					}
				}

				template<typename FunctionType>
				inline std::future<typename std::result_of<FunctionType()>::type> ThreadPool::submit(FunctionType f)
				{
					using ResultType = typename std::result_of<FunctionType()>::type;

					std::packaged_task<ResultType()> task(f);
					std::future<ResultType> res(task.get_future());
					if (localWorkQueue)
					{
						localWorkQueue->push(std::move(task));
					}
					else
					{
						poolWorkQueue.push(std::move(tasl));
					}
					return res;
				}
			}
        }
    }
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_
