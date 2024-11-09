#include "utils.h"
#include <stdio.h>

void inverse_pixels(GimpDrawable* dr)
{
	gint x1, y1, x2, y2;
	GimpPixelRgn rgin, rgout;
	int channels = gimp_drawable_bpp(dr->drawable_id);
	printf("channels of image: %d\n", channels);

	//getting bounds of an image
	printf("Receiving picture bounds\n");
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	
	//initializing regions
	printf("initializing regions\n");
	gimp_pixel_rgn_init(&rgin, dr, x1, y1, x2-x1, y2-y1, FALSE, FALSE);
	gimp_pixel_rgn_init(&rgout, dr, x1, y1, x2-x1, y2-y1, TRUE, TRUE);
	
	// test modification
	int width=1000;
	guchar* buff=g_new(guchar, (x2-x1)*channels);
	printf("Prepared buffer\n");
	for(int i=0; i<width; i++)
	{
		gimp_pixel_rgn_get_row(&rgin, buff, 0, i, x2-x1);
		for(int k=0; k<width; k++)
		{
			for(int j=0; j<channels; j++)
			{
				buff[k*channels+j]=150;
			}
		}
		gimp_pixel_rgn_set_row(&rgout, buff, 0, i, x2-x1);
	}
	guchar* addition = g_new(guchar, (x2-x1)*channels);
	for(int h=width; h<y2-y1; h++)
	{
		gimp_pixel_rgn_get_row(&rgin, addition, 0, h, x2-x1);
		gimp_pixel_rgn_set_row(&rgout, addition, 0, h, x2-x1);
	}
	printf("Processing finished\n");
	
	g_free(addition);
	g_free(buff);

	gimp_drawable_flush(dr);
	printf("data flushed\n");

	gimp_drawable_merge_shadow(dr->drawable_id, TRUE);

	gimp_drawable_update(dr->drawable_id, x1, y1, x2-x1, y2-y1);
	printf("drawable updated\n");
	
}

void output_buff(guchar* buff, int n)
{
	for(guchar* ptr=buff; (ptr-buff)<n; ++ptr)
	{
		printf("%d ", *ptr);
	}
	printf("\n");
}









