/*
 * wbc.c
 *
 *  Created on: Nov 18, 2014
 *      Author: ikaro
 */

/* Model for white blood cell production ( peripheral control in haematopoiesis ) based on:
 *
 * "Pathological Conditions Resulting from Instabilities in Physiological Control Systems"
 * Glass and Mackey, 1979
 *
 */
#include "wbc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

static char *help_strings[] = {
		"usage: [OPTIONS ...]\n",
		"where OPTIONS may include:",
		" -N n             number of samples to generate",
		" -h               print this usage summary",
		" -n double        parameter n (0< n< 20, with equilibrium at 5.0404)"
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

void wbc(int argc,char* argv[]){

	int N=80;
	char ch;
	double x=0.5;
	double theta=1.0;
	double tau=2.0;
	double gama=1.0;
	double lambda =2.0;
	double Ts=0.05;
	double n=5.0404;
	int windowN=(int) tau/Ts;
	double *xt=malloc(windowN*sizeof(double));

	while ((ch = getopt(argc,argv,"hN:n:"))!=EOF)
		switch(ch){
		case 'N':
			N=atoi(optarg);
			break;
		case 'n':
			n=atof(optarg);
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


	double dx=0;
	long int i=0;
	int head=0, tail=0;
	int queueFull=0;
	theta=pow(theta,n);
	for(;i<N;i++){
		*(xt+head)=x;
		dx = -gama*x + ( lambda * theta * (*(xt+tail)) )/(theta + pow(*(xt+tail),n));
		x = x + dx*Ts;
		//printf("%.6f\t%.6f\t%.6f\n",(double) i*Ts,x,*(xt+tail));
		printf("%.6f\n",x);
		head++;
		if(head>(windowN-1)){
			queueFull=1;
			head=0;
		}
		if(queueFull){
			if(head == windowN-1){
				tail=0;
			}else{
				tail=head+1;
			}
		}
	}
}
