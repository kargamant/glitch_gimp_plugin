#include <libgimp/gimp.h>

static void
query (void)
{
	static GimpParamDef args[] = {
	{
	       GIMP_PDB_INT32,
	       "run-mode",
	       "Run mode"						    
	},
	{
		GIMP_PDB_IMAGE,
		"image",
		"Input image"
	},
	{
		GIMP_PDB_DRAWABLE,
		"drawable",
		"Input drawable"
	}
	};
	gimp_install_procedure (
	"plug-in-glitch",
	"Glitch",
	"Applies glitch effect to image",
    	"Egor Deriglazov",
        "Copyright Egor Deriglazov",
	"2024",
	"glitch",
	"RGB*, GRAY*",
	GIMP_PLUGIN,
	G_N_ELEMENTS (args), 0,
	args, NULL);

	gimp_plugin_menu_register ("plug-in-glitch", "<Image>/Filters/Misc"); 
}
static void
run (const gchar *name, gint nparams, const GimpParam  *param, gint *nreturn_vals, GimpParam **return_vals)
{
	static GimpParam  values[1];
	*nreturn_vals = 1;
	*return_vals  = values;
	values[0].type = GIMP_PDB_STATUS;
	values[0].data.d_status = GIMP_PDB_SUCCESS;

	g_message("Test output!\n");
}

GimpPlugInInfo PLUG_IN_INFO = {
	NULL,
	NULL,
	query,
	run
};

MAIN();