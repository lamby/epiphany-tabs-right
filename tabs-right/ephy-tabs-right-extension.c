/*
 *  Copyright © 2009 Chris Lamb <chris@chris-lamb.co.uk>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  $Id$
 */

#include "config.h"

#include "ephy-tabs-right-extension.h"
#include "ephy-debug.h"

#include <epiphany/epiphany.h>

#include <gmodule.h>
#include <gtk/gtk.h>

static GObjectClass *parent_class = NULL;

static GType type = 0;

static void
impl_attach_window (EphyExtension *ext,
		    EphyWindow *window)
{
	GtkWidget *notebook;

	notebook = ephy_window_get_notebook (window);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_RIGHT);
}

static void
impl_detach_window (EphyExtension *ext,
		    EphyWindow *window)
{
	GtkWidget *notebook;

	notebook = ephy_window_get_notebook (window);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
}

static void
ephy_tabs_right_extension_iface_init (EphyExtensionIface *iface)
{
	iface->attach_window = impl_attach_window;
	iface->detach_window = impl_detach_window;
}

GType
ephy_tabs_right_extension_get_type (void)
{
	return type;
}

GType
ephy_tabs_right_extension_register_type (GTypeModule *module)
{
	const GTypeInfo our_info =
	{
		sizeof (EphyTabsRightExtensionClass),
		NULL, /* base_init */
		NULL, /* base_finalize */
		NULL, /* class_init */
		NULL,
		NULL, /* class_data */
		sizeof (EphyTabsRightExtension),
		0, /* n_preallocs */
		NULL /* instance_init */
	};

	const GInterfaceInfo extension_info =
	{
		(GInterfaceInitFunc) ephy_tabs_right_extension_iface_init,
		NULL,
		NULL
	};

	type = g_type_module_register_type (module,
					    G_TYPE_OBJECT,
					    "EphyTabsRightExtension",
					    &our_info, 0);

	g_type_module_add_interface (module,
				     type,
				     EPHY_TYPE_EXTENSION,
				     &extension_info);

	return type;
}
