/* file: rungekutta4.c	 Ikaro Silva	November2, 2014
		  Last revised:       -

-------------------------------------------------------------------------------
Copyright (C) 2014 Ikaro Silva

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA.

You may contact the author by e-mail (ikaro@mit.edu).
_______________________________________________________________________________
 */
#include <stdio.h>
#include <stdlib.h>

double* integrate(double t0, int N, long M, double h, double* x0, double* (*dx)(double t, double *x) )
{
	double* y=malloc(N*M*sizeof(double));
	int n,m ;
	if(y== NULL){
		fprintf(stderr,"Insufficient memory");
		exit(1);
	}

	for(m=0;n<M;n++){
		y[0]=x0[m];
	}

	double k1[M], k2[M], k3[M], k4[M], t=t0;

	/*
	for(n=1;n<N;n++){
		for(m=0;m<M;m++){
			k1[m]=h* dx(t,y[n-1][m]);
			k2[m]=h*dx(t+ h/2.0,y[n-1][m]+ k1/2.0);
			k3[m]=h*dx(t+ h/2.0,y[n-1][m]+ k2/2.0);
			k4[m]=h*dx(t+ h,y[n-1][m]+ k3);
			y[n][m]=y[n-1][m] + (k1[m] + 2*k2[m] + 2*k3[m] + k4[m])/6.0;
		}
		t=t+h;
	}
*/
	return y;

}

