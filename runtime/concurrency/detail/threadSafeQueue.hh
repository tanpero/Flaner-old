#ifndef _FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADSAFEQUEUE_HH_
#define _FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADSAFEQUEUE_HH_

#include <global.hh>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace Flaner
{
	namespace Runtime
	{
		namespace Concurrency
		{
			namespace detail
			{
				template <typename T>
				class ThreadSafeQueue
				{
					struct Node
					{
						std::shared_ptr<T> data;
						std::unique_ptr<Node> next;
					};
					
					std::mutex headMutex;
					std::unique_ptr<Node> head;
					std::mutex tailMutex;
					std::shared_ptr<Node> tail;
					std::condition_variable dataCond;

				public:
					ThreadSafeQueue() :
						head(std::make_unique<Node>()), tail(head->get())
					{}
					ThreadSafeQueue(const ThreadSafeQueue& other) = delete;
					ThreadSafeQueue& operator=(const ThreadSafeQueue& other) = delete;

					std::shared_ptr<T> tryPop();
					bool tryPop(T& value);
					std::shared_ptr<T> waitAndPop();
					void waitAndPop(T& value);
					void push(T newValue);
					void empty();
				};

				template<typename T>
				inline std::shared_ptr<T> ThreadSafeQueue<T>::tryPop()
				{
					
				}

				template<typename T>
				inline bool ThreadSafeQueue<T>::tryPop(T & value)
				{
					return false;
				}

				template<typename T>
				inline std::shared_ptr<T> ThreadSafeQueue<T>::waitAndPop()
				{
					return std::shared_ptr<T>();
				}

				template<typename T>
				inline void ThreadSafeQueue<T>::waitAndPop(T & value)
				{
				}

				template<typename T>
				inline void ThreadSafeQueue<T>::push(T newValue)
				{
					std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
					std::unique_ptr<Node> p = std::make_unique<Node>();
					std::lock_guard<std::mutex> tailLock(tailMutex);
					tail->
				}

				template<typename T>
				inline void ThreadSafeQueue<T>::empty()
				{
				}
			}
		}
	}
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADSAFEQUEUE_HH_
