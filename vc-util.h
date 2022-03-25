#ifndef VC_UTIL
#define VC_UTIL

float min           ( float a, float b );
float max           ( float a, float b );
float clamp         ( float val, float a, float b );

float magnitude     ( float x, float y );
void normalize      ( float *x, float *y );

void split_color    ( int color, char *r, char *g, char *b, char *a );

#endif
