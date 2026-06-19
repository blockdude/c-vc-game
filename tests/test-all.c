#undef INSTANTIATE_MAIN
#include "test-vec2.c"
#include "test-vec3.c"
#include "test-mat4.c"
#include "test-quat.c"
#include "test-timestep.c"
#include "test-clock.c"
#define INSTANTIATE_MAIN

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
