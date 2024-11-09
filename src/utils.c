#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void get_random_rgn(GimpDrawable* dr, GimpPixelRgn* rgin, GimpPixelRgn* rgout)
{
	gint x1, y1, x2, y2;
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	
	srand(time(NULL));
	int lx=x1+rand()%x2;
	int ly=y1+rand()%y2;
	int rx=lx+rand()%(x2-lx);
	int ry=ly+rand()%(y2-ly);

	printf("image bounds: %d, %d, %d, %d\n", x1, y1, x2, y2);
	printf("coordinates: %d, %d, %d, %d\n", lx, ly, rx, ry);
	
	gimp_pixel_rgn_init(rgin, dr, lx, ly, rx-lx, ry-ly, FALSE, FALSE);
	gimp_pixel_rgn_init(rgout, dr, lx, ly, rx-lx, ry-ly, TRUE, FALSE);
}

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
	get_random_rgn(dr, &rgin, &rgout);
	
	int width=rgin.w;
	int height=rgin.h;
	guchar* buff=g_new(guchar, width*channels);
	printf("Prepared buffer\n");
	
	// test modification
	for(int i=0; i<height; i++)
	{
		gimp_pixel_rgn_get_row(&rgin, buff, rgin.x, rgin.y+i, width);
		for(int k=0; k<width; k++)
		{
			for(int j=0; j<channels; j++)
			{
				buff[k*channels+j]=150;
			}
		}
		gimp_pixel_rgn_set_row(&rgout, buff, rgin.x, rgin.y+i, width);
	}
	printf("Processing finished\n");
	
	g_free(buff);

	gimp_drawable_flush(dr);
	printf("data flushed\n");

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









