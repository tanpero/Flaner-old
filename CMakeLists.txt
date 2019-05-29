cmake_minimum_required(VERSION 3.10)
project(Flaner)

add_subdirectory(compiler)
add_subdirectory(vm)
add_subdirectory(runtime)


# install(TARGETS FlanerCompiler DESTINATION bin)
# install(TARGETS FlanerVM DESTINATION bin)
# install(TARGETS FlanerRuntime DESTINATION lib)
