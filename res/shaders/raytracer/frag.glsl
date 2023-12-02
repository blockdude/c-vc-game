#version 330 core

#define M_PI 3.1415926538
#define EPSILON 1e-4f
#define RENDER_DISTANCE 100000000.0f

const uint MAX_OBJECT_COUNT = 5u;
const uint MAX_LIGHT_COUNT  = 1u;
const uint MAX_PLANE_COUNT  = 1u;

const uint OBJECT_TYPE_NONE = 0u;
const uint OBJECT_TYPE_SPHERE = 1u;
const uint OBJECT_TYPE_TRIANGLE = 2u;
const uint OBJECT_TYPE_PLANE = 2u;

out vec4 out_color;

struct material_t
{
	vec3 color;
	float reflectiveness;
};

struct object_t
{
	uint type;
	vec3 pos;
	vec3 norm;
	float scale;
	material_t mat;
};

/* point lighting */
struct light_t
{
	vec3 pos;
	float radius;
	vec3 color;
	float reach;
	float power;
};

struct plane_t
{
	vec3 pos;
	vec3 norm;
};

struct ray_t
{
	vec3 orig;
	vec3 dir;
};

struct sphere_t
{
	vec3 center;
	float radius;
};

struct triangle_t
{
	vec3 pos_a, pos_b, pos_c;		/* vertex position */
	vec3 norm_a, norm_b, norm_c;	/* vertex normal   */
};

struct camera_t
{
	vec3 eye;
	vec3 target;
	vec3 up;
	mat4 view;
	float fov;
};

struct hitdata_t
{
	bool hit;
	float dist;
	vec3 hit_point;
	vec3 normal;
	material_t mat;
};

/* ======================================================== */
/* --------------------------- */
/* UNIFORM DATA				   */
/* --------------------------- */

uniform camera_t camera;
uniform vec2 resolution;

uniform object_t objects[ MAX_OBJECT_COUNT ];
uniform light_t lights[ MAX_LIGHT_COUNT ];
uniform plane_t plane;

/* ======================================================== */

/* ======================================================== */
/* --------------------------- */
/* COLLISION / INTERSECTION    */
/* --------------------------- */

hitdata_t hit_ray_tri( ray_t ray, triangle_t tri )
{
	vec3 edge_ab = tri.pos_b - tri.pos_a;
	vec3 edge_ac = tri.pos_c - tri.pos_a;
	vec3 normal_vector = cross( edge_ab, edge_ac );

	vec3 ao = ray.orig - tri.pos_a;
	vec3 dao = cross( ao, ray.dir );

	float det = -dot( ray.dir, normal_vector );
	float inv_det = 1 / det;

	// Calculate dist to triangle & barycentric coordinates of intersection point
	float dist = dot( ao, normal_vector ) * inv_det;
	float u = dot( edge_ac, dao ) * inv_det;
	float v = -dot( edge_ab, dao ) * inv_det;
	float w = 1 - u - v;

	// Initialize hit info
	hitdata_t hitdata;
	hitdata.hit       = det >= EPSILON && dist >= 0 && u >= 0 && v >= 0 && w >= 0;
	hitdata.hit_point = ray.orig + ray.dir * dist;
	hitdata.normal    = normalize( tri.norm_a * w + tri.norm_b * u + tri.norm_c * v );
	hitdata.dist      = dist;
	return hitdata;
}

hitdata_t hit_ray_sphere( ray_t r, sphere_t s )
{
	hitdata_t hitdata;
	hitdata.hit = false;

	/* offset from center */
	vec3 oc = r.orig - s.center;

	/* Solving for dist results in a quadratic equation with coefficients */
	float a = dot( r.dir, r.dir );
	float b = 2.0 * dot( oc, r.dir );
	float c = dot( oc, oc ) - s.radius * s.radius;
	float discriminant = b * b - 4 * a * c;

	/* sphere does not intersect */
	if ( discriminant < 0 )
		return hitdata;

	float dist = ( -b - sqrt( discriminant ) ) / ( 2 * a );

	/* intersection is behind */
	if ( dist < 0 )
		return hitdata;

	/* ray intersects with sphere */
	hitdata.hit = true;
	hitdata.dist = dist;
	hitdata.hit_point = r.orig + r.dir * dist;
	hitdata.normal = normalize( hitdata.hit_point - s.center );

	return hitdata;
}

hitdata_t hit_ray_plane( ray_t ray, plane_t plane ) 
{ 
	hitdata_t hitdata;
	hitdata.hit = false;

	float denom = dot( plane.norm, ray.dir ); 

	if ( abs( denom ) <= EPSILON )
		return hitdata;

	float dist = dot( plane.pos - ray.orig, plane.norm ) / denom;

	hitdata.hit = dist >= EPSILON;
	hitdata.dist = dist;
	hitdata.hit_point = ray.orig + ray.dir * dist;
	hitdata.normal = plane.norm;

	/* preassigned values for plane (should change to uniform) */
	hitdata.mat.color = vec3( 0.5f, 0.5f, 0.5f );
	hitdata.mat.reflectiveness = 0.0f;

	return hitdata; 
} 

hitdata_t hit_ray_object( ray_t ray, object_t obj )
{
	hitdata_t hitdata;
	hitdata.hit = false;
	hitdata.mat.color = vec3( 0.0f, 0.0f, 0.0f );

	if ( obj.type == OBJECT_TYPE_NONE )
	{
		return hitdata;
	}
	if ( obj.type == OBJECT_TYPE_SPHERE )
	{
		sphere_t sphere = sphere_t( obj.pos, obj.scale );
		hitdata = hit_ray_sphere( ray, sphere );
		hitdata.mat = obj.mat;
	}

	return hitdata;
}

/* ======================================================== */

/* ======================================================== */
/* --------------------------- */
/* RAY CAST					   */
/* --------------------------- */

ray_t camera_raycast( vec2 pixel )
{
	ray_t self;
	self.orig = camera.eye;

	vec3 cameraU = vec3( camera.view[ 0 ][ 0 ], camera.view[ 1 ][ 0 ], camera.view[ 2 ][ 0 ] );
	vec3 cameraV = vec3( camera.view[ 0 ][ 1 ], camera.view[ 1 ][ 1 ], camera.view[ 2 ][ 1 ] );
	vec3 cameraW = vec3( camera.view[ 0 ][ 2 ], camera.view[ 1 ][ 2 ], camera.view[ 2 ][ 2 ] );

	float height = 2.0f * tan( camera.fov / 2.0f );
	float aspect = resolution.x / resolution.y;
	float width = height * aspect;

	vec2 window_dim = vec2( width, height );
	vec2 pixel_size = window_dim / resolution;

	vec2 delta = -0.5 * window_dim + pixel * pixel_size;
	self.dir = -cameraW + cameraV * delta.y + cameraU * delta.x;
	self.dir = normalize( self.dir );

	return self;
}

hitdata_t raycast( ray_t ray )
{
	hitdata_t hitdata;
	hitdata.hit = false;
	hitdata.mat.color = vec3( 0.0f, 0.0f, 0.0f );
	float min_dist = RENDER_DISTANCE;

	/* object collision */
	for ( int i = 0; i < objects.length(); i++ )
	{
		object_t obj = objects[ i ];
		if ( obj.type == OBJECT_TYPE_NONE )
			continue;

		hitdata_t tmp = hit_ray_object( ray, obj );
		if ( tmp.hit == true && tmp.dist < min_dist )
		{
			hitdata = tmp;
			min_dist = tmp.dist;
		}
	}

	/* plane collision */
	hitdata_t tmp = hit_ray_plane( ray, plane );
	if ( tmp.hit == true && tmp.dist < min_dist )
	{
		hitdata = tmp;
		min_dist = tmp.dist;
	}

	return hitdata;
}

/* ======================================================== */

/* ======================================================== */
/* --------------------------- */
/* COMPUTE LIGHT			   */
/* --------------------------- */

vec3 raycast_to_light( hitdata_t hitdata )
{
	vec3 color = vec3( 0.0f );

	if ( hitdata.hit == false )
		return color;

	/* get color from light source */
	for ( int i = 0; i < lights.length(); i++ )
	{
		light_t light = lights[ i ];

		/* ray to light */
		ray_t rtl;
		rtl.dir = normalize( light.pos - hitdata.hit_point );
		rtl.orig = hitdata.hit_point;

		/* cast ray to light source */
		hitdata_t rtl_hitdata = raycast( rtl );

		/* no color if ray to light source is blocked */
		if ( rtl_hitdata.hit == true )
			continue;

		float light_dist = distance( light.pos, hitdata.hit_point );

		if ( light_dist > light.reach )
			continue;

		float diffuse = clamp( dot( hitdata.normal, normalize( light.pos - hitdata.hit_point ) ), 0.0, 1.0 );
		color = light.color * light.power * diffuse * hitdata.mat.color * dot( hitdata.normal, rtl.dir );
	}

	return color;
}

vec3 compute_color( ray_t ray )
{
	vec3 color = vec3( 0.0f );

	/* cast initial ray */
	hitdata_t hitdata;
	hitdata = raycast( ray );

	if ( hitdata.hit == false )
		return color;

	/* reflected ray (single bounce) */
	ray_t rr;
	rr.dir = reflect( ray.dir, hitdata.normal );
	rr.orig = hitdata.hit_point;
	hitdata_t refldata = raycast( rr );

	vec3 orig_color = raycast_to_light( hitdata ) * ( 1.0f - hitdata.mat.reflectiveness );
	vec3 refl_color = raycast_to_light( refldata ) * ( hitdata.mat.reflectiveness );

	color = orig_color + refl_color;

	return color;
}

/* ======================================================== */

/* ======================================================== */
/* --------------------------- */
/* MAIN ENTRY				   */
/* --------------------------- */

void main()
{
	ray_t ray = camera_raycast( gl_FragCoord.xy );
	out_color = vec4( compute_color( ray ), 1.0f );
}

/* ======================================================== */
