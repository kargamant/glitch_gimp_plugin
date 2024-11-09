#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void get_random_rgn(GimpDrawable* dr, GimpPixelRgn* rgin, GimpPixelRgn* rgout)
{
	gint x1, y1, x2, y2;
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	
	int lx=x1+rand()%x2;
	int ly=y1+rand()%y2;
	int rx=lx+rand()%(x2-lx);
	int ry=ly+rand()%(y2-ly);

	//printf("image bounds: %d, %d, %d, %d\n", x1, y1, x2, y2);
	//printf("coordinates: %d, %d, %d, %d\n", lx, ly, rx, ry);
	
	gimp_pixel_rgn_init(rgin, dr, lx, ly, rx-lx, ry-ly, FALSE, FALSE);
	gimp_pixel_rgn_init(rgout, dr, lx, ly, rx-lx, ry-ly, TRUE, FALSE);
}

void inverse_pixels(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels)
{
	guchar* buff=g_new(guchar, rgin->h*rgin->w*channels);
	gimp_pixel_rgn_get_rect(rgin, buff, rgin->x, rgin->y, rgin->w, rgin->h);

	for(guchar* ptr=buff; (ptr-buff)<rgin->h*rgin->w*channels; ++ptr)
	{
		*ptr=255-*ptr;
	}	
	gimp_pixel_rgn_set_rect(rgout, buff, rgout->x, rgout->y, rgout->w, rgout->h);

	g_free(buff);
}

void color_corrupt(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels)
{
	int cmyk_corrupt_type=rand()%channels;
	guchar* buff=g_new(guchar, rgin->h*rgin->w*channels);
	gimp_pixel_rgn_get_rect(rgin, buff, rgin->x, rgin->y, rgin->w, rgin->h);
	
	for(int i=0; i<rgin->h*rgin->w; i++)
	{
		buff[i*channels+cmyk_corrupt_type]=0;
	}	
	gimp_pixel_rgn_set_rect(rgout, buff, rgout->x, rgout->y, rgout->w, rgout->h);

	g_free(buff);
}

void shift_pixels(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels, int shift)
{
	if(rgin->w<=shift)
		return;

	guchar* buff=g_new(guchar, rgin->h*rgin->w*channels);
	gimp_pixel_rgn_get_rect(rgin, buff, rgin->x, rgin->y, rgin->w, rgin->h);

	guchar* pixel_queue=g_new(guchar, channels);
	for(int s=0; s<shift; s++)
	{
		for(int i=0; i<rgin->h; i++)
		{
			for(int k=0; k<channels; k++)
			{
				pixel_queue[k]=buff[i*rgin->w*channels+k];
			}
		
			for(int j=0; j<rgin->w-1; j++)
			{
				for(int k=0; k<channels; k++)
				{
					buff[(i*rgin->w+j)*channels+k] = buff[(i*rgin->w+j+1)*channels+k];
				}
			}

			for(int k=0; k<channels; k++)
			{
				buff[(i*rgin->w+rgin->w-1)*channels+k]=pixel_queue[k];
			}
		}
	}
	gimp_pixel_rgn_set_rect(rgout, buff, rgout->x, rgout->y, rgout->w, rgout->h);

	g_free(buff);
}

void glitch(GimpDrawable* dr, int rand_regions, int shift)
{
	srand(time(NULL));
	gint x1, y1, x2, y2;
	int channels = gimp_drawable_bpp(dr->drawable_id);
	printf("channels of image: %d\n", channels);

	printf("Receiving picture bounds\n");
	gimp_drawable_mask_bounds(dr->drawable_id, &x1, &y1, &x2, &y2);
	
	for(int i=0; i<rand_regions; i++)
	{
		GimpPixelRgn rgin, rgout;
		get_random_rgn(dr, &rgin, &rgout);
		inverse_pixels(&rgin, &rgout, channels);
	}

	for(int j=0; j<rand_regions; j++)
	{
		GimpPixelRgn rgin, rgout;
		get_random_rgn(dr, &rgin, &rgout);
		color_corrupt(&rgin, &rgout, channels);
	}

	for(int k=0; k<rand_regions; k++)
	{
		GimpPixelRgn rgin, rgout;
		get_random_rgn(dr, &rgin, &rgout);
		shift_pixels(&rgin, &rgout, channels, shift);
	}
	
	printf("Processing finished\n");

	gimp_drawable_flush(dr);

	gimp_drawable_update(dr->drawable_id, x1, y1, x2-x1, y2-y1);
}

void output_buff(guchar* buff, int n)
{
	for(guchar* ptr=buff; (ptr-buff)<n; ++ptr)
	{
		printf("%d ", *ptr);
	}
	printf("\n");
}









