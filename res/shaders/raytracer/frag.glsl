#version 330 core

#define M_PI 3.1415926538

out vec4 out_color;

struct ray_t
{
	vec3 orig;
	vec3 dir;
};

struct sphere_t
{
	vec3 pos;
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
	bool did_hit;
	float dst;
	vec3 hit_point;
	vec3 normal;
};

uniform camera_t camera;
uniform vec2 resolution;

ray_t ray_create( vec2 pixel )
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

hitdata_t intersect_ray_tri( ray_t ray, triangle_t tri )
{
	vec3 edgeAB = tri.pos_b - tri.pos_a;
	vec3 edgeAC = tri.pos_c - tri.pos_a;
	vec3 normalVector = cross( edgeAB, edgeAC );

	vec3 ao = ray.orig - tri.pos_a;
	vec3 dao = cross( ao, ray.dir );

	float det = -dot( ray.dir, normalVector );
	float invDet = 1 / det;

	// Calculate dst to triangle & barycentric coordinates of intersection point
	float dst = dot( ao, normalVector ) * invDet;
	float u = dot( edgeAC, dao ) * invDet;
	float v = -dot( edgeAB, dao ) * invDet;
	float w = 1 - u - v;

	// Initialize hit info
	hitdata_t hitInfo;
	hitInfo.did_hit   = det >= 1E-6f && dst >= 0 && u >= 0 && v >= 0 && w >= 0;
	hitInfo.hit_point = ray.orig + ray.dir * dst;
	hitInfo.normal    = normalize( tri.norm_a * w + tri.norm_b * u + tri.norm_c * v );
	hitInfo.dst       = dst;
	return hitInfo;
}

bool hit_sphere( vec3 center, float radius, ray_t r )
{
	vec3 oc = r.orig - center;

	float a = dot( r.dir, r.dir );
	float b = 2.0 * dot( oc, r.dir );
	float c = dot( oc, oc ) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return ( discriminant >= 0 );
}

//ray ray_create( vec2 pixel )
//{
//	ray self;
//	self.orig = camera.eye;
//
//	float aspect = resolution.x / resolution.y;
//
//	float Px = ( 2 * (( pixel.x + 0.5 ) / resolution.x ) - 1 ) * tan( camera.fov / 2 * M_PI / 180 ) * aspect;
//	float Py = ( 1 - 2 * (( pixel.y + 0.5 ) / resolution.y )) * tan( camera.fov / 2 * M_PI / 180 );
//
//	self.dir = vec3( Px, Py, -1 ) - self.orig;
//	self.dir = normalize( self.dir );
//	return self;
//}


void main()
{
	//triangle_t tri;
	//tri.pos_a  = vec3( -1.0f, -1.0f,  0.0f );
	//tri.pos_b  = vec3(  1.0f, -1.0f,  0.0f );
	//tri.pos_c  = vec3(  1.0f,  1.0f,  0.0f );

	//tri.norm_a = vec3(  0.0f,  0.0f,  1.0f );
	//tri.norm_b = vec3(  0.0f,  0.0f,  1.0f );
	//tri.norm_c = vec3(  0.0f,  0.0f,  1.0f );

	//hitdata_t hit = intersect_ray_tri( r, tri );

	//if ( hit.did_hit )
	//{
	//	out_color = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	//}
	//else
	//{
	//	out_color = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
	//}

	ray_t r = ray_create( gl_FragCoord.xy );
	out_color = vec4( r.dir, 0.0f );

	//float a = 0.5f * ( r.dir.y + 1.0f );
	//vec3 color = ( 1.0f - a ) * vec3( 1.0f, 1.0f, 1.0f ) + a * vec3( 0.5f, 0.7f, 1.0f );
	//out_color = vec4( color, 1.0f );
}
