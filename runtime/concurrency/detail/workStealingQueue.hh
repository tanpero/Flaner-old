#ifndef _FLANER_RUNTIME_CONCURRENCY_DETAIL_WORJKSTEALINGQUEUE_HH_
#define _FLANER_RUNTIME_CONCURRENCY_DETAIL_WORJKSTEALINGQUEUE_HH_

#include <global.hh>
#include <functionWrapper.hh>
#include <deque>
#include <mutex>

namespace Flaner
{
    namespace Runtime
    {
        namespace Concurrency
        {
            namespace detail
            {
                class WorkStealingQueue
                {
                    std::deque<FunctionWrapper> theQueue;
                    mutable std::mutex theMutex;

                public:
                    WorkStealingQueue()
                    {}

                    WorkStealingQueue(const WorkStealingQueue& other) = delete;
                    WorkStealingQueue& operator=
                        (const WorkStealingQueue& other) = delete;

                    void push(FunctionWrapper data)
                    {
                        std::lock_guard<std::mutex> lock(theMutex);
                        theQueue.push_front(std::move(data));
                    }

                    bool isEmpty() const
                    {
                        std::lock_guard<std::mutex> lock(theMutex);
                        return theQueue.empty();
                    }

                    bool tryPop(FunctionWrapper& res)
                    {
                        std::lock_guard<std::mutex> lock(theMutex);
                        if (theQueue.empty())
                        {
                            return false;
                        }
                        res = std::move(theQueue.front());
                        theQueue.pop_front();
                        return true;
                    }

                    bool trySteal(FunctionWrapper& res)
                    {
                        std::lock_guard<std::mutex> lock(theMutex);
                        if (theQueue.empty())
                        {
                            return false;
                        }
                        res = std::move(theQueue.back());
                        theQueue.pop_back();
                        return true;
                    }
                };
            }
        }
    }
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_WORJKSTEALINGQUEUE_HH_
