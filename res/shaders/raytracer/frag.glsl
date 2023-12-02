#version 330 core

#define M_PI 3.1415926538
#define EPSILON 1e-6f

const uint MAX_OBJECT_COUNT = 16u;
const uint MAX_LIGHT_COUNT = 4u;

const uint OBJECT_TYPE_NONE = 0u;
const uint OBJECT_TYPE_SPHERE = 1u;
const uint OBJECT_TYPE_CUBE = 2u;

out vec4 out_color;

struct object_t
{
	uint type;
	vec3 pos;
	int scale;
	vec3 color;
	float roughness;
};

/* point lighting */
struct light_t
{
	vec3 pos;
	float radius;
	vec3 color;
	float reach;
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
};

uniform camera_t camera;
uniform vec2 resolution;

uniform object_t objects[ MAX_OBJECT_COUNT ];
uniform light_t lights[ MAX_LIGHT_COUNT ];

ray_t camera_ray( vec2 pixel )
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

	return hitdata; 
} 

void main()
{
	ray_t ray = camera_ray( gl_FragCoord.xy );

	sphere_t sphere = sphere_t( vec3( 0.0f, 0.0f, 0.0f ), 1.0f );
	plane_t plane = plane_t( vec3( 0.0f, -1.0f, 0.0f ), vec3( 0.0f, 1.0f, 0.0f ) );
	hitdata_t hd;

	out_color = vec4( 0.0f, 0.0f, 0.0f, 1.0f );

	hd = hit_ray_plane( ray, plane );
	if ( hd.hit )
		out_color = vec4( 0.5f, 0.5f, 0.5f, 1.0f );

	if ( hd.hit_point.y < camera.eye.y )
	{
		hd = hit_ray_sphere( ray, sphere );
		if ( hd.hit )
			out_color = vec4( 0.0f, 0.0f, 1.0f, 1.0f );
	}
}
