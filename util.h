#ifndef UTIL_STUFF
#define UTIL_STUFF

float magnitude         ( float x, float y );
void normalize          ( float x, float y, float *x_out, float *y_out );
float min               ( float a, float b );
float max               ( float a, float b );
float clamp             ( float val, float min, float max );

void split_color        ( int color, char *r, char *g, char *b, char *a );

void center_pos         ( float x, float y, float *x_out, float *y_out );
float center_x          ( float x );
float center_y          ( float y );

#endif
