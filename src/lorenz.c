/*
 * lorenz.c
 *
 *  Created on: Nov 16, 2014
 *      Author: ikaro
 */

#include "lorenz.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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


void lorenz(int argc,char* argv[]){

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
			fprintf(stderr,"Unknown option for lorenz: '%s'\n",optarg);
			help();
		}

	argc-= optind;
	argv += optind;

	double x=1, y=1, z=1;
	double dx=0, dy=0, dz=0;
	double T=0.01;
	long int n=0;
	for(;n<N;n++){
		dx= 10*(y-x);
		dy= 28*x -y -x*z;
		dz=28*x*y - (8*z/3.0);
		x= x + T*dx;
		y= y + T*dy;
		z= z + T*dz;
		printf("%.6f\n",x);
	}
}
