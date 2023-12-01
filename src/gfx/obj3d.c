#include "obj3d.h"
#include "cglm/struct/vec3.h"

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
	obj->fv = NULL;
	obj->vp = NULL;
	obj->vt = NULL;
	obj->vn = NULL;
}

static inline void obj3d_append_face_vertex_( struct obj3d *obj, const char *vert )
{
	struct vert f;
	int a, b, c;

	sscanf( vert, "%d/%d/%d", &a, &b, &c );

	f.vp = obj->vp[ a - 1 ];
	f.vt = obj->vt[ b - 1 ];
	f.vn = obj->vn[ c - 1 ];

	dynarr_push_back( obj->fv, f );
}

static inline int obj3d_load_mesh_( struct obj3d *obj, const char *file )
{
	const size_t buffer_size = 1024;
	char buffer[ buffer_size ];
	FILE *fp = fopen( file, "r" );
	
	if ( fp == NULL )
	{
		return 1;
	}

	while( !feof( fp ) )
	{
		// get line and store in buffer (should make proper parser but this is fine for now)
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
			vec3s tmp;
			sscanf( buffer, "%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z );
			dynarr_push_back( obj->vp, tmp );
		}
		// get a texture coordinates
		else if ( strcmp( lexeme, "vt" ) == 0 )
		{
			vec2s tmp;
			sscanf( buffer, "%*s %f %f", &tmp.x, &tmp.y );
			dynarr_push_back( obj->vt, tmp );
		}
		// get a vertex normal
		else if ( strcmp( lexeme, "vn" ) == 0 )
		{
			vec3s tmp;
			sscanf( buffer, "%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z );
			dynarr_push_back( obj->vn, tmp );
		}
		// get a face
		else if ( strcmp( lexeme, "f" ) == 0 )
		{
			// store and track start address of each face vertex
			int vert_count = 0;
			char *vert_idx[ 64 ];

			// count number of vertices
			for ( char *itr = buffer; *itr != '\n' && *itr != '\0'; itr++ )
			{
				if ( *itr == ' ' )
				{
					vert_idx[ vert_count ] = itr + 1;
					vert_count++;
				}
			}

			// parse vertex
			for ( int i = 0; i <= vert_count - 3; i++ )
			{
				obj3d_append_face_vertex_( obj, vert_idx[ 0 ] );
				obj3d_append_face_vertex_( obj, vert_idx[ 1 + i ] );
				obj3d_append_face_vertex_( obj, vert_idx[ 2 + i ] );
			}
		}
	}

	fclose( fp );

	return 0;
}

static inline void obj3d_set_min_max_( struct obj3d *obj )
{
	size_t len = dynarr_size( obj->vp );
	vec3s min = len > 0 ? obj->vp[ 0 ] : ( vec3s ){ 0 };
	vec3s max = len > 0 ? obj->vp[ 0 ] : ( vec3s ){ 0 };

	for ( size_t i = 0; i < len; i++ )
	{
		min = glms_vec3_minv( min, obj->vp[ i ] );
		max = glms_vec3_maxv( max, obj->vp[ i ] );
	}

	obj->min = min;
	obj->max = max;
}

static inline void obj3d_compute_extent_( struct obj3d *obj )
{
	obj3d_set_min_max_( obj );
	obj->dia = glms_vec3_distance( obj->min, obj->max );
	obj->center = glms_vec3_center( obj->min, obj->max );
}

static inline void obj3d_compute_properties_( struct obj3d *obj )
{
	obj->fv_len			= dynarr_size( obj->fv );
	obj->vp_len			= dynarr_size( obj->vp );
	obj->vt_len			= dynarr_size( obj->vt );
	obj->vn_len			= dynarr_size( obj->vn );

	obj->fv_nbytes		= dynarr_size( obj->fv ) * sizeof( *obj->fv );
	obj->vp_nbytes		= dynarr_size( obj->vp ) * sizeof( *obj->vp );
	obj->vt_nbytes		= dynarr_size( obj->vt ) * sizeof( *obj->vt );
	obj->vn_nbytes		= dynarr_size( obj->vn ) * sizeof( *obj->vn );

	obj->val_size		= sizeof( float );

	obj->fv_nval		= 8; /* v vt vn */
	obj->vp_nval	   	= 3; /* x y z   */
	obj->vt_nval   		= 2; /* u v     */
	obj->vn_nval   		= 3; /* x y z   */

	obj->stride		   	= ( obj->vp_nval + obj->vt_nval + obj->vn_nval ) * obj->val_size;

	obj->vp_offset		= ( 0 );
	obj->vt_offset		= ( obj->vp_nval * obj->val_size );
	obj->vn_offset		= ( ( obj->vp_nval + obj->vt_nval ) * obj->val_size );
}

int obj3d_load( struct obj3d *obj, const char *file )
{
	if ( obj == NULL || file == NULL )
		return 1;

	obj3d_init_( obj );
	if ( obj3d_load_mesh_( obj, file ) != 0 )
	{
		obj3d_free( obj );
		return 2;
	}

	obj3d_compute_extent_( obj );
	obj3d_compute_properties_( obj );

	if ( obj->fv_len == 0 )
	{
		obj3d_free( obj );
		return 3;
	}

	return 0;
}

void obj3d_free( struct obj3d *obj )
{
	dynarr_free( obj->fv );
	dynarr_free( obj->vp );
	dynarr_free( obj->vt );
	dynarr_free( obj->vn );
}
