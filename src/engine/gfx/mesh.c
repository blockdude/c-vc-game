#include "obj3d.h"
#include "cglm/struct/vec3.h"

#include <util/log.h>
#include <util/types.h>
#include <util/math.h>
#include <util/list.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static inline void mesh_init( struct mesh *obj )
{
	obj->vp = NULL;
	obj->vt = NULL;
	obj->vn = NULL;
	obj->fv = NULL;
}

static inline void mesh_append_face_vertex( struct mesh *obj, const char *vert )
{
	int a, b, c;
	sscanf( vert, "%d/%d/%d", &a, &b, &c );

	a = ( a - 1 ) * 3;
	b = ( b - 1 ) * 2;
	c = ( c - 1 ) * 3;

	list_push_back( obj->fv, obj->vp[ a + 0 ] );
	list_push_back( obj->fv, obj->vp[ a + 1 ] );
	list_push_back( obj->fv, obj->vp[ a + 2 ] );

	list_push_back( obj->fv, obj->vt[ b + 0 ] );
	list_push_back( obj->fv, obj->vt[ b + 1 ] );

	list_push_back( obj->fv, obj->vn[ c + 0 ] );
	list_push_back( obj->fv, obj->vn[ c + 1 ] );
	list_push_back( obj->fv, obj->vn[ c + 2 ] );
}

static inline int mesh_load_mesh( struct mesh *obj, const char *file )
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
			float x, y, z;
			sscanf( buffer, "%*s %f %f %f", &x, &y, &z );
			list_push_back( obj->vp, x );
			list_push_back( obj->vp, y );
			list_push_back( obj->vp, z );
		}
		// get a texture coordinates
		else if ( strcmp( lexeme, "vt" ) == 0 )
		{
			float u, v;
			sscanf( buffer, "%*s %f %f", &u, &v );
			list_push_back( obj->vt, u );
			list_push_back( obj->vt, v );
		}
		// get a vertex normal
		else if ( strcmp( lexeme, "vn" ) == 0 )
		{
			float x, y, z;
			sscanf( buffer, "%*s %f %f %f", &x, &y, &z );
			list_push_back( obj->vn, x );
			list_push_back( obj->vn, y );
			list_push_back( obj->vn, z );
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
				mesh_append_face_vertex( obj, vert_idx[ 0 ] );
				mesh_append_face_vertex( obj, vert_idx[ 1 + i ] );
				mesh_append_face_vertex( obj, vert_idx[ 2 + i ] );
			}
		}
	}

	fclose( fp );

	return 0;
}

static inline void mesh_set_min_max( struct mesh *obj )
{
	size_t len = list_size( obj->vp );

	if ( len <= 0 )
	{
		obj->min = vec3_zero();
		obj->max = vec3_zero();
		return;
	}

	vec3_t min = { obj->vp[ 0 ], obj->vp[ 1 ], obj->vp[ 2 ] };
	vec3_t max = { obj->vp[ 0 ], obj->vp[ 1 ], obj->vp[ 2 ] };

	for ( size_t i = 0; i < len; i += 3 )
	{
		vec3_t v = {
			obj->vp[ i + 0 ],
			obj->vp[ i + 1 ],
			obj->vp[ i + 2 ]
		};

		min = vec3_min( min, v );
		max = vec3_max( max, v );
	}

	obj->min = min;
	obj->max = max;
}

static inline void mesh_compute_extent( struct mesh *obj )
{
	mesh_set_min_max( obj );
	obj->dia = vec3_dist( obj->min, obj->max );
	obj->center = vec3_center( obj->min, obj->max );
}

static inline void mesh_compute_properties( struct mesh *obj )
{
	obj->fv_len			= list_size( obj->fv );
	obj->vp_len			= list_size( obj->vp );
	obj->vt_len			= list_size( obj->vt );
	obj->vn_len			= list_size( obj->vn );

	obj->fv_nbytes		= list_size( obj->fv ) * sizeof( *obj->fv );
	obj->vp_nbytes		= list_size( obj->vp ) * sizeof( *obj->vp );
	obj->vt_nbytes		= list_size( obj->vt ) * sizeof( *obj->vt );
	obj->vn_nbytes		= list_size( obj->vn ) * sizeof( *obj->vn );

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

int mesh_load( struct mesh *obj, const char *file )
{
	if ( obj == NULL || file == NULL )
		return 1;

	mesh_init( obj );
	if ( mesh_load_mesh( obj, file ) != 0 )
	{
		mesh_free( obj );
		return 2;
	}

	mesh_compute_extent( obj );
	mesh_compute_properties( obj );

	if ( obj->fv_len == 0 )
	{
		mesh_free( obj );
		return 3;
	}

	return 0;
}

void mesh_free( struct mesh *obj )
{
	list_free( obj->vp );
	list_free( obj->vt );
	list_free( obj->vn );
	list_free( obj->fv );
}
