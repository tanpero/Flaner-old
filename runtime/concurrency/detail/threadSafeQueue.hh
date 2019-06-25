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

				private:
					std::shared_ptr<Node> getTail();
					std::unique_ptr<Node> popHead();
					std::unique_lock<std::mutex> waitForData();
					std::unique_ptr<Node> waitPopHead();
					std::unique_ptr<Node> waitPopHead(T& value);

				private:
					std::unique_ptr<Node> tryPopHead();
					std::unique_ptr<Node> tryPopHead(T& value);
					
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
					bool empty();
				};


				template<typename T>
				inline std::shared_ptr<T> ThreadSafeQueue<T>::tryPop()
				{
					std::unique_ptr<Node> oldHead = tryPopHead();
					return oldHead ? oldHead->data : std::shared_ptr<T>();
				}


				template<typename T>
				inline bool ThreadSafeQueue<T>::tryPop(T & value)
				{
					std::unique_ptr<Node> const oldHead = tryPopHead(value);
					return oldHead;
				}


				template<typename T>
				inline std::shared_ptr<T> ThreadSafeQueue<T>::waitAndPop()
				{
					std::unique_ptr<Node> const oldHead = waitPopHead();
					return oldHead->data;
				}


				template<typename T>
				inline void ThreadSafeQueue<T>::waitAndPop(T & value)
				{
					std::unique_ptr<Node> const oldHead = waitPopHead(value);
				}


				template<typename T>
				inline void ThreadSafeQueue<T>::push(T newValue)
				{
					std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
					std::unique_ptr<Node> p = std::make_unique<Node>();
					std::lock_guard<std::mutex> tailLock(tailMutex);
					tail->data = newData;
					std::shared_ptr<Node> const newTail = p.get();
					tail->next = std::move(p);
					tail = newTail;
					dataCond.notify_one();
				}


				template<typename T>
				inline bool ThreadSafeQueue<T>::empty()
				{
					std::lock_guard<std::mutex> headLock(headMutex);
					return head.get() == getTail();
				}


				template<typename T>				
				inline std::shared_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::getTail()
				{
					std::lock_guard<std::mutex> tailLock(tailMutex);
					return tail;
				}


				template<typename T>
				inline std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::popHead()
				{
					std::unique_ptr<typename ThreadSafeQueue<T>::Node> oldHead = std::move(head);
					head = std::move(oldHead->next);
					return oldHead;
				}


				template<typename T>
				inline std::unique_lock<std::mutex> ThreadSafeQueue<T>::waitForData()
				{
					std::unique_lock<std::mutex> headLock(headMutex);
					dataCond.wait(headLock, [&] {
						return head.get() != getTail();
					});
					return std::move(headLock);
				}


				template<typename T>
				inline std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::waitPopHead()
				{
					std::unique_lock<std::mutex> headLock(waitForData());
					return popHead();
				}


				template<typename T>
				inline std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::waitPopHead(T & value)
				{
					std::unique_lock<std::mutex> headLock(waitForData());
					value = std::move(*head->data);
					return popHead();
				}


				template<typename T>
				inline std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::tryPopHead()
				{
					std::lock_guard<std::mutex> headLock(headMutex);
					if (head.get() == getTail())
					{
						return std::unique_ptr<typename ThreadSafeQueue<T>::Node>();
					}
					return popHead();
				}


				template<typename T>
				inline std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::tryPopHead(T & value)
				{
					std::lock_guard<std::mutex> headLock(headMutex);
					if (head.get() == getTail())
					{
						return std::unique_ptr<typename ThreadSafeQueue<T>::Node>();
					}
					value = std::move(*head->data);
					return popHead();
				}
			}
		}
	}
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADSAFEQUEUE_HH_
