/*!
 *    \file  main.c
 *   \brief  
 *
 *  <+DETAILED+>
 *
 *  \author  KIM Hyeok (kh), ekh0324@gmail.com
 *
 *  \internal
 *       Created:  2017년 07월 25일
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:  Konkuk University
 *     Copyright:  Copyright (c) 2017, KIM Hyeok
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 */
#include <cairo.h>
#include <gtk/gtk.h>
#include <glib-object.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#define MAIN
#include "harddisk.h"
extern VecR region;
extern real current_time, EndTime;
extern int N;

static cairo_surface_t *surface = NULL;

static gboolean
time_handler (GtkWidget *user_data)
{
	static int a =0; 
	if(a==0) {
		initialization ();
		a=1;
	}
		update();
}
static void
clear_surface (void)
{
	cairo_t *cr;

	cr = cairo_create (surface);

	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);

	cairo_destroy (cr);
}
struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;
	static gboolean
configure_event_cb (GtkWidget         *widget,
		GdkEventConfigure *event,
		gpointer           data)
{
	GtkAllocation allocation;
	if (surface)
		cairo_surface_destroy (surface);

	gtk_widget_get_allocation (widget, &allocation);

	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
			CAIRO_CONTENT_COLOR,
			allocation.width,
			allocation.height);

	/* Initialize the surface to white */
	clear_surface ();

	/* We've handled the configure event, no need for further processing. */
	return TRUE;
}

static void do_drawing(cairo_t *,GtkWidget * );
gpointer harddisk_object;
guint    harddisk_change_event;

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
		gpointer user_data)
{
	do_drawing(cr,widget);

	return FALSE;
}

void do_drawing(cairo_t *cr, GtkWidget *widget)
{ 
	GtkWidget *win = gtk_widget_get_toplevel(widget);
	  
	int width, height;
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  int length = width<height?width:height;
	int i, j, id, ptype;
	char str[8];

/* 	for (i = 0; i <= glob.count - 1; i++ ) {
 * 		for (j = 0; j <= glob.count - 1; j++ ) {
 * 			cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
 * 			cairo_line_to(cr, glob.coordx[j], glob.coordy[j]);
 * 		}
 * 	}
 * 	glob.count=0;
 * 	cairo_stroke(cr);    
 */


	real x,y,r;
	cairo_text_extents_t te;
	event* pe;
	c_str TYPE;

/* 	cairo_arc(cr,glob.coordx[i], glob.coordy[i],30,0., 2.*M_PI);
 * 	cairo_fill(cr);
 */


	cairo_move_to(cr, 0, 0);
	cairo_line_to(cr, length, 0);
	
	cairo_move_to(cr, length, 0);
	cairo_line_to(cr, length, length);

	cairo_move_to(cr, length, length);
	cairo_line_to(cr, 0, length);

	cairo_move_to(cr, 0 , length);
	cairo_line_to(cr, 0 ,0 );

	cairo_stroke(cr);

	pe = get_1st_event ();
	int  type = pe->TYPE;
	Particle* copy = get_safecopy ();

	if (get_drawable ()) {
//		printf("init %d => N = %d \n", get_drawable(), N);
		for (i=0; i<N; i++) {
			x= copy[i].r.x;
			y= copy[i].r.y;
			r= copy[i].pInfo->radius;
			ptype= copy[i].pInfo->id;

			x = (x+.5*region.x)*length/region.x;
			y = (y+.5*region.y)*length/region.y;
			r= copy[i].pInfo->radius*length/region.x;

			if (ptype ==0) {
				cairo_set_source_rgb(cr, 1, 0., 0.);
			}
			else {
				cairo_set_source_rgb(cr,0,0,1);
			}
			if ( type == P2P) {
				if (i == pe->id1) {
					cairo_set_source_rgb(cr,0,1,0);
				} 
				if ( pe->id2== i) {
					cairo_set_source_rgb(cr,0,1,0);
				}
			} else {
				if (i == pe->id1) {
					cairo_set_source_rgb(cr,0,1,1);
				} 
			}
			
			cairo_set_line_width(cr, 1);
			cairo_arc(cr,x,y,r,0., 2.*M_PI);
			cairo_fill(cr);
			//		sleep(1);
			cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 

			cairo_select_font_face(cr, "Purisa",
					CAIRO_FONT_SLANT_NORMAL,
					CAIRO_FONT_WEIGHT_BOLD);

			cairo_move_to(cr, x,y);
			sprintf(str,"%d",i);
			cairo_show_text(cr, str);  

			
		}
	}

}

GtkWidget *window;
GtkWidget *darea;
gpointer run_gui (gpointer);
int main(int argc, char *argv[])
{
	gpointer dummy;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	  glob.count = 0;

	darea = gtk_drawing_area_new();
	gtk_widget_set_size_request (darea, 1000, 700);

	gtk_container_add(GTK_CONTAINER(window), darea);
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);


	g_signal_connect(G_OBJECT(darea), "draw", 
			G_CALLBACK(on_draw_event), NULL);  
	g_signal_connect(window, "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
//	 g_signal_connect(window, "button-press-event", 
//			       G_CALLBACK(clicked), NULL);


  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 700, 700); 
  gtk_window_set_title(GTK_WINDOW(window), "Lines");

  gtk_widget_show_all(window);

	g_signal_connect (darea,"configure-event",
                      G_CALLBACK (configure_event_cb), NULL);
//	g_timeout_add(50, (GSourceFunc)time_handler, (gpointer) darea ); 
	g_thread_new("backgroud application",	run_gui, dummy) ;
  gtk_window_set_title(GTK_WINDOW(window), "Hello Hard sphere");

		gtk_main();
	
	return 0;
}
gpointer run_gui (gpointer data)
{
	
	initialization ();
//	harddisk_object = g_object_new (G_TYPE_OBJECT, NULL);

	while(1) {
//		update_next_event ();

		update();
		usleep(1000*1001/10);
		
		gtk_widget_queue_draw(darea);

		if( current_time > EndTime )
			break;
	}
}
