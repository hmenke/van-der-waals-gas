#ifndef __SIMULATION_H
#define __SIMULATION_H

/*
 * Struct to store values, which are often reused.
 */
typedef struct {
	double m;
	double lambda;
	int n;
	double gamma;
	double rho;
	
	int N;
	int tmax;
	int steps;
	double dt;
} simparams;

void setup_simulation(double **q, double **p, int N);

#endif
