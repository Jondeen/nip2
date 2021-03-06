/* a toolkitgroupview button in a toolkitgroup
 */

/*

    Copyright (C) 1991-2003 The National Gallery

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

 */

/*

    These files are distributed with VIPS - http://www.vips.ecs.soton.ac.uk

*/

/* 
#define DEBUG
 */

#include "ip.h"

static ViewClass *parent_class = NULL;

static void *
toolkitgroupview_dispose_sub( View *view, void *a, void *b )
{
	DESTROY_GTK( view );

	return( NULL );
}

static void
toolkitgroupview_dispose( GObject *gobject )
{
#ifdef DEBUG
	printf( "toolkitgroupview_dispose: %p\n", gobject );
#endif /*DEBUG*/

	/* Toolkitviews are not child widgets of us, they are menu items pased
	 * into the TK. Destroy them explicitly.
	 */
	view_map( VIEW( gobject ), 
		toolkitgroupview_dispose_sub, NULL, NULL ); 

	G_OBJECT_CLASS( parent_class )->dispose( gobject );
}

static void 
toolkitgroupview_refresh( vObject *vobject )
{
	/* 
	Toolkitgroupview *kitgview = TOOLKITGROUPVIEW( view );
	 */

	/* FIXME ... should update display for reordering of toolkits (to keep
	 * menu sorted)
	 */

#ifdef DEBUG
	printf( "toolkitgroup changed\n" );
#endif /*DEBUG*/

	VOBJECT_CLASS( parent_class )->refresh( vobject );
}

static void
toolkitgroupview_class_init( ToolkitgroupviewClass *class )
{
	GObjectClass *gobject_class = (GObjectClass *) class;
	vObjectClass *vobject_class = (vObjectClass *) class;

	parent_class = g_type_class_peek_parent( class );

	gobject_class->dispose = toolkitgroupview_dispose;

	/* Create signals.
	 */

	/* Set methods.
	 */
	vobject_class->refresh = toolkitgroupview_refresh;
}

static void
toolkitgroupview_init( Toolkitgroupview *kitgview )
{
}

GtkType
toolkitgroupview_get_type( void )
{
	static GtkType toolkitgroupview_type = 0;

	if( !toolkitgroupview_type ) {
		static const GtkTypeInfo info = {
			"Toolkitgroupview",
			sizeof( Toolkitgroupview ),
			sizeof( ToolkitgroupviewClass ),
			(GtkClassInitFunc) toolkitgroupview_class_init,
			(GtkObjectInitFunc) toolkitgroupview_init,
			/* reserved_1 */ NULL,
			/* reserved_2 */ NULL,
			(GtkClassInitFunc) NULL,
		};

		toolkitgroupview_type = gtk_type_unique( TYPE_VIEW, &info );
	}

	return( toolkitgroupview_type );
}

View *
toolkitgroupview_new( void )
{
	Toolkitgroupview *kitgview = gtk_type_new( TYPE_TOOLKITGROUPVIEW );

	return( VIEW( kitgview ) );
}

void
toolkitgroupview_set_mainw( Toolkitgroupview *kitgview, Mainw *mainw )
{
	kitgview->mainw = mainw;
        kitgview->menu = mainw->toolkit_menu;
}
