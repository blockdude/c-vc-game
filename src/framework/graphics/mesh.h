#ifndef MESH_H
#define MESH_H

#include "shader.h"
#include "vao.h"
#include "vbo.h"

#include <util/types.h>

enum mesh_status
{
	MESH_SUCCESS = 0,
	MESH_ERROR   = 1
};

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


	/*
	 * This will be the new mesh structure in the future
	 */
	const char *name;

	float *vertices; /* vertex positions    (XYZ)  */
	float *textmap;  /* texture coordinates (UV)   */
	float *normals;  /* vertex normals      (XYZ)  */
	float *tangents; /* vertex tangents     (XYZW) */
	float *colors;   /* Vertex colors       (RGBA) */
	int   *indices;  /* Vertex indices             */

	// extent info
	float  dia;
	vec3_t center;
	vec3_t max;
	vec3_t min;

	struct vao vao;
	struct vbo *vbo;
};

struct model
{
	mat4_t transform;
	struct mesh *meshes;
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * WaveFront object file loader.
 */

int  mesh_load( struct mesh *obj, const char *file );
void mesh_free( struct mesh *obj );

int mesh_upload( struct mesh *obj, struct shader shader );

int mesh_cube( struct mesh *obj );
int mesh_square( struct mesh *obj );
int mesh_sphere( struct mesh *obj );

#ifdef __cplusplus
}
#endif

#endif
