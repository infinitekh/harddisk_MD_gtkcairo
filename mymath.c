#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)



float ran1(long *idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	float temp;
	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) *idum += IM;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;

}
// 외부에서 쓸일 없음 숨김.
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
	a=a-b;  a=a-c;  a=a^(c >> 13);
	b=b-c;  b=b-a;  b=b^(a << 8);
	c=c-a;  c=c-b;  c=c^(b >> 13);
	a=a-b;  a=a-c;  a=a^(c >> 12);
	b=b-c;  b=b-a;  b=b^(a << 16);
	c=c-a;  c=c-b;  c=c^(b >> 5);
	a=a-b;  a=a-c;  a=a^(c >> 3);
	b=b-c;  b=b-a;  b=b^(a << 10);
	c=c-a;  c=c-b;  c=c^(b >> 15);
	return c;
}
long good_seed()
{
	int myFile = open("/dev/random",O_RDONLY);
	long rand;
	if( 0 < myFile) 
		rand = mix(clock(), time(NULL), getpid());
	else {
		int ret = read(myFile,&rand, sizeof(long) );
		close(myFile);
	}
	return rand;
}

/** from Numerical  Recipe`s RNG */
float gasdev( long  *idum)
{
	float ran1(long *idum);
	static int iset=0;
	static float gset;
	float fac,rsq,v1,v2;

	if (*idum <0) iset=0;
	if (iset ==0) {
		do {
			v1=2.0*ran1(idum)-1.0;
			v2=2.0*ran1(idum)-1.0;
			rsq=v1*v1+v2*v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac=sqrt(-2.0*log(rsq)/rsq);
		gset=v1*fac;
		iset=1;
		return v2*fac;
	} else {
		iset=0;
		return gset;
	}
}
/** from LAMMPS SRD P(v) ~ v*exp(-v^2/2\sigma^2) */
float gasdev_asym( long *idum)
{
	float r1,r2;
	r1 = gasdev( idum);
	r2 = gasdev( idum);
	return sqrt(r1*r1+r2*r2);
}

// Process has done i out of n rounds,
// and we want a bar of width w and resolution r.
void loadBar(int x, int n,int retry, int r, int w)
{
	int i;
	// Only update r times.
	if ( x % (n/r) != 0 ) return;

	// Calculuate the ratio of complete-to-incomplete.
	float ratio = x/(float)n;
	int   c     = ratio * w;

	// Show the percentage complete.
	printf("retry:%3d     %3d%% [",retry, (int)(ratio*100) );

	// Show the load bar.
	for (i=0; x<c; x++)
		printf("=");

	for (i=c; x<w; x++)
		printf(" ");

	// ANSI Control codes to go back to the
	// previous line and clear it.
	// printf("]\n33[F33[J");
	printf("\r"); // Move to the first column
	fflush(stdout);
}


//  vim: noai:ts=2:sw=2
