#include "utils.h"
#include <stdio.h>

void inverse_pixels(GimpDrawable* dr)
{
	gint x1, y1, x2, y2;
	GimpPixelRgn rgin, rgout;
	int channels = gimp_drawable_bpp(dr->drawable_id);
	printf("channels: %d\n", channels);

	//getting bounds of an image
	printf("Receiving picture bounds\n");
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	
	//initializing regions
	printf("initializing regions\n");
	gimp_pixel_rgn_init(&rgin, dr, x1, y1, x2-x1, y2-y1, 0, 0);
	gimp_pixel_rgn_init(&rgout, dr, x1, y1, x2-x1, y2-y1, 1, 1);
	
	// test modification
	int width=5;
	guchar* buff=g_new(guchar, width*channels);
	printf("Prepared buffer\n");
	for(int i=0; i<width; i++)
	{
		gimp_pixel_rgn_get_row(&rgin, buff, 0, i, width);
		output_buff(buff);
		printf("Parsed row %d\n", i);
		for(int k=0; k<width; k++)
		{
			for(int j=0; j<channels; j++)
			{
				printf("nulling %d channel of %d pixel\n", j, k);
				buff[k*channels+j]=0;
			}
		}
		gimp_pixel_rgn_set_row(&rgout, buff, 0, i, width);
		printf("Row %d was processed\n", i);
	}
	printf("Processing finished\n");

	gimp_drawable_flush(dr);
	printf("data flushed\n");

	gimp_drawable_merge_shadow(dr->drawable_id, 1);

	gimp_drawable_update(dr->drawable_id, x1, y1, x2-x1, y2-y1);
	printf("drawable updated\n");
	
	g_free(buff);
}

void output_buff(guchar* buff)
{
	for(guchar* ptr=buff; (ptr-buff)<sizeof(buff)/sizeof(guchar); ++ptr)
	{
		printf("%d ", *ptr);
	}
	printf("\n");
}









