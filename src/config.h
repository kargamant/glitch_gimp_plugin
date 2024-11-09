#pragma once
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

	gimp_plugin_menu_register ("plug-in-glitch", "<Image>/Filters/MyFilters"); 
}

typedef struct
{
	int rand_regions, shift;
}GlitchParams;

