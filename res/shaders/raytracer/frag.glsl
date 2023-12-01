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
	float dist;
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

hitdata_t intersects_ray_tri( ray_t ray, triangle_t tri )
{
	vec3 edgeAB = tri.pos_b - tri.pos_a;
	vec3 edgeAC = tri.pos_c - tri.pos_a;
	vec3 normalVector = cross( edgeAB, edgeAC );

	vec3 ao = ray.orig - tri.pos_a;
	vec3 dao = cross( ao, ray.dir );

	float det = -dot( ray.dir, normalVector );
	float invDet = 1 / det;

	// Calculate dist to triangle & barycentric coordinates of intersection point
	float dist = dot( ao, normalVector ) * invDet;
	float u = dot( edgeAC, dao ) * invDet;
	float v = -dot( edgeAB, dao ) * invDet;
	float w = 1 - u - v;

	// Initialize hit info
	hitdata_t hitInfo;
	hitInfo.did_hit   = det >= 1E-6f && dist >= 0 && u >= 0 && v >= 0 && w >= 0;
	hitInfo.hit_point = ray.orig + ray.dir * dist;
	hitInfo.normal    = normalize( tri.norm_a * w + tri.norm_b * u + tri.norm_c * v );
	hitInfo.dist       = dist;
	return hitInfo;
}

hitdata_t intersects_ray_sphere( vec3 sphereCentre, float sphereRadius, ray_t ray )
{
	hitdata_t hitInfo;
	vec3 offsetRayOrigin = ray.orig - sphereCentre;
	// From the equation: sqrLength(rayOrigin + rayDir * dist) = radius^2
	// Solving for dist results in a quadratic equation with coefficients:
	float a = dot(ray.dir, ray.dir); // a = 1 (assuming unit vector)
	float b = 2 * dot(offsetRayOrigin, ray.dir);
	float c = dot(offsetRayOrigin, offsetRayOrigin) - sphereRadius * sphereRadius;
	// Quadratic discriminant
	float discriminant = b * b - 4 * a * c; 

	// No solution when d < 0 (ray misses sphere)
	if (discriminant >= 0) {
		// Distance to nearest intersection point (from quadratic formula)
		float dist = (-b - sqrt(discriminant)) / (2 * a);

		// Ignore intersections that occur behind the ray
		if (dist >= 0) {
			hitInfo.did_hit = true;
			hitInfo.dist = dist;
			hitInfo.hit_point = ray.orig + ray.dir * dist;
			hitInfo.normal = normalize(hitInfo.hit_point - sphereCentre);
		}
	}
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

	//r.orig = camera.eye;
	//r.dir = camera.target;
	//r.orig = vec3( 0 );
	//r.dir = vec3( 0.0f, 0.0f, 1.0f );

	ray_t r = ray_create( gl_FragCoord.xy );
	//hitdata_t hit = intersects_ray_sphere( vec3( 0.0f, 0.0f, 0.0f ), 1.0f, r );
	bool hit = hit_sphere( vec3( 0.0f, 0.0f, 0.0f ), 1.0f, r );
	out_color = vec4( 0.0f, 0.0f, float( hit ), 1.0f );
	//out_color = vec4( camera.target, 1.0f );

	//ray_t r = ray_create( gl_FragCoord.xy );
	//float a = 0.5f * ( r.dir.y + 1.0f );
	//vec3 color = ( 1.0f - a ) * vec3( 1.0f, 1.0f, 1.0f ) + a * vec3( 0.5f, 0.7f, 1.0f );
	//out_color = vec4( color, 0.0f );
}
