#include "obj3d.h"

#include <util/log.h>
#include <util/types.h>
#include <data/dynarr.h>

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

static int obj3d_load_mesh_( struct obj3d *obj, const char *file )
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

			sscanf( buffer, "%*s %d%d%d %d%d%d %d%d%d",
					&a, &b, &c,
					&d, &e, &f,
					&g, &h, &i
			);

			fa.v  = obj->v [ a ];
			fa.vt = obj->vt[ b ];
			fa.vn = obj->vn[ c ];

			fb.v  = obj->v [ e ];
			fb.vt = obj->vt[ f ];
			fb.vn = obj->vn[ g ];

			fc.v  = obj->v [ g ];
			fc.vt = obj->vt[ h ];
			fc.vn = obj->vn[ i ];

			dynarr_push_back( obj->f, fa );
			dynarr_push_back( obj->f, fb );
			dynarr_push_back( obj->f, fc );
		}
	}

	fclose( fp );

	return 0;
}

static void obj3d_compute_extent_( struct obj3d *obj )
{

}

static void obj3d_compute_properties_( struct obj3d *obj )
{
	obj->f_len			= dynarr_size( obj->f );
	obj->v_len			= dynarr_size( obj->v );
	obj->vt_len			= dynarr_size( obj->vt );
	obj->vn_len			= dynarr_size( obj->vn );

	obj->f_nbytes		= dynarr_size( obj->f ) * sizeof( *obj->f );
	obj->v_nbytes		= dynarr_size( obj->v ) * sizeof( *obj->v );
	obj->vt_nbytes		= dynarr_size( obj->vt ) * sizeof( *obj->vt );
	obj->vn_nbytes		= dynarr_size( obj->vn ) * sizeof( *obj->vn );

	obj->elem_size		= sizeof( float );

	obj->v_elem_len	   	= 3; /* x y z */
	obj->vt_elem_len   	= 2; /* u v   */
	obj->vn_elem_len   	= 3; /* r g b */

	obj->stride		   	= ( obj->v_elem_len + obj->vt_elem_len + obj->vn_elem_len ) * obj->elem_size;

	obj->v_offset		= 0;
	obj->vt_offset		= obj->v_elem_len * obj->elem_size;
	obj->vn_offset		= ( obj->v_elem_len + obj->vt_elem_len ) * obj->elem_size;

	obj->v_offset_data	= &obj->f[ 0 ].v;
	obj->vt_offset_data = &obj->f[ 0 ].vt;
	obj->vn_offset_data = &obj->f[ 0 ].vn;

	obj->data			= obj->f;
}

int obj3d_load( struct obj3d *obj, const char *file )
{
	if ( obj == NULL || file == NULL )
	{
		return -1;
	}

	obj3d_init_( obj );

	if ( obj3d_load_mesh_( obj, file ) != 0 )
	{
		return -1;
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
