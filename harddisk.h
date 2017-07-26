#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#define DIM 2
#include "mymath.h"

typedef struct {real x,y;} d_complex;
//typedef enum   PTLTYPE { ACTIVE, FLUID } PTLTYPE;
typedef int PTLid;
typedef struct {
	real mass;
	real radius;
	PTLid id;
//	PTLTYPE type;
} PTL_info; 
typedef struct {
	VecR r,v,f; 
	VecR spin,w,tor;
	VecR r0;
	VecR noise;
	PTL_info* pInfo;
//	int   ibin;
} Particle;
PTL_info* pInfo;
enum { XH=0, XL, YH, YL };

typedef const char * c_str;
enum enumType { P2P, P2W} ;
	
typedef struct EVENT {
	enum enumType TYPE;
	int id1;
	union { 
		int id2;
		int wall_type;
	};
	real time;
} event;



// simulation macro, function and value
#define maxN 1000
#define maxEVENT 1000
#define PRESTEPS   100

//simulation Spatial information
// functions
int  get_drawable ();
void set_drawable ();  
void initialization ();
void init_position ();
void init_for_calculating_table ();
void init_type ();
void init_velocity_Boltzmann ();

void print_information ();
void run ();
void update_next_event ();
void update ();
void update_free (real);
// collision
void collision_wall_slip (int sid, VecR);
void collision_wall_noslip (int sid, VecR);
void collision_wall_elastic(int ,  VecR);
void collision_sphere_elastic(int , int, VecR);
void occur_collision ();

void insert_event_table (event * event);
void build_collision_timetable () ;
void rebuild_collision_timetable (int ) ;

void do_sort ();
void print_sorted_eventlist ();
void print_eventlist ();
event* get_1st_event ();
Particle* get_safecopy ();
