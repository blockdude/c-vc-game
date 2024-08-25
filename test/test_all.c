#undef INSTANTIATE_MAIN
#include "test_list.c"
#include "test_mesh.c"
#include "test_kdtree.c"
#define INSTANTIATE_MAIN

#ifdef INSTANTIATE_MAIN
UTEST_MAIN()
#endif
