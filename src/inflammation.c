/*
 * inflammation.c
 *
 *  Created on: Nov 20, 2014
 *      Author: Ikaro Silva
 *      Copyright 2014
 */

/*
 * ODE model for inflammatory response based on:
 *
 * A Reynolds, Angela, et al.
 * "A reduced mathematical model of the acute inflammatory response: I. Derivation of model and analysis of anti-inflammation."
 * Journal of theoretical biology 242.1 (2006): 220-236.
 *
 */

#include "inflammation.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

static char *help_strings[] = {
		"usage: inflammation [OPTIONS ...]\n",
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


void inflammation(int argc,char* argv[]){

	int N=80;
	char ch;
	double Ts=0.1; //Sampling frequency in hours
	double headerFlag=0;

	//Model variables
	double P=1; //Initial Pathogen level
	double W=0;   //Initial Phagocyte level
	double D=0;   //Initial Tissue damage
	double CA=0.125; //Initial anti-inflamatory response


	//Model Parameters
	double kpm=0.6; //Rate at which local response eliminates pathogens
	double kmp=0.01; //Rate at which response is exhausted by pathogen
	double sm=0.005; //source of non-specific local response
	double um=0.002; //decay rate for non-specific local response
	double kpg=0.3;    //growth rate of pathogen
	double pinf=20e6; //max pathogen population
	double kpn=1.8;  //rate at which phagocytes consume pathogen
	double knp=0.1;  //activation of resting phagocytes by pathogen
	double knn=0.01;  //activation of resting phagocytes by other phagocytes and inflammation
	double snr=0.08; //source of resting phagocytes
	double unr=0.12; //decay rate of resting phagocytes
	double un=0.05; //decay rate of active phagocytes
	double knd=0.02; //activation of resting phagocytes by tissue damage
	double kdn=0.35; //Max rate of damage by Phagocytes
	double xdn=0.06; //Number of Phagocytes needed to bring damage production to half its max
	double ud=0.02; //Decay rate of damage (min 0.017 )
	double cinf=0.28; //strength of anti-inflamatory mediator
	double sc=0.0125; // sourc of anti-inflamatory mediator
	double kcn=0.04; //max production rate of anti-inflamatory mediator
	double kcnd=48; //effectiveness of activated phagocytes and damaged tissue in
	                //inducing production of anti-inflamatory mediator
	double uc=0.1; // decay rate of anti-inflamatory mediator


	while ((ch = getopt(argc,argv,"hN:v"))!=EOF)
		switch(ch){
		case 'N':
			N=atoi(optarg);
			break;
		case 'h':
			help();
			break;
		case 'v':
			headerFlag=1;
			break;
		default:
			fprintf(stderr,"Unknown option for one: '%s'\n",optarg);
			help();
		}

	argc-= optind;
	argv += optind;
	double dP;
	double dW;
	double dD;
	double dCA;
	int n=0;
	double fn, fs,fn2, R;
	xdn=pow(xdn,6);
	for(;n<N;n++){
		R=knn*W+ knp*P + knd*D;
		R=R/(1+ (CA/cinf)*(CA/cinf));
		fn=W/(1+ (CA/cinf)*(CA/cinf));
		fn2=W+kcnd*D;
		fn2=fn2/(1+ (CA/cinf)*(CA/cinf));
		fs=pow(fn,6)/(xdn + pow(fn,6));

		dP= kpg*P*(1-P/pinf) - kpm*sm*P/(um + kmp*P) - kpn*fn*P;
		dW= snr*R/(unr + R) - un*W;
		dD= kdn*fs - ud*D;
		dCA= sc + (kcn*fn2/(1 + fn2)) - uc*CA;

		P = P + Ts*dP;
		W = W + Ts*dW;
		D = D + Ts*dD;
		CA = CA + Ts*dCA;

		if(headerFlag){
			printf("Pathogen\tPhagocyte\tDamage\tAnti-inflammatory Mediator\t\n",P,W,D,CA);
		}
		printf("%.6f %.6f %.6f %.6f \n",P,W,D,CA);
	}

}

