#ifndef MESH_H
#define MESH_H

#include <util/types.h>
#include "shader.h"
#include "vao.h"
#include "vbo.h"

struct mesh
{
	float *vp;	/* vertex positions				x,  y,  z	*/
	float *vt;	/* vertex texture coordinates	u,  v		*/
	float *vn;	/* vertex normal				x,  y,  z	*/
	float *fv;  /* face vertices                v, vt, vn	*/

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
	float  dia;
	vec3_t center;
	vec3_t max;
	vec3_t min;

	// raylib uses seperate vbo for each vertex type and I don't
	// know why. Ill stick to one for now but may change my mind.
	struct vao vao;
	struct vbo vbo;
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * WaveFront object file loader.
 */

int  mesh_load( struct mesh *obj, const char *file );
void mesh_free( struct mesh *obj );

int  mesh_upload( struct mesh *obj, struct shader shader );

int  mesh_cube( struct mesh *obj );
int  mesh_square( struct mesh *obj );
int  mesh_sphere( struct mesh *obj );

#ifdef __cplusplus
}
#endif

#endif
