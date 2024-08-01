#ifndef OBJ3D_H
#define OBJ3D_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * WaveFront object file loader.
 */

#include <cglm/cglm.h>
#include <cglm/struct.h>
#include <stddef.h>

struct vert
{
	vec3s vp;
	vec2s vt;
	vec3s vn;
};

struct obj3d
{
	// dynarrs
	struct vert *fv;	/* face vertices (v, vt, and vn)		*/
	vec3s *vp;			/* vertex positions				x, y, z	*/
	vec2s *vt;			/* vertex texture coordinates	u, v	*/
	vec3s *vn;			/* vertex normal				x, y, z	*/

	size_t fv_len;
	size_t vp_len;
	size_t vt_len;
	size_t vn_len;

	// number of bytes being stored by each array
	size_t fv_nbytes;
	size_t vp_nbytes;
	size_t vt_nbytes;
	size_t vn_nbytes;

	// size (in bytes) of each float value
	size_t val_size;

	// number of values in a single element
	size_t fv_nval;
	size_t vp_nval;
	size_t vt_nval;
	size_t vn_nval;

	// distance between each v, vt, or vn in the faces array
	size_t stride;

	// offset of first elements
	size_t vp_offset;
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

#ifdef __cplusplus
}
#endif

#endif
