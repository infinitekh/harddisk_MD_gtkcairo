#ifndef _MYMATH_H_
#define _MYMATH_H_
// macro from manual
#include <limits.h>
#include <float.h>
typedef double real;
static real real_max = DBL_MAX;

#if DIM  != 2
#define DIM 3
typedef struct {int x,y,z;} VecI;
typedef struct {real x,y,z;} VecR;
typedef struct {real xx,xy,xz,yx,yy,yz,zx,zy,zz;} MatR;
#define VSq(a) 	( (a).x*(a).x +(a).y*(a).y+ (a).z*(a).z )
#define VSqrt(a) 	sqrt( (a).x*(a).x +(a).y*(a).y+ (a).z*(a).z )
#define VSubAdd(v1, v2, v3, v4)		\
	(v1).x = (v2).x - (v3).x+ (v4).x,		\
	(v1).y = (v2).y - (v3).y + (v4).y,		\
	(v1).z = (v2).z - (v3).z + (v4).z
#define VVAdd(v1, v2)	VAdd(v1,v1,v2)	
#define VAdd(v1, v2, v3)		\
	(v1).x = (v2).x + (v3).x,		\
	(v1).y = (v2).y + (v3).y,		\
	(v1).z = (v2).z + (v3).z
#define VScale(v, s) \
	(v).x *= s, (v).y *=s, (v).z *= s
#define VSAdd(v1, v2, s3, v3) \
	(v1).x = (v2).x + (s3) * (v3).x, \
	(v1).y = (v2).y + (s3) * (v3).y, \
	(v1).z = (v2).z + (s3) * (v3).z 
#define VSet(v, sx, sy, sz) \
		(v).x = sx,  (v).y = sy, (v).z = sz
#define VSetAll(v, s) VSet (v, s, s, s)
#define VZero(v) VSetAll (v, 0) 
#define VVSAdd(v1, s2, v2) VSAdd (v1, v1, s2, v2)
#define VVSub(v1, v2) VSub (v1, v1, v2)
#define VSub(v1, v2, v3)		\
	(v1).x = (v2).x - (v3).x,		\
	(v1).y = (v2).y - (v3).y,		\
	(v1).z = (v2).z - (v3).z
real never_used___;
#define VGetTan(v1, v2, v3) \
	never_used___ = VDot(v1,v2);  \
	(v1).x = (v2).x -never_used___ * (v3).x, \
	(v1).y = (v2).y -never_used___ * (v3).y,  \
	(v1).z = (v2).z -never_used___ * (v3).z 
#define VSSub(v1, v2, s3, v3) \
	(v1).x = (v2).x - (s3) * (v3).x, \
	(v1).y = (v2).y - (s3) * (v3).y,  \
	(v1).z = (v2).z - (s3) * (v3).z 
#define VWrap(v, t)		\
	if (v.t >= 0.5 * region.t)      v.t -= region.t;		\
	else if (v.t < -0.5 * region.t) v.t += region.t
#define VWrapAll(v)		\
		{VWrap (v, x);		\
		VWrap (v, y);		\
		VWrap (v, z);}
#define VDot(v1, v2)		\
	((v1).x * (v2).x + (v1).y * (v2).y + (v1).z * (v2).z)
#define VVMAdd(v1, v2, v3)		\
	(v1).x += (v2).x * (v3).x,		\
	(v1).y += (v2).y * (v3).y,		\
	(v1).z += (v2).z * (v3).z  
#define VMul(v1, v2, v3)		\
	(v1).x = (v2).x * (v3).x,		\
	(v1).y = (v2).y * (v3).y,		\
	(v1).z = (v2).z * (v3).z  
#define Sqr(x)     ((x) * (x))
#define Cube(x)    ((x) * (x) * (x))
#define VProd(v)		\
	((v).x * (v).y * (v).z)
#define VCopy(v2, v1)		\
	(v2).x =  (v1).x,		\
(v2).y =  (v1).y,		\
(v2).z =  (v1).z
#define VSCopy(v2, s1, v1)		\
	(v2).x = (s1) * (v1).x,		\
(v2).y = (s1) * (v1).y,		\
(v2).z = (s1) * (v1).z
#define VCross(v3,v1,v2)		\
	v3.x= v1.y*v2.z - v1.z*v2.y,		\
  v3.y= v1.z*v2.x - v1.x*v2.z,		\
  v3.z= v1.x*v2.y - v1.y*v2.x
real unused_uniform___;
#define VUniform(v)              \
			unused_uniform___ =  1./sqrt(VDot(v,v)) ,\
			VScale(v,unused_uniform___);
#define VDisjoin(v)	  (v).x , (v).y , (v).z



#else


typedef struct {int x,y;} VecI;
typedef struct {real x,y;} VecR;
typedef struct {real xx,xy,yx,yy;} MatR;
#define VSq(a) 	( (a).x*(a).x +(a).y*(a).y )
#define VSqrt(a) 	sqrt( (a).x*(a).x +(a).y*(a).y )
#define VSubAdd(v1, v2, v3, v4)		\
	(v1).x = (v2).x - (v3).x+ (v4).x,		\
	(v1).y = (v2).y - (v3).y + (v4).y
#define VVAdd(v1, v2)	VAdd(v1,v1,v2)	
#define VAdd(v1, v2, v3)		\
	(v1).x = (v2).x + (v3).x,		\
	(v1).y = (v2).y + (v3).y
#define VScale(v, s) \
	(v).x *= s, (v).y *=s
#define VSAdd(v1, v2, s3, v3) \
	(v1).x = (v2).x + (s3) * (v3).x, \
	(v1).y = (v2).y + (s3) * (v3).y 
#define VSet(v, sx, sy) \
		(v).x = sx,  (v).y = sy
#define VSetAll(v, s) VSet (v, s, s)
#define VZero(v) VSetAll (v, 0) 
#define VVSAdd(v1, s2, v2) VSAdd (v1, v1, s2, v2)
#define VVSub(v1, v2) VSub (v1, v1, v2)
#define VSub(v1, v2, v3)		\
	(v1).x = (v2).x - (v3).x,		\
	(v1).y = (v2).y - (v3).y
real never_used___;
#define VGetTan(v1, v2, v3) \
	never_used___ = VDot(v1,v2);  \
	(v1).x = (v2).x -never_used___ * (v3).x, \
	(v1).y = (v2).y -never_used___ * (v3).y 
#define VSSub(v1, v2, s3, v3) \
	(v1).x = (v2).x - (s3) * (v3).x, \
	(v1).y = (v2).y - (s3) * (v3).y 
#define VWrap(v, t)		\
	if (v.t >= 0.5 * region.t)      v.t -= region.t;		\
	else if (v.t < -0.5 * region.t) v.t += region.t
#define VWrapAll(v)		\
		{VWrap (v, x);		\
		VWrap (v, y);		}
#define VDot(v1, v2)		\
	((v1).x * (v2).x + (v1).y * (v2).y )
#define VVMAdd(v1, v2, v3)		\
	(v1).x += (v2).x * (v3).x,		\
	(v1).y += (v2).y * (v3).y  
#define VMul(v1, v2, v3)		\
	(v1).x = (v2).x * (v3).x,		\
	(v1).y = (v2).y * (v3).y  
#define Sqr(x)     ((x) * (x))
#define Cube(x)    ((x) * (x) * (x))
#define VProd(v)		\
	((v).x * (v).y )
#define VCopy(v2, v1)		\
	(v2).x =  (v1).x,		\
(v2).y =  (v1).y
#define VSCopy(v2, s1, v1)		\
	(v2).x = (s1) * (v1).x,		\
(v2).y = (s1) * (v1).y
#define VCross(v3,v1,v2)		
real unused_uniform___;
#define VUniform(v)              \
			unused_uniform___ =  1./sqrt(VDot(v,v)) ,\
			VScale(v,unused_uniform___);
#define VDisjoin(v)	  (v).x , (v).y 

#endif
///////// Memory Alooc
#define AllocMem(a, n, t)  a = (t *) malloc ((n) * sizeof (t))
int never_used;
#define AllocMem2D(a, n, m, t)		\
	a = (t **) malloc ((n) * sizeof (t *)) ;		\
for(never_used=0; never_used<n ;		\
		never_used++) AllocMem(a[never_used], m,t )
///////////////////////////
#define PClear(p1)    (p1).m1=0,(p1).m2=0  
#define PSet(p1,v)    (p1).m1=(v),(p2).m2= Sqr(v)
#define PAdd(p1,v)    (p1).m1+=(v), (p2).m2+= Sqr(v)

//-----------------------------------------------------------------------------
//  Matrix 
//-----------------------------------------------------------------------------
#define MSetRotation(M, theta,ke)  


									

float ran1(long * idum);
float gasdev(long *);
float gasdev_asym(long *);

long good_seed();
// Process has done i out of n rounds,
// and we want a bar of width w and resolution r.
void loadBar(int x, int n,int retry, int r, int w);

#endif
