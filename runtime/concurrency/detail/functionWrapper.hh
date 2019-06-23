#ifndef _FLANER_RUNTIME_CONCURRENCY_DETAIL_FUNCTIONWRAPPER_HH_
#define _FLANER_RUNTIME_CONCURRENT_DETAIL_FUNCTIONWRAPPER_HH_

#include <global.hh>
#include <memory>

namespace Flaner
{
    namespace Runtime
    {
        namespace Concurrency
        {
            namespace detail
            {
                class FunctionWrapper
                {
                    struct ImplBase
                    {
                        virtual void call() = 0;
                        virtual ~ImplBase() {}
                    };

                    std::shared_ptr<ImplBase> implBase;

                    template <typename F>
                    struct ImplType : ImplBase
                    {
                        F f;
                        ImplType(F&& _f) : f(std::move(_f)) {}
                        void call()
                        {
                            f();
                        }
                    };

                public:
                    template <typename F>
                    FunctionWrapper(F&& f) :
                        implBase(new ImplType<F>(std::move(f)))
                    {}
                    void operator()()
                    {
                        implBase->call();
                    }
                    FunctionWrapper() = default;
                    FunctionWrapper(FunctionWrapper&& other) :
                        implBase(std::move(other.implBase))
                    {}
                    FunctionWrapper& operator=(FunctionWrapper&& other)
                    {
                        implBase = std::move(other.implBase);
                        return *this;
                    }
                    FunctionWrapper(const FunctionWrapper&) = delete;
                    FunctionWrapper(FunctionWrapper&) = delete;
                    FunctionWrapper& operator=(const FunctionWrapper&) = delete;
                };
            }
        }
    }
}

#endif // !_FLANER_RUNTIME_CONCURRENCY_DETAIL_FUNCTIONWRAPPER_HH_
