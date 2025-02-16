#undef INSTANTIATE_MAIN
#include "test-kdtree.c"
#include "test-list.c"
#include "test-mesh.c"
#include "test-util.c"
#define INSTANTIATE_MAIN

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
