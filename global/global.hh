#ifndef _FLANER_GLOBAL_GLOBAL_HH_
#define _FLANER_GLOBAL_GLOBAL_HH_

namespace Flaner
{
    namespace Global
    { 
    
    };

    namespace Compiler
    {

    };

    namespace VM
    {

    };

    namespace Runtime
    {

    };
};

#ifdef FLANER_DEBUG
#include <cstdio>
#define debug(s) printf("%s\n", s)
#else
#define debug(s) // 
#endif // !DEBUG



#endif // !_FLANER_COMPILER_GLOBAL_HH_
