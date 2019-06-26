#ifndef _FLANER_RUNTIME_CONCURRENCY_DETAIL_JOINTHREADS_HH_
#define _FLANER_RUNTIME_CONCURRENT_DETAIL_JOINTHREADS_HH_

#include <global.hh>
#include <vector>
#include <thread>

namespace Flaner
{
	namespace Runtime
	{
		namespace Concurrency
		{
			namespace detail
			{
				class JoinThreads
				{
					std::vector<std::thread>& threads;

				public:
					explicit JoinThreads(std::vector<std::thread>& _threads)
						: threads(_threads)
					{}
					~JoinThreads()
					{
						for (unsigned long i = 0; i < threads.size(); i++)
						{
							if (threads[i].joinable())
							{
								threads[i].join();
							}
						}
					}
				};
			};
		};
	};
};

#endif // !_FLANER_RUNTIME_CONCURRENT_DETAIL_JOINTHREADS_HH_