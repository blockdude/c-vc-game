#include "obj3d.h"

#include <util/log.h>
#include <util/types.h>
#include <util/fmath.h>
#include <data/dynarr.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline void obj3d_init_( struct obj3d *obj )
{
	obj->f  = NULL;
	obj->v  = NULL;
	obj->vt = NULL;
	obj->vn = NULL;
}

static inline int obj3d_load_mesh_( struct obj3d *obj, const char *file )
{
	const size_t buffer_size = 1024;
	char buffer[ buffer_size ];
	FILE *fp = fopen( file, "r" );
	
	if ( fp == NULL )
	{
		return -1;
	}

	while( !feof( fp ) )
	{
		// get line and store in buffer
		if ( !fgets( buffer, buffer_size, fp ) )
		{
			break;
		}

		if ( strlen( buffer ) - 1 <= 0 )
		{
			continue;
		}

		char lexeme[ 64 ];
		sscanf( buffer, "%s", lexeme );

		// get a vertex position
		if ( strcmp( lexeme, "v" ) == 0 )
		{
			struct vec3 tmp;
			sscanf( buffer, "%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z );
			dynarr_push_back( obj->v, tmp );
		}
		// get a texture coordinates
		else if ( strcmp( lexeme, "vt" ) == 0 )
		{
			struct vec2 tmp;
			sscanf( buffer, "%*s %f %f", &tmp.x, &tmp.y );
			dynarr_push_back( obj->vt, tmp );
		}
		// get a vertex normal
		else if ( strcmp( lexeme, "vn" ) == 0 )
		{
			struct vec3 tmp;
			sscanf( buffer, "%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z );
			dynarr_push_back( obj->vn, tmp );
		}
		// get an object face
		else if ( strcmp( lexeme, "f" ) == 0 )
		{
			struct vert fa, fb, fc;
			int a, b, c, d, e, f, g, h, i;

			sscanf( buffer, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
					&a, &b, &c,
					&d, &e, &f,
					&g, &h, &i
			);

			fa.v  = obj->v [ a - 1 ];
			fa.vt = obj->vt[ b - 1 ];
			fa.vn = obj->vn[ c - 1 ];

			fb.v  = obj->v [ d - 1 ];
			fb.vt = obj->vt[ e - 1 ];
			fb.vn = obj->vn[ f - 1 ];

			fc.v  = obj->v [ g - 1 ];
			fc.vt = obj->vt[ h - 1 ];
			fc.vn = obj->vn[ i - 1 ];

			dynarr_push_back( obj->f, fa );
			dynarr_push_back( obj->f, fb );
			dynarr_push_back( obj->f, fc );
		}
	}

	fclose( fp );

	return 0;
}

static inline struct vec3 obj3d_vec3_min_( struct vec3 va, struct vec3 vb )
{
	struct vec3 res;
	res.x = f32min( va.x, vb.x );
	res.y = f32min( va.y, vb.y );
	res.z = f32min( va.z, vb.z );
	return res;
}

static inline struct vec3 obj3d_vec3_max_( struct vec3 va, struct vec3 vb )
{
	struct vec3 res;
	res.x = f32max( va.x, vb.x );
	res.y = f32max( va.y, vb.y );
	res.z = f32max( va.z, vb.z );
	return res;
}

static inline void obj3d_set_min_max_( struct obj3d *obj )
{
	size_t len = dynarr_size( obj->v );
	struct vec3 min = len > 0 ? obj->v[ 0 ] : ( struct vec3 ){ 0 };
	struct vec3 max = len > 0 ? obj->v[ 0 ] : ( struct vec3 ){ 0 };

	for ( size_t i = 0; i < len; i++ )
	{
		min = obj3d_vec3_min_( min, obj->v[ i ] );
		max = obj3d_vec3_max_( max, obj->v[ i ] );
	}

	obj->min = min;
	obj->max = max;
}

static inline float obj3d_vec3_distance_( struct vec3 va, struct vec3 vb )
{
	struct vec3 tmp;

	tmp.x = vb.x - va.x;
	tmp.y = vb.y - va.y;
	tmp.z = vb.z - va.z;

	tmp.x = tmp.x * tmp.x;
	tmp.y = tmp.y * tmp.y;
	tmp.z = tmp.z * tmp.z;

	float res = sqrt( tmp.x + tmp.y + tmp.z );
	return res;
}

static inline struct vec3 obj3d_vec3_center_( struct vec3 va, struct vec3 vb )
{
	struct vec3 res;

	res.x = va.x + vb.x;
	res.y = va.y + vb.y;
	res.z = va.z + vb.z;

	res.x /= 2;
	res.y /= 2;
	res.z /= 2;

	return res;
}

static inline void obj3d_compute_extent_( struct obj3d *obj )
{
	obj3d_set_min_max_( obj );
	obj->dia = obj3d_vec3_distance_( obj->min, obj->max );
	obj->center = obj3d_vec3_center_( obj->min, obj->max );
}

static inline void obj3d_compute_properties_( struct obj3d *obj )
{
	obj->f_len			= dynarr_size( obj->f );
	obj->v_len			= dynarr_size( obj->v );
	obj->vt_len			= dynarr_size( obj->vt );
	obj->vn_len			= dynarr_size( obj->vn );

	obj->f_nbytes		= dynarr_size( obj->f ) * sizeof( *obj->f );
	obj->v_nbytes		= dynarr_size( obj->v ) * sizeof( *obj->v );
	obj->vt_nbytes		= dynarr_size( obj->vt ) * sizeof( *obj->vt );
	obj->vn_nbytes		= dynarr_size( obj->vn ) * sizeof( *obj->vn );

	obj->val_size		= sizeof( float );

	obj->f_nval			= 8; /* v vt vn */
	obj->v_nval	   		= 3; /* x y z   */
	obj->vt_nval   		= 2; /* u v     */
	obj->vn_nval   		= 3; /* x y z   */

	obj->stride		   	= ( obj->v_nval + obj->vt_nval + obj->vn_nval ) * obj->val_size;

	obj->v_offset		= ( 0 );
	obj->vt_offset		= ( obj->v_nval * obj->val_size );
	obj->vn_offset		= ( ( obj->v_nval + obj->vt_nval ) * obj->val_size );

	obj->v_offset_ptr	= ( void * )obj->v_offset;
	obj->vt_offset_ptr	= ( void * )obj->vt_offset;
	obj->vn_offset_ptr	= ( void * )obj->vn_offset;

	obj->data			= obj->f;
}

int obj3d_load( struct obj3d *obj, const char *file )
{
	if ( obj == NULL || file == NULL )
	{
		return -1;
	}

	obj3d_init_( obj );

	int res = obj3d_load_mesh_( obj, file );
	if ( res != 0 )
	{
		return res - 1;
	}

	obj3d_compute_extent_( obj );
	obj3d_compute_properties_( obj );

	return 0;
}

void obj3d_free( struct obj3d *obj )
{
	dynarr_free( obj->f );
	dynarr_free( obj->v );
	dynarr_free( obj->vt );
	dynarr_free( obj->vn );
}
