#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "solver.h"
#include "statistics.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	simparams X;

	X.m = 1;
	X.lambda = 1./6.;
	X.n = 4;
	X.gamma = 1./X.n;
	X.rho = 100;
	X.N = 10; // default
	X.tmax = 100;
	X.steps = 1e6;
	X.dt = X.tmax*1.0/X.steps;

	double te = 14; // ?
	int maxN = 100;
	double *var = (double*) malloc(maxN * sizeof(double));

        FILE* fp;
        if ((fp = fopen("Var.dat","w")) == NULL) return 1;
	#pragma omp parallel for
	for (int n = 1; n < maxN; n++) {
		X.N = n;
		printf("### N = %d ###\n", X.N);

		double **q = (double**) malloc(X.N * sizeof(double));
		for (int i = 0; i < X.N; i++)
			q[i] = (double*) malloc(X.steps * sizeof(double));

		double **p = (double**) malloc(X.N * sizeof(double));
		for (int i = 0; i < X.N; i++)
			p[i] = (double*) malloc(X.steps * sizeof(double));

		double *Q = (double*) malloc(X.steps * sizeof(double));

		double *EKin = (double*) malloc(X.steps * sizeof(double));

		printf("Setting up the simulation\n");
		setup_simulation(q, p, X.N);

		printf("Integrating differential equation\n");
		for (int t = 0; t < X.steps-1; t++) {
			velocity_verlet_step(q, p, t, &X);
		}

		printf("Calculating COM motion and kinetic energy\n");
		centre_of_mass_motion(Q, q, &X);
		kinetic_energy(EKin, p, &X);
		var[X.N] = mean_kinetic_energy(EKin, te, &X);
		fprintf( fp, "%d\t%e\n", X.N, var[X.N]);
		fflush(fp);

		if ( n == maxN-1 ) {
			printf("Writing results to disk\n");
			write_single_pointer("Q.dat", Q, X.steps, X.dt);
			write_single_pointer("EKin.dat", EKin, X.steps, X.dt);
		}

		free(q);
		free(p);
		free(Q);
		free(EKin);
	}
        fclose(fp);
	free(var);

	return 0;
}
