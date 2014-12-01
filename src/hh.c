/* file: hh.c	 Ikaro Silva
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

/*
 * Hodgkin-Huxley model for neural excitation based on:
 * Example 7.5 from "Numerical Methods in Biomedical Engineering", Dunn et al, Acadmic Press Series
 *
 */
#include "hh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

static char *help_strings[] = {
		"usage: hh [OPTIONS ...]\n",
		"where OPTIONS may include:",
		" -N n             number of samples to generate",
		" -s f             sampling interval (default 0.01)",
		" -h               print this usage summary",
		"The standard output is one column.",
		NULL
};

static void help()
{
	int i;
	for (i = 0; help_strings[i] != NULL; i++)
		fprintf(stderr, "%s\n", help_strings[i]);
	exit(-1);
}

/*Define constants of the model,but allow them to be overwritten from command line*/
double GK=36.0;
double VK=-12.0;
double V0=8.0;
double H0=0.5961;
double GNA=120.0;
double VNA=115.0;
double N0=0.3177;
double GL=0.3;
double VL=10.6;
double M0=0.05293;
double I=10.0;
double CM=1.0;


inline double alphaN(double v){
	return 0.01*(10 -v )/(exp( (10-v)/10.0 ) - 1.0);
}

inline double alphaM(double v){
	return 0.1*(25 -v )/(exp( (25-v)/10.0 ) - 1.0);
}

inline double alphaH(double v){
	return 0.07*exp(-v/20.0);
}

inline double betaN(double v){
	return 0.125*exp(-v/80.0);
}

inline double betaM(double v){
	return 4.0*exp(-v/18.0);
}

inline double betaH(double v){
	return 1.0/(exp( (30-v)/10.0 ) + 1.0);
}


inline void dx(double v, double n, double m,double h, double* dV){
	dV[0]=( -GK*n*n*n*n*(v-VK) - GNA*m*m*m*h*(v-VNA) - GL*(v-VL) + I ) /CM;
	dV[1]=alphaN(v)*(1-n)-betaN(v)*n;
	dV[2]=alphaM(v)*(1-m)-betaM(v)*m;
	dV[3]=alphaH(v)*(1-h)-betaH(v)*h;
}


void hh(int argc,char* argv[]){

	int N=10;
	char ch;
	double Ts=0.01;
	while ((ch = getopt(argc,argv,"hN:s:"))!=EOF)
		switch(ch){
		case 'N':
			N=atoi(optarg);
			break;
		case 's':
			Ts=atof(optarg);
			break;
		case 'h':
			help();
			break;
		default:
			fprintf(stderr,"Unknown option for hh: '%s'\n",optarg);
			help();
		}

	argc-= optind;
	argv += optind;

	double v=V0,n=N0,m=M0,h=H0;
	double dV[4]={0,0,0,0};
	long int t=0;
	for(;t<N;t++){
		dx(v,n,m,h,dV);
		/*Use trapezoid rule for integration */
		v=v+Ts*dV[0];
		n=n+Ts*dV[1];
		m=m+Ts*dV[2];
		h=h+Ts*dV[3];
		printf("%.6f\n",v);
	}
}





