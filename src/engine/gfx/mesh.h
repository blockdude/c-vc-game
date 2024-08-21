struct vert
{
	vec3s vp;
	vec2s vt;
	vec3s vn;
};

struct mesh
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
