#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include "widget.h"

gboolean glitch_dialogue(GlitchParams* params)
{
	GtkWidget *dialog;
	GtkWidget *main_vbox;
	GtkWidget *main_hbox;
	GtkWidget *frame;
	GtkWidget *regions_label;
	GtkWidget *shift_label;
	GtkWidget *alignment;
	GtkWidget *spinbutton_regions;
	GtkObject *spinbutton_adj_regions;
	GtkWidget *spinbutton_shift;
	GtkObject *spinbutton_adj_shift;
	GtkWidget *frame_label;
	gboolean   run;

	gimp_ui_init ("glitch", FALSE);

	dialog = gimp_dialog_new ("Glitch", "glitch",
							NULL, 0,
							gimp_standard_help_func, "plug-in-glitch",
							GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							GTK_STOCK_OK, GTK_RESPONSE_OK,
							NULL);
	main_vbox = gtk_vbox_new (FALSE, 6);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG (dialog)->vbox), main_vbox);
	gtk_widget_show (main_vbox);

	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (main_vbox), frame, TRUE, TRUE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 6);

	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_widget_show (alignment);
	gtk_container_add (GTK_CONTAINER (frame), alignment);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 6, 6, 6, 6);

	main_hbox = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (main_hbox);
	gtk_container_add (GTK_CONTAINER (alignment), main_hbox);

	regions_label = gtk_label_new_with_mnemonic ("_Regions:");
	gtk_widget_show (regions_label);
	gtk_box_pack_start (GTK_BOX (main_hbox), regions_label, FALSE, FALSE, 6);
	gtk_label_set_justify (GTK_LABEL (regions_label), GTK_JUSTIFY_RIGHT);

	spinbutton_adj_regions = gtk_adjustment_new (3, 1, 1000, 1, 5, 5);
	spinbutton_regions = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_adj_regions), 1, 0);
	gtk_widget_show (spinbutton_regions);
	gtk_box_pack_start (GTK_BOX (main_hbox), spinbutton_regions, FALSE, FALSE, 6);
	gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton_regions), TRUE);

	g_signal_connect (spinbutton_adj_regions, "value_changed",
								  G_CALLBACK (gimp_int_adjustment_update),
												  &params->rand_regions);
	shift_label = gtk_label_new_with_mnemonic ("_Shift:");
	gtk_widget_show (shift_label);
	gtk_box_pack_start (GTK_BOX (main_hbox), shift_label, FALSE, FALSE, 6);
	gtk_label_set_justify (GTK_LABEL (shift_label), GTK_JUSTIFY_RIGHT);

	spinbutton_adj_shift = gtk_adjustment_new (3, 1, 1000, 1, 5, 5);
	spinbutton_shift = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_adj_shift), 1, 0);
	gtk_widget_show (spinbutton_shift);
	gtk_box_pack_start (GTK_BOX (main_hbox), spinbutton_shift, FALSE, FALSE, 6);
	gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton_shift), TRUE);

	g_signal_connect (spinbutton_adj_shift, "value_changed",
								  G_CALLBACK (gimp_int_adjustment_update),
												  &params->shift);
	gtk_widget_show (dialog);

	run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);
	
	printf("params: %d, %d\n", params->rand_regions, params->shift);

	gtk_widget_destroy (dialog);

	return run;
}
