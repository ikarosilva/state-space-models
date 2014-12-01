/* file: conway.c	 Ikaro Silva	Oct 10, 2014
		  Last revised:       -

-------------------------------------------------------------------------------
conway: TODO:Description
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

#include "conway.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char *help_strings[] = {
 "usage: conway [OPTIONS ...]\n",
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

void conway(int argc,char* argv[]){

	int N;
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
			fprintf(stderr,"Unknown option for conway: '%s'\n",optarg);
			help();
		}

	argc-= optind;
	argv += optind;

	double output;
	int a[N];
	long int n=0;
	for(;n<N;n++){
		if(n<3){
			a[n]=1;
			output=1;
		}else{
			a[n]=a[a[n-1]]+ a[n-a[n-1]];
			output= (double) a[n] - ((double)n/2.0);
		}
		printf("%.6f\n",output);
	}
}
