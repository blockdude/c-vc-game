#ifndef OBJ3D_H
#define OBJ3D_H

/*
 * WaveFront object file loader.
 */

#include <stddef.h>

struct vec3
{
	float x;
	float y;
	float z;
};

struct vec2
{
	float x;
	float y;
};

struct vert
{
	struct vec3 v;
	struct vec2 vt;
	struct vec3 vn;
};

struct obj3d
{
	// dynarrs
	struct vert *f;		/* vertices (v, vt, and vn)       */
	struct vec3 *v;		/* vertex positions		x, y, z   */
	struct vec2 *vt;	/* texture coordinates	u, v	  */
	struct vec3 *vn;	/* vertex normal		x, y, z   */

	size_t f_len;
	size_t v_len;
	size_t vt_len;
	size_t vn_len;

	// number of bytes being stored by each array
	size_t f_nbytes;
	size_t v_nbytes;
	size_t vt_nbytes;
	size_t vn_nbytes;

	// size of each element
	size_t elem_size;

	// number of values in a single element
	size_t f_elem_len;
	size_t v_elem_len;
	size_t vt_elem_len;
	size_t vn_elem_len;

	// distance between each v, vt, or vn in the faces array
	size_t stride;

	// offset of first elements
	size_t v_offset;
	size_t vt_offset;
	size_t vn_offset;

	// address of first elements in faces
	void *v_offset_data;
	void *vt_offset_data;
	void *vn_offset_data;

	// raw data
	void *data;

	// extent info
	float dia;
	struct vec3 center;
	struct vec3 max;
	struct vec3 min;
};

int  obj3d_load( struct obj3d *obj, const char *file );
int  obj3d_square( struct obj3d *obj );
int  obj3d_sphere( struct obj3d *obj );
void obj3d_free( struct obj3d *obj );

#endif
