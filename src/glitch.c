#include "utils.h"
#include <stdio.h>
#include "widget.h"

GlitchParams params = {3, 25};

static void
run (const gchar *name, gint nparams, const GimpParam  *param, gint *nreturn_vals, GimpParam **return_vals)
{
	static GimpParam  values[1];
	*nreturn_vals = 1;
	*return_vals  = values;
	values[0].type = GIMP_PDB_STATUS;
	values[0].data.d_status = GIMP_PDB_SUCCESS;

	if(!glitch_dialogue(&params))
		return;
	printf("params: %d, %d\n", params.rand_regions, params.shift);

	GimpDrawable* drawable = gimp_drawable_get(param[2].data.d_drawable);
	glitch(drawable, params.rand_regions, params.shift);

	gimp_displays_flush();
	gimp_drawable_detach(drawable);
}

GimpPlugInInfo PLUG_IN_INFO = {
	NULL,
	NULL,
	query,
	run
};

MAIN();
