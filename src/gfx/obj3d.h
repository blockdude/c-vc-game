#ifndef OBJ3D_H
#define OBJ3D_H

/*
 * WaveFront object file loader.
 */

#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <stddef.h>

struct vert
{
	vec3s v;
	vec2s vt;
	vec3s vn;
};

struct obj3d
{
	// dynarrs
	struct vert *f;		/* vertices (v, vt, and vn)       */
	vec3s *v;			/* vertex positions		x, y, z   */
	vec2s *vt;			/* texture coordinates	u, v	  */
	vec3s *vn;			/* vertex normal		x, y, z   */

	size_t f_len;
	size_t v_len;
	size_t vt_len;
	size_t vn_len;

	// number of bytes being stored by each array
	size_t f_nbytes;
	size_t v_nbytes;
	size_t vt_nbytes;
	size_t vn_nbytes;

	// size (in bytes) of each float value
	size_t val_size;

	// number of values in a single element
	size_t f_nval;
	size_t v_nval;
	size_t vt_nval;
	size_t vn_nval;

	// distance between each v, vt, or vn in the faces array
	size_t stride;

	// offset of first elements
	size_t v_offset;
	size_t vt_offset;
	size_t vn_offset;

	// extent info
	float dia;
	vec3s center;
	vec3s max;
	vec3s min;
};

int  obj3d_load( struct obj3d *obj, const char *file );
void obj3d_free( struct obj3d *obj );

int  obj3d_square( struct obj3d *obj );
int  obj3d_sphere( struct obj3d *obj );

#endif
