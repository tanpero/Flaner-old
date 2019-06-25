#ifndef _FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_
#define _FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_

#include <global.hh>
#include <workStealingQueue.hh>
#include <atomic>
#include <vector>

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
					
                };
            }
        }
    }
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_THREADPOOL_HH_
