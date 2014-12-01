/*
 * five.c
 *
 *  Created on: Nov 16, 2014
 *      Author: ikaro
 */


#include "five.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

static char *help_strings[] = {
 "usage: one [OPTIONS ...]\n",
 "where OPTIONS may include:",
 " -N n             number of samples to generate",
 " -h               print this usage summary",
 "The standard output is one column.",
NULL
};

static void help()
{
    int i;

    fprintf(stderr, help_strings[0]);
    for (i = 1; help_strings[i] != NULL; i++)
    	fprintf(stderr, "%s\n", help_strings[i]);
    exit(-1);
}

void five(int argc,char* argv[]){

	int N=80;
	char ch;
	while ((ch = getopt(argc,argv,"hN:"))!=EOF)
		switch(ch){
		case 'N':
			N=atoi(optarg);
			break;
		case 'h':
			help();
			break;
		default:
			fprintf(stderr,"Unknown option for one: '%s'\n",optarg);
			help();
		}

	argc-= optind;
	argv += optind;

	double x=1,y=1, z=1, v=0, zold, m, yold;
	long int n=0;

	for(;n<N;n++){
		zold=z;
		z=1.4 + 0.3*v - z*z;
		v=zold;
		m= 0.4 - 6.0 / (1.0 + x*x + y*y);
		yold=y;
		y=0.7*(x*sin(m) + y*cos(m));
		x=1 + 0.7*(x*cos(m) + yold*sin(m)) + 0.2*zold;
		printf("%.6f\n",x);
	}
}
