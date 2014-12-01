/*
 * one.c
 *
 *  Created on: Nov 15, 2014
 *      Author: ikaro
 */

#include "one.h"
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

static double gauss(double u, double std)
{
  double x= (rand()+1.0)/(RAND_MAX+1.0);
  double y= (rand()+1.0)/(RAND_MAX+1.0);
  x=sqrt(-2*log(y)) * cos(2*PI*x);
  return (x+u)*std;
}


void one(int argc,char* argv[]){

	int N=80;
	char ch;
	double A=4, p=0.95;
	double sigW=2, sigV=3;
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

	double x=70,y=0;
	long int n=0;
	sigV=sqrt(sigV);
	sigW=sqrt(sigW);

	for(;n<N;n++){
		x=A + p*x + gauss(0.0,sigV);
		y= x + gauss(0.0,sigW);
		printf("%.6f\n",y);
	}
}
