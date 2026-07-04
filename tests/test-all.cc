#undef INSTANTIATE_MAIN
#include "test-vec2.cc"
#include "test-vec3.cc"
#include "test-mat4.cc"
#include "test-quat.cc"
#include "test-clock.cc"
#define INSTANTIATE_MAIN

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
